
struct basic_trajectory_t{
  double t_preview;
  double t0;
  double l0;
  double p_ds;
  double h;
  double T;
  double z0;
  double b_y0;
  double d_x;
  double d_t;
  double *x_op, *y_op, *desired_zmp_x, *desired_zmp_y, *ax_left, *az_left, *ax_right, * az_right;
  int N;

  double x_os(double t);
  double y_os(double t);
  double x_left(double t);
  double x_right(double t);
  double z_left(double t);
  double z_right(double t);
  double d_zmp_x(double t);
  double d_zmp_y(double t);
  double d_zmp_y_2(double);
  void fill_trajectories(); 
};



