#include "rt_nonfinite.h"
#include "main_trajectory.h"
#include "f_zmp_x.h"
#include "main_data.h"

double f_zmp_x(double t)
{
  double b_x;
  double b_t;
  if (t <= p_ds * t0) {
    b_t = t / (p_ds * t0);
    b_x = (1.0 + 2.0 * b_t) * ((1.0 - b_t) * (1.0 - b_t)) * 0.0 + b_t * b_t *
      (3.0 - 2.0 * b_t) * 0.02;
  } else {
    b_x = 0.02;
  }

  return b_x;
}
