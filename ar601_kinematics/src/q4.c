/*
 * File: q4.c
 *
 * MATLAB Coder version            : 2.8
 * C/C++ source code generated on  : 23-Jun-2016 07:20:40
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ik_right_12.h"
#include "q4.h"

/* Function Definitions */

/*
 * Arguments    : double x
 *                double y
 *                double z
 *                const double R[16]
 * Return Type  : double
 */
double q4(double x, double y, double z, const double R[16])
{
  double t2;
  double t3;
  double t4;
  t2 = (((R[10] * -0.096 + R[2] * 0.02) + R[6] * 0.088) + z) - 0.1055;
  t3 = ((R[8] * -0.096 + R[0] * 0.02) + R[4] * 0.088) + x;
  t4 = ((R[9] * -0.096 + R[1] * 0.02) + R[5] * 0.088) + y;
  return acos(((t2 * t2 * 6.3775510204081627 + t3 * t3 * 6.3775510204081627) +
               t4 * t4 * 6.3775510204081627) - 1.0);
}

/*
 * File trailer for q4.c
 *
 * [EOF]
 */
