/*
 * File: q5_2.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 27-Apr-2016 13:07:02
 */

/* Include files */
#include "rt_nonfinite.h"
#include "ik_left_12.h"
#include "ik_right_12.h"
#include "q5_2.h"

/* Function Definitions */

/*
 * Arguments    : double x
 *                double y
 *                double z
 *                const double R[16]
 * Return Type  : double
 */
double q5_2(double x, double y, double z, const double R[16])
{
  double t2;
  double t3;
  double t4;
  double t10;
  double t11;
  double t17;
  double t5;
  t2 = (((R[10] * -0.096 + R[2] * 0.02) + R[6] * 0.088) + z) - 0.1055;
  t3 = ((R[8] * -0.096 + R[0] * 0.02) + R[4] * 0.088) + x;
  t4 = ((R[9] * -0.096 + R[1] * 0.02) + R[5] * 0.088) + y;
  t10 = t2 * t2;
  t11 = t10 * 6.3775510204081627;
  t17 = t3 * t3 * 6.3775510204081627;
  t2 = t4 * t4;
  t4 = t2 * 6.3775510204081627;
  t5 = ((t11 + t17) + t4) - 1.0;
  return -atan(sqrt(-(t5 * t5) + 1.0) / ((t11 + t17) + t4)) - atan(t3 / sqrt(t10
    + t2));
}

/*
 * File trailer for q5_2.c
 *
 * [EOF]
 */
