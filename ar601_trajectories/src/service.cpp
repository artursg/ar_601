#include "ros/ros.h"
#include "ros/package.h"
#include "ar601_trajectories/GetTrajectory.h"

extern "C" {
  #include "main_trajectory.h"
  #include "main_emxAPI.h"
}

void load_from_file(const std::string & filename, emxArray_real_T *x_left, emxArray_real_T *y_left, emxArray_real_T *z_left, emxArray_real_T *theta_left, emxArray_real_T *x_right, emxArray_real_T *y_right, emxArray_real_T *z_right, emxArray_real_T *theta_right, emxArray_real_T *zmp_x, emxArray_real_T *zmp_y, emxArray_real_T *theta_torso, double &L)
{
  L = 0;
  FILE * f = fopen(filename.c_str(), "r");
  if (f == NULL)
    ROS_ERROR("file not found: %s", filename.c_str());
  double res[11];
  int i = 0;
  while(fscanf(f, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf", &res[0], & res[1], & res[2], &res[3], &res[4], &res[5], &res[6], &res[7], &res[8], &res[9], &res[10]) == 11)
    {
      x_left->data[i] = res[0];
      y_left->data[i] = res[1];
      z_left->data[i] = res[2];
      theta_left->data[i] = res[3];
      x_right->data[i] = res[4];
      y_right->data[i] = res[5];
      z_right->data[i] = res[6];
      theta_right->data[i] = res[7];
      zmp_x->data[i] = res[8];
      zmp_y->data[i] = res[9];
      theta_torso->data[i] = res[10];
      i++;
    }
  L = i;
  fclose(f);
}

bool add(ar601_trajectories::GetTrajectory::Request  &req,
         ar601_trajectories::GetTrajectory::Response &res)
{
  size_t SIZE = 1000000;
  emxArray_real_T *zmp_x = emxCreate_real_T(1, SIZE);
  emxArray_real_T *zmp_y = emxCreate_real_T(1, SIZE);
  emxArray_real_T *x_left = emxCreate_real_T(1, SIZE);
  emxArray_real_T *y_left = emxCreate_real_T(1, SIZE);
  emxArray_real_T *z_left = emxCreate_real_T(1, SIZE);
  emxArray_real_T *theta_left = emxCreate_real_T(1, SIZE);
  emxArray_real_T *x_right = emxCreate_real_T(1, SIZE);
  emxArray_real_T *y_right = emxCreate_real_T(1, SIZE);
  emxArray_real_T *z_right = emxCreate_real_T(1, SIZE);
  emxArray_real_T *theta_right = emxCreate_real_T(1, SIZE);
  emxArray_real_T *theta_torso = emxCreate_real_T(1, SIZE);
  double L;
  std::string path = ros::package::getPath("ar601_trajectories");
  switch(req.type) 
    {
    case 0:
      load_from_file(path+("/trajectories/0.traj"), x_left, y_left, z_left, theta_left, x_right, y_right, z_right, theta_right, zmp_x, zmp_y, theta_torso, L);
      break;
    case 1:
      load_from_file(path+("/trajectories/step_forward.traj"), x_left, y_left, z_left, theta_left, x_right, y_right, z_right, theta_right, zmp_x, zmp_y, theta_torso, L);
      break;
    case 2:
      load_from_file(path+("/trajectories/step_back.traj"), x_left, y_left, z_left, theta_left, x_right, y_right, z_right, theta_right, zmp_x, zmp_y, theta_torso, L);
      break;
    case 3:
      load_from_file(path+("/trajectories/step_right.traj"), x_left, y_left, z_left, theta_left, x_right, y_right, z_right, theta_right, zmp_x, zmp_y, theta_torso, L);
      break;
    case 4:
      load_from_file(path+("/trajectories/step_left.traj"), x_left, y_left, z_left, theta_left, x_right, y_right, z_right, theta_right, zmp_x, zmp_y, theta_torso, L);
      break;
    case 5:
      load_from_file(path+("/trajectories/still.traj"), x_left, y_left, z_left, theta_left, x_right, y_right, z_right, theta_right, zmp_x, zmp_y, theta_torso, L);
      break;
    case 6:
      load_from_file(path+("/trajectories/stepping.traj"), x_left, y_left, z_left, theta_left, x_right, y_right, z_right, theta_right, zmp_x, zmp_y, theta_torso, L);
      break;
    default:
      main_trajectory(x_left, y_left, z_left, theta_left, x_right, y_right, z_right, theta_right, zmp_x, zmp_y, theta_torso, &L);
      break;
    };
  ROS_INFO("%f %f %f", theta_left->data[0], theta_right->data[0], theta_torso->data[0]); 
  res.N = L;
  int i = 0;
  while(i < res.N)
    {
      res.zmp_x.push_back(zmp_x->data[i]);
      res.zmp_y.push_back(zmp_y->data[i]);
      res.x_left.push_back(x_left->data[i]);
      res.y_left.push_back(y_left->data[i]);
      res.z_left.push_back(z_left->data[i]);
      res.theta_left.push_back(theta_left->data[i]);
      res.x_right.push_back(x_right->data[i]);
      res.y_right.push_back(y_right->data[i]);
      res.z_right.push_back(z_right->data[i]);
      res.theta_right.push_back(theta_right->data[i]);
      res.theta_torso.push_back(theta_torso->data[i]);      
      i++;
    }
  ROS_INFO("sending back trajectory: [%ld]", (long int)res.N);
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "trajectory_server");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("get_trajectory", add);
  ros::spin();

  return 0;
}
