#include <ctime>
#include <iostream>
#include <string>
#include <map>
#include <stdlib.h>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>

#include <ros/ros.h>
#include <ros/package.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/Int64.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/Int64MultiArray.h>
#include <geometry_msgs/Vector3.h>
#include <std_srvs/Empty.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/JointState.h>
#include <sensor_msgs/Temperature.h>
#include <sensor_msgs/MagneticField.h>
#include <sensor_msgs/FluidPressure.h>

#include <robot_state_publisher/robot_state_publisher.h>
#include <kdl_parser/kdl_parser.hpp>
#include "ar601_messages/JointStatus.h"
#include "ar601_messages/Power.h"
#include "ar_packet.h"

using boost::asio::ip::udp;
const short PORT = 10001;
const int PUBLISHING_RATE = 10; // publishing rate - 10 Hz
const std::string robot_ip = "192.169.1.10";

// Publishers 
ros::Publisher joint_state_pub;
ros::Publisher joint_state_raw_pub;
ros::Publisher joint_status_pub;
ros::Publisher imu_pub;
ros::Publisher imu2_pub;
ros::Publisher temperature_pub;
ros::Publisher magnetic_field_pub;
ros::Publisher pressure_pub;
ros::Publisher power_pub;
ros::Publisher force_rfoot_pub;
ros::Publisher force_lfoot_pub;
ros::Publisher force_rarm_pub;
ros::Publisher force_larm_pub;
ros::Publisher force_uch_rfoot_pub; 
ros::Publisher force_uch_lfoot_pub;
ros::Publisher force_uch_rarm_pub;
ros::Publisher force_uch_larm_pub;

const std::string INI_LOCATION = "/config/config.ini";

KDL::Tree robot_tree;
robot_state_publisher::RobotStatePublisher * rsp;

std::map<int, int> devices;
std::map<int, std::string> device_names;
std::map<int, int> device_kp;
std::map<int, int> device_ki;
std::map<int, int> device_buffer;
std::map<int, int> device_maxpos;
std::map<int, int> device_minpos;
std::map<int, int> device_ilim;
std::map<int, bool> device_reverse;
std::map<int, int> device_type;
typedef std::map<int, int>::iterator it_type;

size_t LEFT_FOOT_DEVICE;
size_t RIGHT_FOOT_DEVICE;
size_t LEFT_ARM_DEVICE;
size_t RIGHT_ARM_DEVICE;

boost::array<uint8_t, PACKET_SIZE> send_buf;
boost::array<uint8_t, PACKET_SIZE> recv_buf;

typedef struct tensor_uch
{
  int16_t uch0;
  int16_t uch1;
  int16_t uch2;
  int16_t uch3;
} tensor_uch;

typedef struct force_coefficients_t
{
  double Kmx;
  double Kmy;
  double Kfz;
  double Kfz_mx;
  double Kfz_my;
  force_coefficients_t(double kmx, double kmy, double kfz, double kfz_mx, double kfz_my)
  {
    Kmx = kmx;
    Kmy = kmy;
    Kfz = kfz;
    Kfz_mx = kfz_mx;
    Kfz_my = kfz_my;
  }
} force_coefficients_t;

force_coefficients_t foot_coefficients(0.0102, 0.0104, 0.0980, -0.0128, -0.0556);
force_coefficients_t arm_coefficients(0.0038, 0.0038, 0.0982, -0.0046, -0.0147);

tensor_uch uch_left_foot, uch_right_foot, uch_left_arm, uch_right_arm;

void publish_packet(ARPacketT & packet);

class udp_server
{
public:
 udp_server(boost::asio::io_service& io_service)
   : socket_(io_service, udp::endpoint(udp::v4(), PORT))
  {
    start_receive();
  }

private:
  void start_receive()
  {
    socket_.async_receive_from(
        boost::asio::buffer(recv_buf), remote_endpoint_,
        boost::bind(&udp_server::handle_receive, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }

  void handle_receive(const boost::system::error_code& error,
      std::size_t bytes/*bytes_transferred*/)
  {
    if (!error || error == boost::asio::error::message_size)
    {
      publish_packet(recv_buf);
      start_receive();
    }
  }

  void handle_send(boost::shared_ptr<std::string> /*message*/,
      const boost::system::error_code& /*error*/,
      std::size_t /*bytes_transferred*/)
  {
  }

  udp::socket socket_;
  udp::endpoint remote_endpoint_;
};

void on_48v(ARPacketT & sendb);
void on_12v(ARPacketT & sendb);
void on_8v_1(ARPacketT & sendb);
void on_8v_2(ARPacketT & sendb);
void on_6v_1(ARPacketT & sendb);
void on_6v_2(ARPacketT & sendb);
void off_48v(ARPacketT & sendb);
void off_12v(ARPacketT & sendb);
void off_8v_1(ARPacketT & sendb);
void off_8v_2(ARPacketT & sendb);
void off_6v_1(ARPacketT & sendb);
void off_6v_2(ARPacketT & sendb);

float get_POS(ARPacketT & sendb, short num);
void set_POS(ARPacketT & sendb, short num, float pvalue);
void MOT_STOP(ARPacketT & sendb, short num);
void MOT_TRACE(ARPacketT & sendb, short num);
void MOT_STOP_BR(ARPacketT & sendb, short num);
void MOT_RELAX(ARPacketT & sendb, short num);
void set_DUMP(ARPacketT & sendb, short num, short value);
void set_STIFF(ARPacketT & sendb, short num, short value);

class power_sub
{
  int line;
  ros::Subscriber ps;
  
  void powerCallback(const std_msgs::UInt8::ConstPtr& s)
  {
    int signal = s->data; 
    switch(line)
      {
      case 48:
	if (signal == 1)
	  on_48v(send_buf);
	else
	  off_48v(send_buf);
	break;
      case 12:
	if (signal == 1)
	  on_12v(send_buf);
	else
	  off_12v(send_buf);
	break;
      case 82:
	if (signal == 1)
	  on_8v_2(send_buf);
	else
	  off_8v_2(send_buf);
	break;
      case 81:
	if (signal == 1)
	  on_8v_1(send_buf);
	else
	  off_8v_1(send_buf);
	break;
      case 62:
	if (signal == 1)
	  on_6v_2(send_buf);
	else
	  off_6v_2(send_buf);
	break;
      case 61:
	if (signal == 1)
	  on_6v_1(send_buf);
	else
	  off_6v_1(send_buf);
	break;
      };
    ROS_INFO("Power line %d command : [%d]", line, signal);
  }

public:
  power_sub(ros::NodeHandle n, int line_)
  {
    line = line_;
    char buffer[16];
    sprintf(buffer, "power/%dv", line_);
    ps = n.subscribe(buffer, 1000, &power_sub::powerCallback, this );
  }
};

class joint_control 
{
  int n_joint;
  ros::Subscriber command;
  ros::Subscriber state;
  ros::Subscriber controller_p;
  ros::Subscriber controller_i;

  void joint_command_callback(const std_msgs::Float64::ConstPtr& s)
  {
    set_POS(send_buf, n_joint, s->data);
  }
  
  void joint_state_callback(const std_msgs::Int8::ConstPtr& s)
  {
    switch(s->data)
      {
      case 0: MOT_STOP_BR(send_buf, n_joint); break;
      case 1: MOT_STOP(send_buf, n_joint); break;    
      case 2: MOT_RELAX(send_buf, n_joint); break;
      case 3: {set_POS(send_buf,n_joint,get_POS(recv_buf,n_joint));MOT_TRACE(send_buf, n_joint);} break;
      };
  }

  void joint_p_callback(const std_msgs::Int64::ConstPtr& p)
  {
    set_STIFF(send_buf, n_joint, p->data);
  }

  void joint_i_callback(const std_msgs::Int64::ConstPtr& p)
  {
    set_DUMP(send_buf, n_joint, p->data);
  }
  
public:
  joint_control(ros::NodeHandle n, int nj)
  {
    ROS_INFO("Setting up control for joint %d...", nj);
    n_joint = nj;
    char n_joint_command[32];
    char n_joint_state[32];
    char n_joint_p[32];
    char n_joint_i[32];
    sprintf(n_joint_command, "control/joint_%d/command", n_joint);
    sprintf(n_joint_state, "control/joint_%d/state", n_joint);
    sprintf(n_joint_p, "control/joint_%d/p", n_joint);
    sprintf(n_joint_i, "control/joint_%d/i", n_joint);
    command = n.subscribe(n_joint_command, 1000, &joint_control::joint_command_callback, this);
    state = n.subscribe(n_joint_state, 1000, &joint_control::joint_state_callback, this);
    controller_p = n.subscribe(n_joint_p, 1000, &joint_control::joint_p_callback, this);
    controller_i = n.subscribe(n_joint_i, 1000, &joint_control::joint_i_callback, this);
    ROS_INFO(" Done...\n");
  }
};

class AR601
{
 public:
  AR601() 
    {
    }
  
  void read() {}
  void write() {}
};


				       
