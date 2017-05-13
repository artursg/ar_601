#include "rt_nonfinite.h"
#include "main_trajectory.h"
#include "f_z.h"
#include "main_data.h"

double f_z(double t, double up)
{
  double z;
  if (up == 1.0) {
    if (t <= p_ds * t0) {
      z = 0.0;
    } else {
      z = 0.5 * h * (1.0 - cos(2.0 * (1.0 / (t0 - p_ds * t0)) *
        3.1415926535897931 * (t - p_ds * t0)));
    }
  } else {
    z = 0.0;
  }

  return z;
}
