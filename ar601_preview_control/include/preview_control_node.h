#include <deque>

#include <Eigen/Core>

#include <ros/ros.h>
#include <ros/package.h>

const double GRAVITATIONAL_CONSTANT = 9.80665;

class preview_control_node
{
 private:
  Eigen::Matrix<double, 3, 3> mA;
  Eigen::Matrix<double, 3, 1> mB;
  Eigen::Matrix<double, 1, 3> mC;
  Eigen::Matrix<double, 3, 2> xk;
  Eigen::Matrix<double, 1 ,2> uk;
  Eigen::Matrix<double, Eigen::Dynamic, 1> G;
  Eigen::Matrix<double, 1, 3> K;
  Eigen::Matrix<double, 1, 2> ZMP;
  Eigen::Matrix<double, 1, 2> ZMP_debt;
  double K_e;
  double scale_K_e;
  Eigen::Matrix<double, 2, 1> last_path_point;
  std::deque<Eigen::Matrix<double, 2, 1> > path;
  std::deque<Eigen::Matrix<double, 2, 1> > path_completed;

  void calc_uk();
  void calc_xk();
  Eigen::Matrix<double, 1, 2> sum_e;

 public:
 preview_control_node(const double dt, const double z0)
   : xk(Eigen::Matrix<double, 3, 2>::Zero()), uk(Eigen::Matrix<double, 1, 2>::Zero())
    {
      mA <<
	1, dt, 0.5 * dt * dt,
	0, 1, dt,
	0, 0, 1;
      mB <<
	1 / 6.0 * dt * dt * dt,
	0.5 * dt * dt,
	dt;
      mC << 1.0, 0.0, -z0/GRAVITATIONAL_CONSTANT;
      // K <<  544.087434885219,194.776048014174,16.7896681203493; //R=1e-6, Qe=1e-5, Q(x,v,a)=0
      // K_e = 3.05678545583634;

      // K <<  91676.0743700954,25187.5908056266,187.151962932711; //R=1e-6, Qe=1, Q(x,v,a)=0
      // K_e = 672.246232105208;

      // K <<  32911.7193456056,9706.22773870703,256.700260614023; //R=1e-6, Qe=1, Q(x,v,a)=0 0 1
      // K_e = 224.716980029896;

      // K <<  12745.9926786501,4258.77397436245,257.010770553134; //R=1e-6, Qe=1, Q(x,v,a)=0 0 10
      // K_e = 76.7538424259238;

      K <<  5076.84855257841,2101.03303186172,254.036571437320; //R=1e-6, Qe=1, Q(x,v,a)=0 0 100
      K_e = 24.6541163780930;

      // K <<  2156.84185638053,1191.19376959271,252.361273544738; //R=1e-6, Qe=1, Q(x,v,a)=0 0 1000
      // K_e = 7.83898364928063;

      scale_K_e=0;  
      sum_e(0,0) = 0;
      sum_e(0,1) = 0;
    }
  void load_G_p();

  void update(const Eigen::Vector2d& zmp);
  
  void get_path(std::deque<Eigen::Matrix<double, 2, 1> > &return_path)
  {
    return_path = path_completed;
  }

  void get_last_point(Eigen::Matrix<double, 2, 1> &last)
  {
	last = last_path_point;
  }

  void set_path(std::deque<Eigen::Matrix<double, 2, 1> > &planned)
  {
    path = planned;
  }

  void clear_path()
  {
    path.clear();
  }

  void add_path_point(double x, double y)
  {
    Eigen::Matrix<double, 2, 1> p;
    p(0) = x;
    p(1) = y;
    path.push_back(p);
  }
  
  void get_xk(double &x, double &xi, double &xii)
  {
    x = xk(0,0);
    xi = xk(1,0);
    xii = xk(2,0);
  }

  void get_yk(double &y, double &yi, double &yii)
  {
    y = xk(0,1);
    yi = xk(1,1);
    yii = xk(2,1);
  }
  
  void get_uk(double &x, double &y)
  {
    x = uk(0,0);
    y = uk(0,1);
  }

  void set_scale_K_e(double nK_e)
  {
    scale_K_e = nK_e;
    sum_e=sum_e*0;
  }
};
