#include "ros/ros.h"
#include "ar601_messages/IK.h"

extern "C" {
  void ik_right_12(double x, double y, double z, double phi_x, double phi_y,
                 double phi_z, double x_t, double y_t, double z_t, double
                 phi_x_t, double phi_y_t, double phi_z_t, double angles[6]);
  void ik_left_12(double x, double y, double z, double phi_x, double phi_y, double
                phi_z, double x_t, double y_t, double z_t, double phi_x_t,
                double phi_y_t, double phi_z_t, double angles[6]);
}

bool ik(ar601_messages::IK::Request  &req,
	ar601_messages::IK::Response &res)
{

  double angles[6];
  if (req.left)
    ik_left_12(req.x, req.y, req.z, req.phi_x, req.phi_y, req.phi_z, req.x_t, req.y_t, req.z_t, req.phi_x_t, req.phi_y_t,
req.phi_z_t, angles);
  else
    ik_right_12(req.x, req.y, req.z, req.phi_x, req.phi_y, req.phi_z, req.x_t, req.y_t, req.z_t, req.phi_x_t, req.phi_y_t,
req.phi_z_t, angles);
  for (int i = 0; i < 6; i++)
    res.angles.push_back(angles[i] * 57.2958);
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "ik_server_node");
  ros::NodeHandle n;
  ros::ServiceServer service = n.advertiseService("ik_server", ik);
  ros::spin();
  return 0;
}
