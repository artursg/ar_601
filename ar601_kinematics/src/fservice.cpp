#include "ros/ros.h"
#include "ar601_kinematics/FK.h"

extern "C" {
  void right_in_left(double q1, double q2, double q3, double q4, double q5,
  double q6, double q7, double q8, double q9, double q10, double q11, double q12,
  double S[16]);
  
  void left_in_right(double q1, double q2, double q3, double q4, double q5,
  double q6, double q7, double q8, double q9, double q10, double q11, double q12, double S[16]);
}

bool fk(ar601_kinematics::FK::Request  &req,
	ar601_kinematics::FK::Response &res)
{

  double S[16];
  if (req.left)
    left_in_right(req.q1, req.q2, req.q3, req.q4, req.q5, req.q6, req.q7, req.q8, req.q9, req.q10, req.q11, req.q12, S);
  else
    right_in_left(req.q1, req.q2, req.q3, req.q4, req.q5, req.q6, req.q7, req.q8, req.q9, req.q10, req.q11, req.q12, S);
  for (int i = 0; i < 16; i++)
    res.S.push_back(S[i]);
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "fk_server_node");
  ros::NodeHandle n;
  ros::ServiceServer service = n.advertiseService("fk_server", fk);
  ros::spin();
  return 0;
}
