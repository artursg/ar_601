#include "ros/ros.h"
#include "std_msgs/Float64MultiArray.h"
#include "std_msgs/Int64MultiArray.h"
#include "geometry_msgs/PointStamped.h"

std::string uch_topic;
ros::Publisher pubZMP;
ros::Publisher pubMoments;

double KMx, KMy, KFz;
bool Reverse;

void forceCallback(const std_msgs::Int64MultiArray::ConstPtr& msg)
{
  double mx, my;
  if (Reverse == false)
  {
    mx = KMx*(msg->data[0] - msg->data[3]);
    my = KMy*(msg->data[1] - msg->data[2]);
  }
  else
  {
    mx = -KMx*(msg->data[0] - msg->data[3]);
    my = -KMy*(msg->data[1] - msg->data[2]);
  }
  double fz = KFz*(msg->data[0] + msg->data[1] + msg->data[2] + msg->data[3]);
  geometry_msgs::PointStamped moments;
  moments.point.y=mx;
  moments.point.x=my;
  moments.point.z=fz;
  pubMoments.publish(moments);
  geometry_msgs::PointStamped zmpPoint;
  if (fz<1)
  {
  zmpPoint.point.x = 0;
  zmpPoint.point.y = 0;
  zmpPoint.point.z = 0;
  }
  else
  {
  zmpPoint.point.x = mx/fz;
  zmpPoint.point.y = my/fz;
  zmpPoint.point.z = fz;
  }
  pubZMP.publish(zmpPoint);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "force_node");
  ros::NodeHandle n;
  if (!ros::param::get("~uch_topic", uch_topic))
    exit(-1);
  if (!ros::param::get("~KMx", KMx))
    KMx = 0.031;
  if (!ros::param::get("~KMy", KMy))
    KMy = 0.030;
  if (!ros::param::get("~KFz", KFz))
    KFz = 1.705;
  if (!ros::param::get("~Reverse", Reverse))
    Reverse = false;
  pubZMP = n.advertise<geometry_msgs::PointStamped>(uch_topic + "_zmp", 1000);
  pubMoments = n.advertise<geometry_msgs::PointStamped>(uch_topic + "_moments", 1000);
  ros::Subscriber sub = n.subscribe(uch_topic, 1000, forceCallback);
  ros::spin();
  return 0;
}
