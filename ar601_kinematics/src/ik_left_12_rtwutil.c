/*
 * File: ik_left_12_rtwutil.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 27-Apr-2016 13:07:02
 */

/* Include files */
#include "rt_nonfinite.h"
#include "ik_left_12.h"
#include "ik_right_12.h"
#include "ik_left_12_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
double rt_atan2d_snf(double u0, double u1)
{
  double y;
  int b_u0;
  int b_u1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      b_u0 = 1;
    } else {
      b_u0 = -1;
    }

    if (u1 > 0.0) {
      b_u1 = 1;
    } else {
      b_u1 = -1;
    }

    y = atan2(b_u0, b_u1);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(double)(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/*
 * File trailer for ik_left_12_rtwutil.c
 *
 * [EOF]
 */
