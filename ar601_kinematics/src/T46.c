/*
 * File: T46.c
 *
 * MATLAB Coder version            : 2.8
 * C/C++ source code generated on  : 23-Jun-2016 07:20:40
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ik_right_12.h"
#include "T46.h"

/* Function Definitions */

/*
 * Arguments    : double b_q4
 *                double q5
 *                double q6
 *                double x
 *                double y
 *                double z
 *                const double R[16]
 *                double S[16]
 * Return Type  : void
 */
void T46(double b_q4, double q5, double q6, double x, double y, double z, const
         double R[16], double S[16])
{
  double t2;
  double t3;
  double t4;
  double t5;
  double t6;
  double t7;
  double t8;
  double t9;
  double t10;
  double t11;
  double t12;
  double t13;
  double t16;
  double t26;
  double t29;
  double t35;
  double t37;
  double t42;
  double t47;
  double t49;
  double t54;
  double b_x[16];
  t2 = cos(b_q4);
  t3 = cos(q5);
  t4 = t2 * t2;
  t5 = sin(q5);
  t6 = t3 * t3;
  t7 = sin(b_q4);
  t8 = t7 * t7;
  t9 = t5 * t5;
  t10 = sin(q6);
  t11 = cos(q6);
  t12 = t11 * t11;
  t13 = t10 * t10;
  t16 = t2 * t5 + t3 * t7;
  t26 = 1.0 / (((((((t4 * t6 * t13 + t4 * t9 * t12) + t6 * t8 * t12) + t4 * t9 *
                   t13) + t6 * t8 * t13) + t8 * t9 * t12) + t8 * t9 * t13) + t4 *
               t6 * t12);
  t29 = t2 * t3 + -(t5 * t7);
  t35 = 1.0 / (((t4 * t6 + t4 * t9) + t6 * t8) + t8 * t9);
  t37 = 1.0 / (t12 + t13);
  t42 = (((R[10] * -0.096 + R[2] * 0.02) + R[6] * 0.088) + z) - 0.1055;
  t47 = ((R[9] * -0.096 + R[1] * 0.02) + R[5] * 0.088) + y;
  t49 = 1.0 / (t4 + t8);
  t54 = ((R[8] * -0.096 + R[0] * 0.02) + R[4] * 0.088) + x;
  b_x[0] = (R[0] * t29 * t35 + R[1] * t10 * t16 * t26) - R[2] * t11 * t16 * t26;
  b_x[1] = R[1] * t11 * t37 + R[2] * t10 * t37;
  b_x[2] = (R[0] * t16 * t35 - R[1] * t10 * t26 * t29) + R[2] * t11 * t26 * t29;
  b_x[3] = 0.0;
  b_x[4] = (R[4] * t29 * t35 + R[5] * t10 * t16 * t26) - R[6] * t11 * t16 * t26;
  b_x[5] = R[5] * t11 * t37 + R[6] * t10 * t37;
  b_x[6] = (R[4] * t16 * t35 - R[5] * t10 * t26 * t29) + R[6] * t11 * t26 * t29;
  b_x[7] = 0.0;
  b_x[8] = (R[8] * t29 * t35 + R[9] * t10 * t16 * t26) - R[10] * t11 * t16 * t26;
  b_x[9] = R[9] * t11 * t37 + R[10] * t10 * t37;
  b_x[10] = (R[8] * t16 * t35 - R[9] * t10 * t26 * t29) + R[10] * t11 * t26 *
    t29;
  b_x[11] = 0.0;
  b_x[12] = ((t7 * t49 * 0.28 + t29 * t35 * t54) - t11 * t16 * t26 * t42) + t10 *
    t16 * t26 * t47;
  b_x[13] = t10 * t37 * t42 + t11 * t37 * t47;
  b_x[14] = ((t49 * ((t2 + t4) + t8) * -0.28 + t16 * t35 * t54) + t11 * t26 *
             t29 * t42) - t10 * t26 * t29 * t47;
  b_x[15] = 1.0;
  memcpy(&S[0], &b_x[0], sizeof(double) << 4);
}

/*
 * File trailer for T46.c
 *
 * [EOF]
 */
