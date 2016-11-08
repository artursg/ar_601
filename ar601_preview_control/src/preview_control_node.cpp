#include "preview_control_node.h"

#include <fstream>

void preview_control_node::calc_xk()
{
  calc_uk();
  xk = mA * xk + mB * uk;
}


void preview_control_node::calc_uk()
{
  Eigen::Matrix<double, 1, 2> G_p(Eigen::Matrix<double, 1, 2>::Zero());
  for (size_t i = 0; i < G.size(); i++) {      
    Eigen::Matrix<double, 1, 2> point = last_path_point;
    if (i < path.size())
    {
      point = path[i];
      last_path_point = point;
    }
    G_p += G(i) * point;
  }
  uk = -K_e*scale_K_e*sum_e - K*xk - G_p;
}

void preview_control_node::load_G_p()
{
  std::string path = ros::package::getPath("ar601_preview_control") + "/config/g_coef.txt";
  std::ifstream file;
  std::string line;
  std::vector<double> buffer;
  file.open(path.c_str());
  if (file.is_open())
    {
      while(getline(file, line))
	{
	  buffer.push_back(strtod(line.c_str(), NULL));
	}
      size_t G_p_length = buffer.size();
      G = Eigen::VectorXd::Map(buffer.data(), buffer.size()); 
    }
  else
    ROS_ERROR("File with G_p  %s not found", path.c_str());
  ROS_INFO("Total %zu G_p coefficients loaded.", G.size());
}

void preview_control_node::update(const Eigen::Vector2d& zmp)
{
  ZMP_debt(0, 0) = zmp(0) - path.front()(0);

  ZMP_debt(0, 1) = zmp(1) - path.front()(1);

  sum_e += ZMP_debt;
  if (path.size() > 1)
    {
      calc_xk();
      //path_completed.push_back(Eigen::Vector2d(xk(0), xk(1)));
      path.pop_front();      
    }
}
