#include "ar601_connection_node.h"

void on_48v(ARPacketT & sendb)
{
  sendb[1409] = sendb[1409] | uint8_t(32);
}

void on_12v(ARPacketT & sendb)
{
  sendb[1409] = sendb[1409] | uint8_t(16);
}

void on_8v_2(ARPacketT & sendb)
{
  sendb[1409] = sendb[1409] | uint8_t(8);
}

void on_8v_1(ARPacketT & sendb)
{
  sendb[1409] = sendb[1409] | uint8_t(4);
}

void on_6v_2(ARPacketT & sendb)
{
  sendb[1409] = sendb[1409] | uint8_t(2);
}
void on_6v_1(ARPacketT & sendb)
{
  sendb[1409] = sendb[1409] | uint8_t(1);
}

void off_48v(ARPacketT & sendb)
{
  sendb[1409] = sendb[1409] & uint8_t(255 - 32);
}

void off_12v(ARPacketT & sendb)
{
  sendb[1409] = sendb[1409] & uint8_t(255 - 16);
}

void off_8v_2(ARPacketT & sendb)
{
  sendb[1409] = sendb[1409] & uint8_t(255 - 8);
}

void off_8v_1(ARPacketT & sendb)
{
  sendb[1409] = sendb[1409] & uint8_t(255 - 4);
}

void off_6v_2(ARPacketT & sendb)
{
  sendb[1409] = sendb[1409] & uint8_t(255 - 2);
}
void off_6v_1(ARPacketT & sendb)
{
  sendb[1409] = sendb[1409] & uint8_t(255 - 1);
}

short get_IContr(ARPacketT & sendb, short num)
{
  return as_int16_t(sendb[device_buffer[num] * 16 + 6],sendb[device_buffer[num] * 16 + 7]);
}

short get_VContr(ARPacketT & sendb, short num)
{
  return as_int16_t(sendb[device_buffer[num] * 16 + 4], sendb[device_buffer[num] * 16 + 5]);
}

short get_U(ARPacketT & sendb, short num)
{
  return as_int16_t(sendb[device_buffer[num] * 16 + 4], sendb[device_buffer[num] * 16 + 5]);
}

short get_I(ARPacketT & sendb, short num)
{
  return as_int16_t(sendb[device_buffer[num] * 16 + 6], sendb[device_buffer[num] * 16 + 7]);
}

short get_6V_1_U(ARPacketT & sendb)
{
  return as_int16_t(sendb[88*16], sendb[88*16 + 1]);
}

short get_6V_2_U(ARPacketT & sendb)
{
  return as_int16_t(sendb[88*16 + 2], sendb[88*16 + 3]);
}

short get_8V_1_U(ARPacketT & sendb)
{
  return as_int16_t(sendb[88*16 + 3], sendb[88*16 + 4]);
}

short get_8V_2_U(ARPacketT & sendb)
{
  return as_int16_t(sendb[88*16 + 5], sendb[88*16 + 6]);
}

short get_12V_U(ARPacketT & sendb)
{
  return as_int16_t(sendb[88*16 + 7], sendb[88*16 + 8]);
}

short get_48V_U(ARPacketT & sendb)
{
  return as_int16_t(sendb[88*16 + 9], sendb[88*16 + 10]);
}

short get_6V_1_I(ARPacketT & sendb)
{
  return as_int16_t(sendb[88*16 + 11], sendb[88*16 + 12]);
}

short get_6V_2_I(ARPacketT & sendb)
{
  return as_int16_t(sendb[88*16 + 13], sendb[88*16 + 14]);
}

short get_8V_1_I(ARPacketT & sendb)
{
  return as_int16_t(sendb[88*16 + 15], sendb[88*16 + 16]);
}

short get_8V_2_I(ARPacketT & sendb)
{
  return as_int16_t(sendb[88*16 + 17], sendb[88*16 + 18]);
}

short get_12V_I(ARPacketT & sendb)
{
  return as_int16_t(sendb[88*16 + 19], sendb[88*16 + 20]);
}

short get_48V_I(ARPacketT & sendb)
{
  return as_int16_t(sendb[88*16 + 21], sendb[88*16 + 22]);
}

float get_POS(ARPacketT & sendb, short num)
{
  int16_t r = as_int16_t(sendb[device_buffer[num] * 16 + 2], sendb[device_buffer[num] * 16 + 3]); 
  if (device_reverse[num])
    return -r*1.0/100;
  else
    return r*1.0/100;
}

float get_POS_raw(ARPacketT & sendb, short num)
{
  int16_t r = as_int16_t(sendb[device_buffer[num] * 16 + 2], sendb[device_buffer[num] * 16 + 3]); 
  return r*1.0/100;
}

void set_POS(ARPacketT & sendb, short num, float pvalue)
{
  int16_t value = pvalue*100;
  int16_t min = device_minpos[num];
  int16_t max = device_maxpos[num];
  if (device_reverse[num])
    {
      value = -value;
    }
  if ((value <= min) || (value >= max))
    {
      ROS_INFO("Hit limit with at %d with %f (%d) while max: %d and min: %d.\n", num, pvalue, value, max, min);
      return;
    }
  uint8_t byte_1, byte_2;
  as_2uint8_t(value, byte_1, byte_2);
  sendb[device_buffer[num] * 16 + 3] = byte_2;
  sendb[device_buffer[num] * 16 + 2] = byte_1;
}

void set_ILIM(ARPacketT & sendb, short num, short value)
{
  uint8_t byte_1, byte_2;
  as_2uint8_t(value, byte_1, byte_2);
  sendb[device_buffer[num] * 16 + 7] = byte_2;
  sendb[device_buffer[num] * 16 + 6] = byte_1;
}

short get_STIFF(ARPacketT & sendb, short num)
{
  return as_int16_t(sendb[device_buffer[num] * 16 + 8], sendb[device_buffer[num] * 16 + 9]);
}

void set_STIFF(ARPacketT & sendb, short num, short value)
{
  uint8_t byte_1, byte_2;
  as_2uint8_t(value, byte_1, byte_2);
  sendb[device_buffer[num] * 16 + 9] = byte_2;
  sendb[device_buffer[num] * 16 + 8] = byte_1;
}

short get_DUMP(ARPacketT & sendb, short num)
{
  return as_int16_t(sendb[device_buffer[num] * 16 + 10], sendb[device_buffer[num] * 16 + 11]);
}

void set_DUMP(ARPacketT & sendb, short num, short value)
{
  uint8_t byte_1, byte_2;
  as_2uint8_t(value, byte_1, byte_2);
  sendb[device_buffer[num] * 16 + 11] = byte_2;
  sendb[device_buffer[num] * 16 + 10] = byte_1;
}

uint8_t get_MOT_STAT(ARPacketT & sendb, short num)
{
  return sendb[device_buffer[num] * 16 + 1];
}

float get_POSMIN(ARPacketT & sendb, short num)
{
  if (device_reverse[num] > 0)
    return -as_int16_t(sendb[device_buffer[num] * 16 + 14], sendb[device_buffer[num] * 16 + 15]);
  else
    return as_int16_t(sendb[device_buffer[num] * 16 + 12], sendb[device_buffer[num] * 16 + 13]);
}

void set_POSMIN(ARPacketT & sendb, short num, int16_t pvalue)
{
  short value = pvalue;
  uint8_t byte_1, byte_2;
  as_2uint8_t(value, byte_1, byte_2);
  sendb[device_buffer[num] * 16 + 13] = byte_2;
  sendb[device_buffer[num] * 16 + 12] = byte_1;
  device_minpos[num] = pvalue;
}

float get_POSMAX(ARPacketT & sendb, short num)
{
  if (device_reverse[num])
    {
      return -as_int16_t(sendb[device_buffer[num] * 16 + 12], sendb[device_buffer[num] * 16 + 13])*1.0/100;
    }
  else
    return as_int16_t(sendb[device_buffer[num] * 16 + 14], sendb[device_buffer[num] * 16 + 15])*1.0/100;
}

void set_POSMAX(ARPacketT & sendb, short num, int16_t pvalue)
{
  int16_t value = pvalue;
  uint8_t byte_1, byte_2;
  as_2uint8_t(value, byte_1, byte_2);
  sendb[device_buffer[num] * 16 + 15] = byte_2;
  sendb[device_buffer[num] * 16 + 14] = byte_1;
  device_maxpos[num] = pvalue;
}

short get_FX(ARPacketT & sendb, short num)
{
  return as_int16_t(sendb[device_buffer[num] * 16 + 2], sendb[device_buffer[num] * 16 + 3]);
}

short get_FY(ARPacketT & sendb, short num)
{
  return as_int16_t(sendb[device_buffer[num] * 16 + 4], sendb[device_buffer[num] * 16 + 5]);
}

short get_FZ(ARPacketT & sendb, short num)
{
  return as_int16_t(sendb[device_buffer[num] * 16 + 6], sendb[device_buffer[num] * 16 + 7]);
}

short get_UCH0(ARPacketT & sendb, short num)
{
  return as_int16_t(sendb[device_buffer[num] * 16 + 8], sendb[device_buffer[num] * 16 + 9]);
}

short get_UCH1(ARPacketT & sendb, short num)
{
  return as_int16_t(sendb[device_buffer[num] * 16 + 10], sendb[device_buffer[num] * 16 + 11]);
}

short get_UCH2(ARPacketT & sendb, short num)
{
  return as_int16_t(sendb[device_buffer[num] * 16 + 12], sendb[device_buffer[num] * 16 + 13]);
}

short get_UCH3(ARPacketT & sendb, short num)
{
  return as_int16_t(sendb[device_buffer[num] * 16 + 14], sendb[device_buffer[num] * 16 + 15]);
}

void set_UCH0(ARPacketT & sendb, short num, short uch)
{
  uint8_t byte_1, byte_2;
  as_2uint8_t(uch, byte_1, byte_2);
  sendb[device_buffer[num] * 16 + 8] = byte_1;
  sendb[device_buffer[num] * 16 + 9] = byte_2;  
}

void set_UCH1(ARPacketT & sendb, short num, short uch)
{
  uint8_t byte_1, byte_2;
  as_2uint8_t(uch, byte_1, byte_2);
  sendb[device_buffer[num] * 16 + 10] = byte_1;
  sendb[device_buffer[num] * 16 + 11] = byte_2;  
}

void set_UCH2(ARPacketT & sendb, short num, short uch)
{
  uint8_t byte_1, byte_2;
  as_2uint8_t(uch, byte_1, byte_2);
  sendb[device_buffer[num] * 16 + 12] = byte_1;
  sendb[device_buffer[num] * 16 + 13] = byte_2;  
}

void set_UCH3(ARPacketT & sendb, short num, short uch)
{
  uint8_t byte_1, byte_2;
  as_2uint8_t(uch, byte_1, byte_2);
  sendb[device_buffer[num] * 16 + 14] = byte_1;
  sendb[device_buffer[num] * 16 + 15] = byte_2;  
}

float get_GyroX(ARPacketT & buffer, short num)
{
  return as_int16_t(buffer[device_buffer[num] * 16 + 2], buffer[device_buffer[num] * 16 + 3])/100.0;
}

float get_GyroY(ARPacketT & buffer, short num)
{
  return as_int16_t(buffer[device_buffer[num] * 16 + 4], buffer[device_buffer[num] * 16 + 5])/100.0;
}

float get_GyroZ(ARPacketT & buffer, short num)
{
  return as_int16_t(buffer[device_buffer[num] * 16 + 6], buffer[device_buffer[num] * 16 + 7])/100.0;
}

float get_MagX(ARPacketT & buffer, short num)
{
  return as_int16_t(buffer[device_buffer[num] * 16 + 8], buffer[device_buffer[num] * 16 + 9])/100.0;
}

float get_MagY(ARPacketT & buffer, short num)
{
  return as_int16_t(buffer[device_buffer[num] * 16 + 10], buffer[device_buffer[num] * 16 + 11])/100.0;
}

float get_MagZ(ARPacketT & buffer, short num)
{
  return as_int16_t(buffer[device_buffer[num] * 16 + 12], buffer[device_buffer[num] * 16 + 13])/100.0;
}

float get_Temperature(ARPacketT & buffer, short num)
{
  return as_int16_t(buffer[device_buffer[num] * 16 + 14], buffer[device_buffer[num] * 16 + 15])/100.0;
}

float get_Yaw(ARPacketT & buffer, short num)
{
  return as_int16_t(buffer[device_buffer[num] * 16 + 2], buffer[device_buffer[num] * 16 + 3])/100.0;
}

float get_Pitch(ARPacketT & buffer, short num)
{
  return as_int16_t(buffer[device_buffer[num] * 16 + 4], buffer[device_buffer[num] * 16 + 5])/100.0;
}

float get_Roll(ARPacketT & buffer, short num)
{
  return as_int16_t(buffer[device_buffer[num] * 16 + 6], buffer[device_buffer[num] * 16 + 7])/100.0;
}

float get_G_AccX(ARPacketT & buffer, short num)
{
  return as_int16_t(buffer[device_buffer[num] * 16 + 8], buffer[device_buffer[num] * 16 + 9])/100.0;
}

float get_G_AccY(ARPacketT & buffer, short num)
{
  return as_int16_t(buffer[device_buffer[num] * 16 + 10], buffer[device_buffer[num] * 16 + 11])/100.0;
}

float get_G_AccZ(ARPacketT & buffer, short num)
{
  return as_int16_t(buffer[device_buffer[num] * 16 + 12], buffer[device_buffer[num] * 16 + 13])/100.0;
}

float get_Barometer(ARPacketT & buffer, short num)
{
  return as_int16_t(buffer[device_buffer[num] * 16 + 14], buffer[device_buffer[num] * 16 + 15])/100.0;
}

void MOT_CENTER(ARPacketT & sendb, short num)
{
  sendb[device_buffer[num] * 16 + 7] = sendb[device_buffer[num] * 16 + 3];
  sendb[device_buffer[num] * 16 + 6] = sendb[device_buffer[num] * 16 + 2];
}

void MOT_STOP(ARPacketT & sendb, short num)
{
  sendb[device_buffer[num] * 16 + 1] = sendb[device_buffer[num] * 16 + 1] & uint8_t(255 - 3);
  sendb[device_buffer[num] * 16 + 1] = sendb[device_buffer[num] * 16 + 1] | uint8_t(1);
}

void MOT_TRACE(ARPacketT & sendb, short num)
{
  sendb[device_buffer[num] * 16 + 1] = sendb[device_buffer[num] * 16 + 1] & uint8_t(255 - 3);
  sendb[device_buffer[num] * 16 + 1] = sendb[device_buffer[num] * 16 + 1] | uint8_t(3);
}

void MOT_RELAX(ARPacketT & sendb, short num)
{
  sendb[device_buffer[num] * 16 + 1] = sendb[device_buffer[num] * 16 + 1] & uint8_t(255 - 3);
  sendb[device_buffer[num] * 16 + 1] = sendb[device_buffer[num] * 16 + 1] | uint8_t(2);
}

void MOT_STOP_BR(ARPacketT & sendb, short num)
{
  sendb[device_buffer[num] * 16 + 1] = sendb[device_buffer[num] * 16 + 1] & uint8_t(255 - 3);
}

void set_REV(ARPacketT & sendb, short num, short value)
{
  if (value > 0)
    {
      device_reverse[num] = 1;
    }
  else
    {
      device_reverse[num] = 0;
    }
}
 
void set_DEVICE_BUFFER(ARPacketT & sendb, int num, int buff_adr)
{
  sendb[buff_adr * 16] = num;
}

void print_buffer_debug(ARPacketT & sendb, int device)
{
  int8_t buffer[16];
  for (int i = 0; i < 16; i++)
    {
      buffer[i] = sendb[device_buffer[device]*16 + i];
    }
  ROS_INFO("B: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7], buffer[8], buffer[9], buffer[10], buffer[11], buffer[12], buffer[13], buffer[14], buffer[15]);
}

template<typename T1>
void fill_from_ini(boost::property_tree::ptree &tree, std::map<T1, std::string> & map, const char * section ){
  map.clear();
  BOOST_FOREACH(boost::property_tree::ptree::value_type &v, tree.get_child(section)) {
    T1 key = static_cast<T1>(atoi(v.first.data()));
    std::string value = v.second.data();
    map[key] = value;
  }
}

template<typename T1, typename T2>
void fill_from_ini(boost::property_tree::ptree &tree, std::map<T1, T2> & map, const char * section ){
  map.clear();
  BOOST_FOREACH(boost::property_tree::ptree::value_type &v, tree.get_child(section)) {
    T1 key = static_cast<T1>(atoi( v.first.data() ));
    T2 value = static_cast<T2>(atoi( v.second.data().c_str() ));
    map[key] = value;
  }
}

void load_ini()
{
  try
    {
      std::string full_path = ros::package::getPath("ar601_connection");
      std::cout << "ini path is : " << full_path << std::endl;
      boost::property_tree::ptree pt;
      boost::property_tree::ini_parser::read_ini(full_path + INI_LOCATION, pt);
      /* Read devices ids */
      fill_from_ini(pt, devices, "DEVICE_NOMB");
      fill_from_ini(pt, device_kp, "STIF_MOTOR");
      fill_from_ini(pt, device_ki, "DUMP_MOTOR");
      fill_from_ini(pt, device_ilim, "ILIM_MOTOR");
      fill_from_ini(pt, device_buffer, "DEVICE_NOMB_BUFFER");
      fill_from_ini(pt, device_maxpos, "MAXPOS_MOTOR");
      fill_from_ini(pt, device_minpos, "MINPOS_MOTOR");
      fill_from_ini(pt, device_type, "DEVICE_TYPE");   
      device_reverse.clear();
      BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child("REVERS_MOTOR"))
	{
	  int key = static_cast<int>(atoi( v.first.data() ));
	  bool value = strcmp(v.second.data().c_str(), "True") == 0;
	  device_reverse[key] = value;
	}
      fill_from_ini(pt, device_names, "DEVICE_NAME");
      /* Tensor sensor ini */
      uch_left_foot.uch0 = pt.get<int16_t>("FORCE_SENSOR_LEFT_FOOT.UCH0");
      uch_left_foot.uch1 = pt.get<int16_t>("FORCE_SENSOR_LEFT_FOOT.UCH1");
      uch_left_foot.uch2 = pt.get<int16_t>("FORCE_SENSOR_LEFT_FOOT.UCH2");
      uch_left_foot.uch3 = pt.get<int16_t>("FORCE_SENSOR_LEFT_FOOT.UCH3");
      
      uch_right_foot.uch0 = pt.get<int16_t>("FORCE_SENSOR_RIGHT_FOOT.UCH0");
      uch_right_foot.uch1 = pt.get<int16_t>("FORCE_SENSOR_RIGHT_FOOT.UCH1");
      uch_right_foot.uch2 = pt.get<int16_t>("FORCE_SENSOR_RIGHT_FOOT.UCH2");
      uch_right_foot.uch3 = pt.get<int16_t>("FORCE_SENSOR_RIGHT_FOOT.UCH3");
    }
  catch(std::exception &e)
    {
      printf("Fatal error with ini file: %s\n", e.what());
      exit(-1);
    }
}

void publish_force_sensor(ros::Publisher& publisher, ARPacketT & packet, short device, force_coefficients_t & coeff)
{
  double Mx = get_FX(packet, device);
  double My = get_FY(packet, device);
  double Fz = get_FZ(packet, device);
  std_msgs::Float64MultiArray force_msg;
  force_msg.data.push_back(Mx);
  force_msg.data.push_back(My);
  force_msg.data.push_back(Fz);
  publisher.publish(force_msg);
}

void publish_force_sensor_uch(ros::Publisher& publisher, ARPacketT & packet, short device)
{
  int16_t uch0 = get_UCH0(packet, device);
  int16_t uch1 = get_UCH1(packet, device);
  int16_t uch2 = get_UCH2(packet, device);
  int16_t uch3 = get_UCH3(packet, device);
  std_msgs::Int64MultiArray force_uch;
  force_uch.data.push_back(uch0);
  force_uch.data.push_back(uch1);
  force_uch.data.push_back(uch2);
  force_uch.data.push_back(uch3);
  publisher.publish(force_uch);
}

void publish_packet(ARPacketT & packet)
{
  sensor_msgs::JointState joint_msgs, joint_msgs_raw;
  sensor_msgs::Imu imu_msg;
  sensor_msgs::Imu imu_msg_2;
  ar601_messages::JointStatus joint_status_msgs; 
  std::map<std::string, double> joint_positions;
  for(it_type iterator = devices.begin(); iterator != devices.end(); iterator++) 
    {
      int device = iterator->first;
      if (device_type.find(device) != device_type.end() )
	{
	  int type = device_type[device];
	  int buffer_n = device_buffer[device];
	  switch (type)
	    {
	    case 0:
	      {
		joint_positions[device_names[device]] = get_POS(packet, device);
		joint_msgs.name.push_back(device_names[device]);
		joint_msgs.position.push_back(get_POS(packet, device));
		joint_msgs_raw.name.push_back(device_names[device]);
		joint_msgs_raw.position.push_back(get_POS_raw(packet, device));
		std_msgs::Int64 voltage;
		voltage.data = get_U(packet, device);
		std_msgs::Int64 load;
		load.data = get_I(packet, device);
		std_msgs::Int64 kp;
		kp.data = get_STIFF(packet, device);
		std_msgs::Int64 ki;
		ki.data = get_DUMP(packet, device);
		std_msgs::Float64 maximum;
		maximum.data = get_POSMAX(packet, device);
		std_msgs::Float64 minimum;
		minimum.data = get_POSMIN(packet, device);
		std_msgs::Bool over_maximum;
		over_maximum.data = false;
		std_msgs::Bool over_minimum;
		over_minimum.data = false;
		std_msgs::Int8 status;
		status.data = get_MOT_STAT(packet, device) & 0xC0;
		std_msgs::Bool torque_control;
		torque_control.data = false;
		joint_status_msgs.voltage.push_back(voltage);
		joint_status_msgs.load.push_back(load);
		joint_status_msgs.kp.push_back(kp);
		joint_status_msgs.ki.push_back(ki);
		joint_status_msgs.maximum.push_back(maximum);
		joint_status_msgs.minimum.push_back(minimum);
		joint_status_msgs.over_minimum.push_back(over_minimum);
		joint_status_msgs.over_maximum.push_back(over_maximum);
		joint_status_msgs.status.push_back(status);
		joint_status_msgs.torque_control.push_back(torque_control);
	      }
	      break;
	    case 1:
	      {
		imu_msg.orientation_covariance[0] = -1;
		geometry_msgs::Vector3 v;
		v.x = get_Yaw(packet, 13);
		v.y = get_Pitch(packet, 13);
		v.z = get_Roll(packet, 13);
    imu_msg.angular_velocity = v;
		imu_msg.angular_velocity_covariance[0] = -1;
		geometry_msgs::Vector3 a;
		a.x = get_G_AccX(packet, 13);
		a.y = get_G_AccY(packet, 13);
		a.z = get_G_AccZ(packet, 13);
		imu_msg.linear_acceleration = a;
		imu_msg.linear_acceleration_covariance[0] = -1;
    imu_msg_2.orientation_covariance[0] = -1;
    geometry_msgs::Vector3 v2;
    v2.x = get_Yaw(packet, 14);
    v2.y = get_Pitch(packet, 14);
    v2.z = get_Roll(packet, 14);
    imu_msg_2.angular_velocity = v2;
    imu_msg_2.angular_velocity_covariance[0] = -1;
    geometry_msgs::Vector3 a2;
    a2.x = get_G_AccX(packet, 14);
    a2.y = get_G_AccY(packet, 14);
    a2.z = get_G_AccZ(packet, 14);
    imu_msg_2.linear_acceleration = a2;
    imu_msg_2.linear_acceleration_covariance[0] = -1;
	      }
	      break;
	    case 2:
	      {
		publish_force_sensor(force_lfoot_pub, packet, device, foot_coefficients);
		publish_force_sensor_uch(force_uch_lfoot_pub, packet, device);
	      }
	      break;
	    case 3:
	      {	
		publish_force_sensor(force_rfoot_pub, packet, device, foot_coefficients);
		publish_force_sensor_uch(force_uch_rfoot_pub, packet, device);
	      }
	      break;
	    case 4:
	      {	
		publish_force_sensor(force_rarm_pub, packet, device, arm_coefficients);
		publish_force_sensor_uch(force_uch_rarm_pub, packet, device);
	      }
	      break;
	    case 5:
	      {	
		publish_force_sensor(force_larm_pub, packet, device, arm_coefficients);
		publish_force_sensor_uch(force_uch_larm_pub, packet, device);
	      }
	      break;
	    };
	}
    }
  ar601_messages::Power power_msgs;
  power_msgs.load48.data = get_48V_U(packet);
  power_msgs.voltage48.data = get_48V_I(packet);
  // 12v
  power_msgs.load12.data = get_12V_U(packet);
  power_msgs.voltage12.data = get_12V_I(packet);
  // 8v
  power_msgs.load8_2.data = get_8V_2_U(packet);
  power_msgs.voltage8_2.data = get_8V_2_I(packet);
  power_msgs.load8_1.data = get_8V_1_U(packet);
  power_msgs.voltage8_1.data = get_8V_1_I(packet);
  // 6v
  power_msgs.load6_2.data = get_6V_1_U(packet);
  power_msgs.voltage6_2.data = get_6V_1_I(packet);
  power_msgs.load6_1.data = get_6V_1_U(packet);
  power_msgs.voltage6_1.data = get_6V_1_I(packet);
  // publish 
  joint_state_pub.publish(joint_msgs);
  joint_state_raw_pub.publish(joint_msgs_raw);
  joint_status_pub.publish(joint_status_msgs);
  imu_pub.publish(imu_msg);
  imu2_pub.publish(imu_msg_2);
  power_pub.publish(power_msgs); 
  rsp->publishTransforms(joint_positions, ros::Time::now(), "");
}

void set_force_uch(ARPacketT & sendb, short device, tensor_uch& defaults)
{
  ROS_INFO("UCH for %d - %d %d %d %d", device, defaults.uch0, defaults.uch1, defaults.uch2, defaults.uch3);
  set_UCH0(sendb, device, defaults.uch0);
  set_UCH1(sendb, device, defaults.uch1);
  set_UCH2(sendb, device, defaults.uch2);
  set_UCH3(sendb, device, defaults.uch3);
}

void force_sensor_reset(size_t device, tensor_uch& defaults)
{
  short uch0 = get_UCH0(recv_buf, device) + defaults.uch0;
  short uch1 = get_UCH1(recv_buf, device) + defaults.uch1;
  short uch2 = get_UCH2(recv_buf, device) + defaults.uch2;
  short uch3 = get_UCH3(recv_buf, device) + defaults.uch3;
  defaults.uch0 = uch0;
  defaults.uch1 = uch1;
  defaults.uch2 = uch2;
  defaults.uch3 = uch3;
  ROS_INFO("UCH for %zu - %d %d %d %d", device, uch0, uch1, uch2, uch3);
  set_UCH0(send_buf, device, uch0);
  set_UCH1(send_buf, device, uch1);
  set_UCH2(send_buf, device, uch2);
  set_UCH3(send_buf, device, uch3);
}

void reset_lfoot_sensor()
{
  force_sensor_reset(LEFT_FOOT_DEVICE, uch_left_foot);
}

void reset_rfoot_sensor()
{
  force_sensor_reset(RIGHT_FOOT_DEVICE, uch_right_foot);
}

void reset_larm_sensor()
{
  force_sensor_reset(LEFT_ARM_DEVICE, uch_left_arm);
}

void reset_rarm_sensor()
{
  force_sensor_reset(RIGHT_ARM_DEVICE, uch_right_arm);
}


bool reset_all_force_sensors(std_srvs::Empty::Request & req, std_srvs::Empty::Response & res)
{
  reset_lfoot_sensor();
  reset_rfoot_sensor();
  reset_larm_sensor();
  reset_rarm_sensor();
  return true;
}

void buffers_from_ini(ARPacketT & sendb)
{
  typedef std::map<int, int>::iterator it_type;
  for(it_type iterator = devices.begin(); iterator != devices.end(); iterator++) 
    {
      int device = iterator->first;
      if (device_type.find(device) != device_type.end() )
	{
	  int type = device_type[device];
	  int buffer_n = device_buffer[device];
	  set_DEVICE_BUFFER(sendb, device, buffer_n);
	  switch (type)
	    {
	    case 0:
	      {
		MOT_STOP_BR(sendb, device);
		set_STIFF(sendb, device, device_kp[device]);
		set_DUMP(sendb, device, device_ki[device]);
		set_POSMAX(sendb, device, device_maxpos[device]);
		set_POSMIN(sendb, device, device_minpos[device]);
		set_REV(sendb, device, device_reverse[device]);
		set_ILIM(sendb, device, device_ilim[device]);
	      }
	      break;
	    case 2:
	      {
		set_force_uch(sendb, device, uch_left_foot);
		LEFT_FOOT_DEVICE = device;
	      }
	      break;
	    case 3:
	      {
		set_force_uch(sendb, device, uch_right_foot);
		RIGHT_FOOT_DEVICE = device;
	      }
	      break;
	    case 4:
	      {
		set_force_uch(sendb, device, uch_left_arm);
		LEFT_ARM_DEVICE = device;
	      }
	      break;
	    case 5:
	      {
		set_force_uch(sendb, device, uch_right_arm);
		RIGHT_ARM_DEVICE = device;
	      }
	      break;
	    };
	}
    }
}

int main(int argc, char ** argv)
{
  load_ini();
  boost::asio::io_service io_service;
  for (size_t i = 0; i < PACKET_SIZE; i++)
    {
      send_buf[i] = recv_buf[i] = 0;
    }
  // ROS
  ros::init(argc, argv, "ar601_connection");
  ros::NodeHandle n;
  joint_state_pub = n.advertise<sensor_msgs::JointState>("joint_states", PUBLISHING_RATE);
  joint_state_raw_pub = n.advertise<sensor_msgs::JointState>("joint_states_raw", PUBLISHING_RATE);
  joint_status_pub = n.advertise<ar601_messages::JointStatus>("joint_status", PUBLISHING_RATE);
  imu_pub = n.advertise<sensor_msgs::Imu>("imu", PUBLISHING_RATE);
  imu2_pub = n.advertise<sensor_msgs::Imu>("imu2", PUBLISHING_RATE);
  temperature_pub = n.advertise<sensor_msgs::Temperature>("temperature", PUBLISHING_RATE);
  magnetic_field_pub = n.advertise<sensor_msgs::MagneticField>("magnetic_field", PUBLISHING_RATE);
  pressure_pub  = n.advertise<sensor_msgs::FluidPressure>("pressure", PUBLISHING_RATE);
  power_pub = n.advertise<ar601_messages::Power >("power/lines", PUBLISHING_RATE);
  force_rfoot_pub = n.advertise<std_msgs::Float64MultiArray >("force/right_foot", PUBLISHING_RATE);
  force_lfoot_pub = n.advertise<std_msgs::Float64MultiArray >("force/left_foot", PUBLISHING_RATE);
  force_rarm_pub = n.advertise<std_msgs::Float64MultiArray >("force/right_arm", PUBLISHING_RATE);
  force_larm_pub = n.advertise<std_msgs::Float64MultiArray >("force/left_arm", PUBLISHING_RATE);
  force_uch_rfoot_pub = n.advertise<std_msgs::Int64MultiArray >("force/right_foot_uch", PUBLISHING_RATE);
  force_uch_lfoot_pub = n.advertise<std_msgs::Int64MultiArray >("force/left_foot_uch", PUBLISHING_RATE);
  force_uch_rarm_pub = n.advertise<std_msgs::Int64MultiArray >("force/right_arm_uch", PUBLISHING_RATE);
  force_uch_larm_pub = n.advertise<std_msgs::Int64MultiArray >("force/left_arm_uch", PUBLISHING_RATE);
  int joint_id = 20;
  power_sub p48(n, 48);
  power_sub p12(n, 12);
  power_sub p82(n, 82);
  power_sub p81(n, 81);
  power_sub p62(n, 62);
  power_sub p61(n, 61);
  // KDL Tree
  std::string robot_desc_string;
  n.param("robot_description", robot_desc_string, std::string());
  if (!kdl_parser::treeFromString(robot_desc_string, robot_tree)){
    ROS_ERROR("Failed to construct kdl tree");
  }
  // Robot state pulisher 
  rsp = new robot_state_publisher::RobotStatePublisher(robot_tree);
  // Services
  ros::ServiceServer service = n.advertiseService("ar601/reset_all_force_sensors", reset_all_force_sensors);
  // Make joint controls
  std::vector<joint_control *> controls;
  for(it_type iterator = devices.begin(); iterator != devices.end(); iterator++) 
    {
      int device = iterator->first;
      if (device_type.find(device) != device_type.end() && device_type[device] == 0)
	{
   	  controls.push_back(new joint_control(n, device));
   	}
    }
  udp::socket socket(io_service);
  socket.open(udp::v4());
  udp::endpoint robot_endpoint = udp::endpoint(boost::asio::ip::address::from_string(robot_ip), PORT);
  udp::endpoint remote_endpoint;
  buffers_from_ini(send_buf);
  udp_server server(io_service);
  boost::thread bt(boost::bind(&boost::asio::io_service::run, &io_service));
  on_12v(send_buf);
  ros::Rate rate(250);
  bool init = false;
  while (ros::ok())
    {
      try
	{
	  if (!init)
	    {
	      printf("Powering up...\n");
	      on_48v(send_buf);
	      socket.send_to(boost::asio::buffer(send_buf), robot_endpoint);
	      rate.sleep();
	      on_8v_2(send_buf);
	      socket.send_to(boost::asio::buffer(send_buf), robot_endpoint);
	      rate.sleep();
	      on_8v_1(send_buf);
	      socket.send_to(boost::asio::buffer(send_buf), robot_endpoint);
	      rate.sleep();
	      on_6v_2(send_buf);
	      socket.send_to(boost::asio::buffer(send_buf), robot_endpoint);
	      rate.sleep();
	      on_6v_1(send_buf);
	      init = true;
	      printf("Powering up complete.\n");
	      continue;
	    }
	  socket.send_to(boost::asio::buffer(send_buf), robot_endpoint);
	  ros::spinOnce();
	  rate.sleep();
	}
      catch(std::exception &e) {
	printf("Caught error: %s", e.what());
      }
    }
  delete rsp;
  return 0;
}
