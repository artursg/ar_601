#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Float64.h"
#include "ar601_kinematics/IK.h"

ros::Publisher pubLHipYaw, pubLHipRoll, pubLHipPitch, pubLKneePitch, pubLAnklePitch, pubLAnkleRoll, pubRHipYaw, pubRHipRoll, pubRHipPitch, pubRKneePitch, pubRAnklePitch, pubRAnkleRoll;
ros::ServiceClient ik_service;

void commandCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
  ar601_kinematics::IK::Request req;
  ar601_kinematics::IK::Response resLeft, resRight;
  req.left = true;
  req.x = 0;
  req.y = 0.088;
  req.z = 0;
  req.phi_x = 0;
  req.phi_y = 0;
  req.phi_z = 0;
  req.x_t = msg->linear.x;
  req.y_t = msg->linear.y;
  req.z_t = msg->linear.z;
  req.phi_x_t = msg->angular.x;
  req.phi_y_t = msg->angular.y;
  req.phi_z_t = msg->angular.z;    
  ik_service.call(req, resLeft);
  req.left = false;
  req.x = 0;
  req.y = -0.088;
  req.z = 0;
  req.phi_x = 0;
  req.phi_y = 0;
  req.phi_z = 0;
  req.x_t = msg->linear.x;
  req.y_t = msg->linear.y;
  req.z_t = msg->linear.z;
  req.phi_x_t = msg->angular.x;
  req.phi_y_t = msg->angular.y;
  req.phi_z_t = msg->angular.z;    
  ik_service.call(req, resRight);
  std_msgs::Float64 data[12];
  data[0].data = resLeft.angles[0];
  data[1].data = resLeft.angles[1];
  data[2].data = resLeft.angles[2];
  data[3].data = resLeft.angles[3];
  data[4].data = resLeft.angles[4];
  data[5].data = resLeft.angles[5];
  data[6].data = resRight.angles[0];
  data[7].data = resRight.angles[1];
  data[8].data = resRight.angles[2];
  data[9].data = resRight.angles[3];
  data[10].data = resRight.angles[4];
  data[11].data = resRight.angles[5];
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
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "cog_move");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("cog_command", 1000, commandCallback);
  ik_service = n.serviceClient<ar601_kinematics::IK>("ik_server");
  pubLHipYaw = n.advertise<std_msgs::Float64>("control/joint_12/command", 1000);
  pubLHipRoll = n.advertise<std_msgs::Float64>("control/joint_11/command", 1000);
  pubLHipPitch = n.advertise<std_msgs::Float64>("control/joint_10/command", 1000);
  pubLKneePitch = n.advertise<std_msgs::Float64>("control/joint_9/command", 1000);
  pubLAnklePitch = n.advertise<std_msgs::Float64>("control/joint_8/command", 1000);
  pubLAnkleRoll = n.advertise<std_msgs::Float64>("control/joint_7/command", 1000);
  pubRHipYaw = n.advertise<std_msgs::Float64>("control/joint_6/command", 1000);
  pubRHipRoll = n.advertise<std_msgs::Float64>("control/joint_5/command", 1000);
  pubRHipPitch = n.advertise<std_msgs::Float64>("control/joint_4/command", 1000);
  pubRKneePitch = n.advertise<std_msgs::Float64>("control/joint_3/command", 1000);
  pubRAnklePitch = n.advertise<std_msgs::Float64>("control/joint_2/command", 1000);
  pubRAnkleRoll = n.advertise<std_msgs::Float64>("control/joint_1/command", 1000);

  ros::spin();

  return 0;
}
