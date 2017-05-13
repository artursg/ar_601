#include "ros/topic.h"
#include <preview_control_node.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int64.h>
#include <geometry_msgs/PointStamped.h>
#include <sensor_msgs/JointState.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include "ar601_messages/IK.h"
#include "ar601_messages/FK.h"
#include "ar601_trajectories/GetTrajectory.h"
#include <deque>
#include <Eigen/Core>
#include <math.h>

using namespace message_filters;

ros::ServiceClient ik_service;
ros::ServiceClient fk_service;
ros::ServiceClient trajectory_service;
ros::Publisher pubLHipYaw, pubLHipRoll, pubLHipPitch, pubLKneePitch, pubLAnklePitch, pubLAnkleRoll, pubRHipYaw, pubRHipRoll, pubRHipPitch, pubRKneePitch, pubRAnklePitch, pubRAnkleRoll, pubXController, pubYController;
ros::Publisher pubLHipYaw_p, pubLHipRoll_p, pubLHipPitch_p, pubLKneePitch_p, pubLAnklePitch_p, pubLAnkleRoll_p, pubRHipYaw_p, pubRHipRoll_p, pubRHipPitch_p, pubRKneePitch_p, pubRAnklePitch_p, pubRAnkleRoll_p;
ros::Publisher pubZMP_X, pubZMP_Y;
ros::Subscriber joint_states_sub;

preview_control_node * pcn;

double zmp_x, zmp_y, los_x, los_y, ros_x, ros_y, teta_left,teta_right;

std::deque<double> dx, dy;

const size_t window = 5;
const size_t window2 = 50;

double pre_rfoot_angles[6];
double pre_lfoot_angles[6];

double joints_state[12];
double angle_error[12];
double f_angle_error[12];
std::deque<double> dangle[12];


void jsCallback(const sensor_msgs::JointState::ConstPtr& msg)
{
  joints_state[0] = msg->position[0];
  joints_state[1] = msg->position[1];
  joints_state[2] = msg->position[2];
  joints_state[3] = msg->position[3];
  joints_state[4] = msg->position[4];
  joints_state[5] = msg->position[5];
  joints_state[6] = msg->position[6];
  joints_state[7] = msg->position[7];
  joints_state[8] = msg->position[8];
  joints_state[9] = msg->position[9];
  joints_state[10] = msg->position[10];
  joints_state[11] = msg->position[11];
}

void keCallback(const std_msgs::Float64::ConstPtr& msg)
{
  if (pcn != NULL)
    pcn->set_scale_K_e(msg->data);
  ROS_INFO("scale changed in main callback to %f",msg->data);
}

void callback(const geometry_msgs::PointStamped::ConstPtr& left, const geometry_msgs::PointStamped::ConstPtr& right)
{
  double force = right->point.z + left->point.z;
  double x, y;
  if (force < 0.001)
  {
    ROS_INFO("Negative weight!");
    x=0;
    y=0;
  }
  else
  {
    x=((ros_x+right->point.x*cos(teta_right)-right->point.y*sin(teta_right))*right->point.z + (los_x+left->point.x*cos(teta_left)-left->point.y*sin(teta_left))*left->point.z)/(force);
    y=((ros_y+right->point.y*cos(teta_right)+right->point.x*sin(teta_right))*right->point.z + (los_y+left->point.y*cos(teta_left)+left->point.x*sin(teta_left))*left->point.z)/(force);
  }
  if (isnan(x))
    x = 0;
  if (isnan(y))
    y = 0;

  dx.push_back(x);
  dy.push_back(y);
  size_t dsize = dx.size();
  if (dsize > window)
  {
    dx.pop_front();
    dy.pop_front();
    dsize--;
  }
  x = y = 0;
  for (std::deque<double>::const_iterator it = dx.begin(); it != dx.end(); it++)
    x += *it;
  for (std::deque<double>::const_iterator it = dy.begin(); it != dy.end(); it++)
    y += *it;
  zmp_x = x/dsize;
  zmp_y = y/dsize;
  if (fabs(zmp_x)>100)
      ROS_INFO("Error!!! %f %f %f %f %f %f", right->point.x, left->point.x, ros_x, los_x,right->point.z,left->point.z);
  if (fabs(zmp_y)>100)
      ROS_INFO("Error!!! %f %f %f %f", right->point.y, left->point.y,right->point.z,left->point.z);
  std_msgs::Float64 datax, datay;
  datax.data = zmp_x;
  datay.data = zmp_y;
  pubZMP_X.publish(datax);
  pubZMP_Y.publish(datay);
}

void zmpxCallback(const std_msgs::Float64::ConstPtr& msg)
{
  zmp_x = msg->data;
}

void zmpyCallback(const std_msgs::Float64::ConstPtr& msg)
{
  zmp_y = msg->data;
}

double torso_roll(double y)
{
  const double border = 0.0228;
  if (y < -border)
  {
    return (y + border)*(-0.8295)+0.038076;
  }
  else if (y > border)
  {
    return (y - border)*-(0.8295)-0.038076;
  }
  else
  {
    return -1.67*y;
  }

}

double torso_pitch(double x)
{
  const double border = 0.04;
  if (x < -border) {
    return (x + 0.04)*0.0;
  }
  else if (x > border){
    return (x - 0.04)*-0.0;
  }
  else {
    return 0.0;
  }
}

void set_initial_pose(double foot_diff, double height, boost::shared_ptr<sensor_msgs::JointState const> ptr) 
{
  ros::Rate r(250);
  ar601_messages::IK::Request req;
  ar601_messages::IK::Response resLeft, resRight;
  req.left = true;
  req.x = 0;
  req.y = foot_diff;
  req.z = 0;
  req.phi_x = 0;
  req.phi_y = 0;
  req.phi_z = 0;
  req.x_t = 0;
  req.y_t = 0;
  req.z_t = height;
  req.phi_x_t = 0;
  req.phi_y_t = 0;
  req.phi_z_t = 0;    
  ik_service.call(req, resLeft);
  req.left = false;
  req.x = 0;
  req.y = -foot_diff;
  req.z = 0;
  req.phi_x = 0;
  req.phi_y = 0;
  req.phi_z = 0;
  req.x_t = 0;
  req.y_t = 0;
  req.z_t = height;
  req.phi_x_t = 0;
  req.phi_y_t = 0;
  req.phi_z_t = 0;
  ik_service.call(req, resRight);
  double goal[12];
  for (int i = 0; i < 6; i++)
  {
    goal[i] = resLeft.angles[i];
    //ROS_INFO("Goal %lf", goal[i]);
  }
  for (int i = 0; i < 6; i++)
  {
    goal[6 + i] = resRight.angles[i];
    //ROS_INFO("Goal %lf", goal[6 + i]);
  }
  double state[12];
  for (int i = 0; i < 12; i++)
    state[i] = ptr->position[i];
  for (int i = 0; i < 12; i++)
  {
    //ROS_INFO("State %lf", state[i]);
  }
  //size_t t = 2000;
  size_t t;
  if (fabs(goal[3]-state[8])>5)
    {t=2500;}
  else
    {t=500;}
  for(int i = 0; i < t; i++)
  {
    std_msgs::Float64 data[12];
    for (int j = 0; j < 12; j++)
      data[j].data = state[11 - j] + (goal[j] - state[11 - j])*(i/(double)t);
    pubLHipYaw.publish(data[0]);
    pubLHipRoll.publish(data[1]);
    pubLHipPitch.publish(data[2]);
    pubLKneePitch.publish(data[3]);
    pubLAnklePitch.publish(data[4]);
    pubLAnkleRoll.publish(data[5]);
    pubRHipYaw.publish(data[6]);
    pubRHipRoll.publish(data[7]);
    pubRHipPitch.publish(data[8]);
    pubRKneePitch.publish(data[9]);
    pubRAnklePitch.publish(data[10]);
    pubRAnkleRoll.publish(data[11]);
    r.sleep();
    ros::spinOnce();
  }
  ROS_INFO("Initial setup complete");
  ROS_INFO("Press Enter to continue");
  getchar();
  
}

int stiffness_from_error(double x)
{
  int res=1000;
  if (fabs(x)>2)
  {
    res=10500;
  }
  else
  {
    res=500+5000.0*fabs(x);
  }
  return res;
}

int main(int argc, char ** argv)
{
  double _dt, _t0, _z0, _l0, _h, _T, _y0;
  int _trajectory;
  ros::init(argc, argv, "preview_control_node");
  try{
    ros::NodeHandle nh;
    zmp_x = zmp_y = 0;
    ik_service = nh.serviceClient<ar601_messages::IK>("ik_server");
    fk_service = nh.serviceClient<ar601_messages::FK>("fk_server");
    trajectory_service = nh.serviceClient<ar601_trajectories::GetTrajectory>("get_trajectory");
    pubLHipYaw = nh.advertise<std_msgs::Float64>("control/joint_12/command", 1000);
    pubLHipRoll = nh.advertise<std_msgs::Float64>("control/joint_11/command", 1000);
    pubLHipPitch = nh.advertise<std_msgs::Float64>("control/joint_10/command", 1000);
    pubLKneePitch = nh.advertise<std_msgs::Float64>("control/joint_9/command", 1000);
    pubLAnklePitch = nh.advertise<std_msgs::Float64>("control/joint_8/command", 1000);
    pubLAnkleRoll = nh.advertise<std_msgs::Float64>("control/joint_7/command", 1000);
    pubRHipYaw = nh.advertise<std_msgs::Float64>("control/joint_6/command", 1000);
    pubRHipRoll = nh.advertise<std_msgs::Float64>("control/joint_5/command", 1000);
    pubRHipPitch = nh.advertise<std_msgs::Float64>("control/joint_4/command", 1000);
    pubRKneePitch = nh.advertise<std_msgs::Float64>("control/joint_3/command", 1000);
    pubRAnklePitch = nh.advertise<std_msgs::Float64>("control/joint_2/command", 1000);
    pubRAnkleRoll = nh.advertise<std_msgs::Float64>("control/joint_1/command", 1000);

    pubLHipYaw_p = nh.advertise<std_msgs::Int64>("control/joint_12/p", 1000);
    pubLHipRoll_p = nh.advertise<std_msgs::Int64>("control/joint_11/p", 1000);
    pubLHipPitch_p = nh.advertise<std_msgs::Int64>("control/joint_10/p", 1000);
    pubLKneePitch_p = nh.advertise<std_msgs::Int64>("control/joint_9/p", 1000);
    pubLAnklePitch_p = nh.advertise<std_msgs::Int64>("control/joint_8/p", 1000);
    pubLAnkleRoll_p = nh.advertise<std_msgs::Int64>("control/joint_7/p", 1000);
    pubRHipYaw_p = nh.advertise<std_msgs::Int64>("control/joint_6/p", 1000);
    pubRHipRoll_p = nh.advertise<std_msgs::Int64>("control/joint_5/p", 1000);
    pubRHipPitch_p = nh.advertise<std_msgs::Int64>("control/joint_4/p", 1000);
    pubRKneePitch_p = nh.advertise<std_msgs::Int64>("control/joint_3/p", 1000);
    pubRAnklePitch_p = nh.advertise<std_msgs::Int64>("control/joint_2/p", 1000);
    pubRAnkleRoll_p = nh.advertise<std_msgs::Int64>("control/joint_1/p", 1000);

    pubXController = nh.advertise<std_msgs::Float64>("x_controller", 1000);
    pubYController = nh.advertise<std_msgs::Float64>("y_controller", 1000);
    
    pubZMP_X = nh.advertise<std_msgs::Float64>("zmp_x", 1000);
    pubZMP_Y = nh.advertise<std_msgs::Float64>("zmp_y", 1000);
    FILE *f=fopen("test.log","w");
    FILE *f_ref=fopen("ref_angles.log","w");
    FILE *f_enc=fopen("enc_angles.log","w");
    FILE *f_err=fopen("err_angles.log","w");
    FILE *f_stiff=fopen("stiffness.log","w");
    FILE *f_zmp_error_out=fopen("zmp_error_out.log","w");

    
    message_filters::Subscriber<geometry_msgs::PointStamped> left_sub(nh, "/force/left_foot_uch_zmp", 1);
    message_filters::Subscriber<geometry_msgs::PointStamped> right_sub(nh, "/force/right_foot_uch_zmp", 1);
    TimeSynchronizer<geometry_msgs::PointStamped, geometry_msgs::PointStamped> sync(left_sub, right_sub, 10);
    sync.registerCallback(boost::bind(&callback, _1, _2));
    
    ros::Subscriber js_sub = nh.subscribe("/joint_states", 1000, jsCallback);
    ros::Subscriber Ke_sub = nh.subscribe("pc_scale_ke", 1000, keCallback);
    
    /* Get parameters */
    if (!nh.getParam("t0", _t0))
    {
     _t0 = 5;
    }
    if (!nh.getParam("z0", _z0))
    {
      _z0 = 0.7;
    }
    if (!nh.getParam("T", _T))
    {
      _T = 4e-3;
    }
    if (!nh.getParam("trajectory", _trajectory))
      _trajectory = 5;
    ros::Rate loop_rate(1/_T);
    ROS_INFO("Loop rate %f", 1/_T);
    preview_control_node pc_node(_T, _z0);
    pcn = &pc_node;
    pc_node.load_G_p();
    pc_node.set_scale_K_e(0.0); //0.1
    ar601_trajectories::GetTrajectory::Request  reqTrajectory;
    ar601_trajectories::GetTrajectory::Response resTrajectory;
    reqTrajectory.type = _trajectory;
    trajectory_service.call(reqTrajectory, resTrajectory);
    ROS_INFO("Trajectory %d recieved %zd", _trajectory, resTrajectory.N);
    int c = 0;
    boost::shared_ptr<sensor_msgs::JointState const> sharedPtr;
    sharedPtr = ros::topic::waitForMessage<sensor_msgs::JointState>("/joint_states", ros::Duration(4.0));
    set_initial_pose(0.09, 0.7, sharedPtr);

    //zmp compensation

    // FILE *f_zmp_comp;
    // double zmp_comp[resTrajectory.N];
    // if((f_zmp_comp=fopen("compensation.txt","r"))==NULL)
    // {
    //   ROS_INFO("ZMP file not found");
    //   return -1;
    // }
    // else
    // {

    //   for(int j=0;j<resTrajectory.N;j++)
    //   {
    //     fscanf(f_zmp_comp,"%lf ",&zmp_comp[j]);
    //     ROS_INFO("j:=%d zmp_comp:= %f",j,zmp_comp[j] );
    //   }

    // getchar();
    // }
    // fclose(f_zmp_comp);

    for (int i = 0; i < resTrajectory.N; i++)
      pc_node.add_path_point(resTrajectory.zmp_x[i], resTrajectory.zmp_y[i]);//+zmp_comp[i]);
    bool first = true;
    for (int i = 0; i < 12; i++)
      f_angle_error[i]=0;

    //zmp_error on previous trial

    // FILE *f_zmp_error_in;
    // double zmp_error[resTrajectory.N][2];
    // if((f_zmp_error_in=fopen("zmp_error_in.log","r"))==NULL)
    // {
    //   ROS_INFO("ZMP file not found");
    //   return -1;
    // }
    // else
    // {
    //   for (int i=0;i<resTrajectory.N;i++)
    //   {
    //     for(int j=0;j<2;j++)
    //     {
    //       fscanf(f_zmp_error_in,"%lf ",&zmp_error[i][j]);
    //       ROS_INFO("i:=%d j:=%d zmp_error:= %f", i, j,zmp_error[i][j] );
    //     }
    //   }
    // getchar();
    // }
    // fclose(f_zmp_error_in);

    


    //stiffness at contact
    int left_p[resTrajectory.N];
    int right_p[resTrajectory.N];
    int p_0=4000; //initial stiffness
    for (int i = 0; i < resTrajectory.N; i++)
    {
      left_p[i]=p_0;
      right_p[i]=p_0;
    }
    int m,n;
    int relax_duration=50;  //relaxation time *0.004
    for (int i = 1; i < resTrajectory.N; i++)
    {
      if ((resTrajectory.z_left[i-1]>0)&&(resTrajectory.z_left[i]==0))
      {
        m=i-relax_duration; 
        if (m<0)
          m=0;
        n=i+relax_duration;
        if (n>resTrajectory.N)
          n=resTrajectory.N;
        for (int k = m; k < n+1; k++)
        {
          if (k<=i)
            {left_p[k]=0;}
          else
            {left_p[k]=p_0*(k-i)/(n-i);} //p_0*(1-0.5*(1-cos(2*M_PI*(k-m)/(n-m))));}
        }
      } 
      if ((resTrajectory.z_right[i-1]>0)&&(resTrajectory.z_right[i]==0))
      {
        m=i-relax_duration; 
        if (m<0)
          m=0;
        n=i+relax_duration;
        if (n>resTrajectory.N)
          n=resTrajectory.N;
        for (int k = m; k < n+1; k++)
        {
          if (k<=i)
            {right_p[k]=0;}
          else
            {right_p[k]=p_0*(k-i)/(n-i);} //p_0*(1-0.5*(1-cos(2*M_PI*(k-m)/(n-m))));}
        }
      }
    }

    // main loop

    while(ros::ok()) {
      pc_node.update(Eigen::Vector2d(zmp_x, zmp_y));
      //pc_node.update(Eigen::Vector2d(zmp_error[0][c], zmp_error[1][c]));      
      los_x = resTrajectory.x_left[c];
      los_y = resTrajectory.y_left[c];
      ros_x = resTrajectory.x_right[c];
      ros_y = resTrajectory.y_right[c];
      teta_left=resTrajectory.theta_left[c];
      teta_right=resTrajectory.theta_right[c];
      double x1, x2, x3, y1, y2, y3;
      
      pc_node.get_xk(x1, x2, x3);
      pc_node.get_yk(y1, y2, y3);
      fprintf(f,"%f %f %f %f %f %f %f %f\n",x1,y1,x3,y3,zmp_x,zmp_y,resTrajectory.zmp_x[c], resTrajectory.zmp_y[c]);
      fprintf(f_zmp_error_out,"%f %f\n",zmp_x,zmp_y);
      ar601_messages::IK::Request req;
      ar601_messages::IK::Response resLeft, resRight;
      double h = _z0;
      double current_angle;
      if (fabs(resTrajectory.theta_right[c] - resTrajectory.theta_left[c])<M_PI)
      {
      	current_angle=(resTrajectory.theta_right[c] + resTrajectory.theta_left[c])/2;
      }
      else
      {
      	if ((resTrajectory.theta_right[c] + resTrajectory.theta_left[c])/2<0)
          {
             current_angle=-M_PI-(resTrajectory.theta_right[c] + resTrajectory.theta_left[c])/2;
          }
        else
          {
             current_angle=M_PI-(resTrajectory.theta_right[c] + resTrajectory.theta_left[c])/2;
          }
      }
      double y1_corrected = cos(current_angle)*(y1 - (resTrajectory.y_left[c] + resTrajectory.y_right[c])/2) - sin(current_angle)*(x1 - (resTrajectory.x_left[c] + resTrajectory.x_right[c])/2);
      req.left = true;
      req.x = resTrajectory.x_left[c];
      req.y = resTrajectory.y_left[c];
      req.z = resTrajectory.z_left[c];
      req.phi_x = 0;
      req.phi_y = 0;
      req.phi_z = resTrajectory.theta_left[c];
      req.x_t = x1;
      req.y_t = y1;
      req.z_t = h;
      req.phi_x_t = torso_roll(y1_corrected);
      req.phi_y_t = torso_pitch(x1 - 1/2*(resTrajectory.x_left[c] + resTrajectory.x_right[c]));
      req.phi_z_t = resTrajectory.theta_torso[c];    
      ik_service.call(req, resLeft);
      
      req.left = false;
      req.x = resTrajectory.x_right[c];
      req.y = resTrajectory.y_right[c];
      req.z = resTrajectory.z_right[c];
      req.phi_x = 0;
      req.phi_y = 0;
      req.phi_z = resTrajectory.theta_right[c];
      req.x_t = x1;
      req.y_t = y1;
      req.z_t = h;
      req.phi_x_t = torso_roll(y1_corrected);
      req.phi_y_t = torso_pitch(x1 - 1/2*(resTrajectory.x_left[c] + resTrajectory.x_right[c]));
      req.phi_z_t = resTrajectory.theta_torso[c];    
      ik_service.call(req, resRight);
      for (int i = 0; i < 6; i++)
    	{
    	  if (fabs(resLeft.angles[i] - pre_lfoot_angles[i]) > 0.5 && !first)
    	    {
    		//resLeft.angles[i] = pre_lfoot_angles[i];
    		ROS_INFO("Dangerous increase in left %d joint from %f to %f",i,pre_lfoot_angles[i],resLeft.angles[i]);
    		ROS_INFO("Left foot data: [%f,%f,%f,0,0,%f,%f,%f,%f,%f,%f,%f]",resTrajectory.x_left[c],resTrajectory.y_left[c],resTrajectory.z_left[c],resTrajectory.theta_left[c],x1,y1,h,torso_roll(y1_corrected),torso_pitch(x1 - 1/2*(resTrajectory.x_left[c] + resTrajectory.x_right[c])),resTrajectory.theta_torso[c]);
    		//ROS_INFO("Left foot data before 1 it: [%f,%f,%f,0,0,%f,%f,%f,%f,%f,%f,%f]",resTrajectory.x_left[c-1],resTrajectory.y_left[c-1],resTrajectory.z_left[c-1],resTrajectory.theta_left[c-1],x1,y1,h,torso_roll(y1_corrected),torso_pitch(x1 - 1/2*(resTrajectory.x_left[c] + resTrajectory.x_right[c])),resTrajectory.theta_torso[c-1]);
        ROS_INFO("%f",torso_roll(y1_corrected));
        ROS_INFO("y1= %f",y1);
    		return -1;
    	    }
    	  if (fabs(resRight.angles[i] - pre_rfoot_angles[i]) > 0.5 && !first)
    	    {
    		//resRight.angles[i] = pre_rfoot_angles[i];
    		ROS_INFO("Dangerous increase in right %d joint from %f to %f", i,pre_rfoot_angles[i], resRight.angles[i]);
    		ROS_INFO("Right foot data: [%f,%f,%f,0,0,%f,%f,%f,%f,%f,%f,%f]",resTrajectory.x_right[c],resTrajectory.y_right[c],resTrajectory.z_right[c],resTrajectory.theta_right[c],x1,y1,h,torso_roll(y1_corrected),torso_pitch(x1 - 1/2*(resTrajectory.x_left[c] + resTrajectory.x_right[c])),resTrajectory.theta_torso[c]);
    		ROS_INFO("Right foot data before 1 sec: [%f,%f,%f,0,0,%f,%f,%f,%f,%f,%f,%f]",resTrajectory.x_right[c-250],resTrajectory.y_right[c-250],resTrajectory.z_right[c-250],resTrajectory.theta_right[c-250],x1,y1,h,torso_roll(y1_corrected),torso_pitch(x1 - 1/2*(resTrajectory.x_left[c] + resTrajectory.x_right[c])),resTrajectory.theta_torso[c-250]);
    		return -1;
    	    }
    	  pre_lfoot_angles[i] = resLeft.angles[i];
    	  pre_rfoot_angles[i] = resRight.angles[i];
    	}
      if (first)
      	 first = false;

      std_msgs::Float64 data[12];
      data[0].data = resLeft.angles[0];//+f_angle_error[11];
      data[1].data = resLeft.angles[1];//+f_angle_error[10];
      data[2].data = resLeft.angles[2];//+f_angle_error[9];
      data[3].data = resLeft.angles[3];//+f_angle_error[8];
      data[4].data = resLeft.angles[4];//+f_angle_error[7];
      data[5].data = resLeft.angles[5];//+f_angle_error[6];
      data[6].data = resRight.angles[0];//+f_angle_error[5];
      data[7].data = resRight.angles[1];//+f_angle_error[4];
      data[8].data = resRight.angles[2];//+f_angle_error[3];
      data[9].data = resRight.angles[3];//+f_angle_error[2];
      data[10].data = resRight.angles[4];//+f_angle_error[1];
      data[11].data = resRight.angles[5];//+f_angle_error[0];
      pubLHipYaw.publish(data[0]);
      pubLHipRoll.publish(data[1]);
      pubLHipPitch.publish(data[2]);
      pubLKneePitch.publish(data[3]);
      pubLAnklePitch.publish(data[4]);
      pubLAnkleRoll.publish(data[5]);
      pubRHipYaw.publish(data[6]);
      pubRHipRoll.publish(data[7]);
      pubRHipPitch.publish(data[8]);
      pubRKneePitch.publish(data[9]);
      pubRAnklePitch.publish(data[10]);
      pubRAnkleRoll.publish(data[11]);

      angle_error[11]=resLeft.angles[0]-joints_state[11];
      angle_error[10]=resLeft.angles[1]-joints_state[10];
      angle_error[9]=resLeft.angles[2]-joints_state[9];
      angle_error[8]=resLeft.angles[3]-joints_state[8];
      angle_error[7]=resLeft.angles[4]-joints_state[7];
      angle_error[6]=resLeft.angles[5]-joints_state[6];
      angle_error[5]=resRight.angles[0]-joints_state[5];
      angle_error[4]=resRight.angles[1]-joints_state[4];
      angle_error[3]=resRight.angles[2]-joints_state[3];
      angle_error[2]=resRight.angles[3]-joints_state[2];
      angle_error[1]=resRight.angles[4]-joints_state[1];
      angle_error[0]=resRight.angles[5]-joints_state[0];

      for (int i=0;i<12;i++)
      {
        if (fabs(angle_error[i])>5)
        {
          angle_error[i]=0;
        }
      }

      for (int i=0;i<12;i++)
        dangle[i].push_back(angle_error[i]);
      size_t dsize = dangle[0].size();
      if (dsize > window2)
      {
        for (int i=0;i<12;i++)
          dangle[i].pop_front();
        dsize--;
      }
      double x[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
      for (int i=0;i<12;i++)
      {
        for (std::deque<double>::const_iterator it = dangle[i].begin(); it != dangle[i].end(); it++)
        {
          x[i] += *it;
        }
      }
      for (int i=0;i<12;i++)
        f_angle_error[i]=x[i]/dsize;

      fprintf(f_ref,"%f %f %f %f %f %f %f %f %f %f %f %f\n",resRight.angles[5],resRight.angles[4],resRight.angles[3],resRight.angles[2],resRight.angles[1],resRight.angles[0],
        resLeft.angles[5],resLeft.angles[4],resLeft.angles[3],resLeft.angles[2],resLeft.angles[1],resLeft.angles[0]);
      fprintf(f_enc,"%f %f %f %f %f %f %f %f %f %f %f %f\n",joints_state[0],joints_state[1],joints_state[2],joints_state[3],joints_state[4],joints_state[5],
        joints_state[6],joints_state[7],joints_state[8],joints_state[9],joints_state[10],joints_state[11]);
      fprintf(f_err,"%f %f %f %f %f %f %f %f %f %f %f %f\n",f_angle_error[0],f_angle_error[1],f_angle_error[2],f_angle_error[3],f_angle_error[4],f_angle_error[5],
        f_angle_error[6],f_angle_error[7],f_angle_error[8],f_angle_error[9],f_angle_error[10],f_angle_error[11]);

      std_msgs::Int64 left_p_c, right_p_c;
      left_p_c.data=left_p[c];
      right_p_c.data=right_p[c];
      // pubLKneePitch_p.publish(left_p_c);
      // pubLAnklePitch_p.publish(left_p_c);
      // pubLAnkleRoll_p.publish(left_p_c);
      // pubRKneePitch_p.publish(right_p_c);
      // pubRAnklePitch_p.publish(right_p_c);
      // pubRAnkleRoll_p.publish(right_p_c);

      std_msgs::Int64 LKneePitch_p, LAnklePitch_p, LAnkleRoll_p, RKneePitch_p, RAnklePitch_p, RAnkleRoll_p;
      LKneePitch_p.data=stiffness_from_error(f_angle_error[8]);
      LAnklePitch_p.data=stiffness_from_error(f_angle_error[7]);
      LAnkleRoll_p.data=stiffness_from_error(f_angle_error[6]);
      RKneePitch_p.data=stiffness_from_error(f_angle_error[2]);
      RAnklePitch_p.data=stiffness_from_error(f_angle_error[1]);
      RAnkleRoll_p.data=stiffness_from_error(f_angle_error[0]);
      // pubLKneePitch_p.publish(LKneePitch_p);
      // pubLAnklePitch_p.publish(LAnklePitch_p);
      // pubLAnkleRoll_p.publish(LAnkleRoll_p);
      // pubRKneePitch_p.publish(RKneePitch_p);
      // pubRAnklePitch_p.publish(RAnklePitch_p);
      // pubRAnkleRoll_p.publish(RAnkleRoll_p);

      fprintf(f_stiff,"%d %d %d %d %d %d\n",stiffness_from_error(f_angle_error[8]),stiffness_from_error(f_angle_error[7]),stiffness_from_error(f_angle_error[6]),stiffness_from_error(f_angle_error[2]),
        stiffness_from_error(f_angle_error[1]),stiffness_from_error(f_angle_error[0]));


      std_msgs::Float64 X1, Y1;
      X1.data = x1;
      Y1.data = y1;
      pubXController.publish(X1);
      pubYController.publish(Y1);
      c++;
      if (c == resTrajectory.N)
	      break;	
      ros::spinOnce();
      loop_rate.sleep();
    }
    fclose(f);
    fclose(f_ref);
    fclose(f_enc);
    fclose(f_err);
    fclose(f_stiff);
    fclose(f_zmp_error_out);
    Eigen::Matrix<double, 2, 1> last;
    pc_node.get_last_point(last);
    //ROS_INFO("TT %lf %lf", last(0), last(1));
  }
  catch(std::exception &e)
    {
      ROS_INFO("Exception: %s", e.what());
    }
  
  return 0;  
}
