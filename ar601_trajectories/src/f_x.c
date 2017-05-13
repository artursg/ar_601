#include "rt_nonfinite.h"
#include "main_trajectory.h"
#include "f_x.h"
#include "main_data.h"

double f_x(double t, double x1, double x2)
{
  double b_x;
  if (t <= p_ds * t0) {
    b_x = x1;
  } else {
    b_x = 0.5 * (x2 - x1) * (1.0 - cos(3.1415926535897931 * (t - p_ds * t0) /
      (t0 - p_ds * t0))) + x1;
  }

  return b_x;
}
