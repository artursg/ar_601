#include "preview_control_node.h"

#include <gtest/gtest.h>
#include <ros/package.h>

#include <fstream>

#include "basic_trajectory.h"

// Declare a test
TEST(TestSuite, walk_ideal)
{
  // Load test files
  std::string path = ros::package::getPath("ar601_preview_control");
  path = path + "/test/data/";
  std::fstream x_test, u_test;
  x_test.open((path + std::string("/test_x.data")).c_str(), std::fstream::in);
  ASSERT_FALSE(x_test.fail());
  u_test.open((path + std::string("/test_u.data")).c_str(), std::fstream::in);
  ASSERT_FALSE(u_test.fail());
  // Sample trajectory
  basic_trajectory_t traj;
  traj.fill_trajectories();
  preview_control_node node(traj.T, traj.z0);
  node.load_G_p();
  std::deque<Eigen::Matrix<double, 2, 1> > plan;
  // Compare results
  for (size_t i = 0; i < traj.N; i++)
    node.add_path_point(traj.desired_zmp_x[i], traj.desired_zmp_y[i]);
  FILE * f = fopen("test.txt", "w");
  for (int i = 0; i < traj.N; i++){
    node.update(Eigen::Vector2d(traj.desired_zmp_x[i], traj.desired_zmp_y[i]));
    double x1, x2, x3, y1, y2, y3;
    node.get_xk(x1, x2, x3);
    node.get_yk(y1, y2, y3);
    fprintf(f, "%f %f %f %f\n", traj.ax_left[i], traj.az_left[i], x1, y1);
  }
  fclose(f);
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
