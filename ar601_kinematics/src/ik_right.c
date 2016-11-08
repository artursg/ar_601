/*
 * File: ik_right.c
 *
 * MATLAB Coder version            : 2.8
 * C/C++ source code generated on  : 23-Jun-2016 07:20:40
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ik_right_12.h"
#include "ik_right.h"
#include "T46.h"
#include "q5_1.h"
#include "q4.h"
#include "mpower.h"

/* Function Declarations */
static double rt_atan2d_snf(double u0, double u1);

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_atan2d_snf(double u0, double u1)
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
 * UNTITLED Summary of this function goes here
 *    Detailed explanation goes here
 * Arguments    : double x
 *                double y
 *                double z
 *                double R[16]
 *                double xt
 *                double yt
 *                double zt
 *                const double Rt[16]
 *                double angles[6]
 * Return Type  : void
 */
void ik_right(double x, double y, double z, double R[16], double xt, double yt,
              double zt, const double Rt[16], double angles[6])
{
  int i3;
  double dr[3];
  int i4;
  static const double b[3] = { 0.0, 0.176, 0.0 };

  double A[16];
  double dv6[16];
  static const signed char iv4[4] = { 0, 0, 0, 1 };

  double b_b[16];
  double b_A[16];
  int i5;
  double I[16];
  double b_angles[48];
  double b_x;
  double t2;
  double t3;
  double t4;
  double t10;
  double t11;
  double t17;
  double t22;
  double t23;
  double t5;
  double q1;
  double q3;
  double q2;
  for (i3 = 0; i3 < 3; i3++) {
    dr[i3] = 0.0;
    for (i4 = 0; i4 < 3; i4++) {
      dr[i3] += Rt[i3 + (i4 << 2)] * b[i4];
    }
  }

  x += dr[0];
  y += dr[1];
  z += dr[2];
  mpower(R, A);
  dv6[0] = 1.0;
  dv6[4] = 0.0;
  dv6[8] = 0.0;
  dv6[12] = x;
  dv6[1] = 0.0;
  dv6[5] = 1.0;
  dv6[9] = 0.0;
  dv6[13] = y;
  dv6[2] = 0.0;
  dv6[6] = 0.0;
  dv6[10] = 1.0;
  dv6[14] = z;
  for (i3 = 0; i3 < 4; i3++) {
    dv6[3 + (i3 << 2)] = iv4[i3];
  }

  mpower(dv6, b_b);
  dv6[0] = 1.0;
  dv6[4] = 0.0;
  dv6[8] = 0.0;
  dv6[12] = xt;
  dv6[1] = 0.0;
  dv6[5] = 1.0;
  dv6[9] = 0.0;
  dv6[13] = yt;
  dv6[2] = 0.0;
  dv6[6] = 0.0;
  dv6[10] = 1.0;
  dv6[14] = zt;
  for (i3 = 0; i3 < 4; i3++) {
    for (i4 = 0; i4 < 4; i4++) {
      b_A[i3 + (i4 << 2)] = 0.0;
      for (i5 = 0; i5 < 4; i5++) {
        b_A[i3 + (i4 << 2)] += A[i3 + (i5 << 2)] * b_b[i5 + (i4 << 2)];
      }
    }

    dv6[3 + (i3 << 2)] = iv4[i3];
  }

  mpower(R, A);
  for (i3 = 0; i3 < 4; i3++) {
    for (i4 = 0; i4 < 4; i4++) {
      b_b[i3 + (i4 << 2)] = 0.0;
      for (i5 = 0; i5 < 4; i5++) {
        b_b[i3 + (i4 << 2)] += b_A[i3 + (i5 << 2)] * dv6[i5 + (i4 << 2)];
      }
    }

    for (i4 = 0; i4 < 4; i4++) {
      I[i3 + (i4 << 2)] = 0.0;
      for (i5 = 0; i5 < 4; i5++) {
        I[i3 + (i4 << 2)] += b_b[i3 + (i5 << 2)] * Rt[i5 + (i4 << 2)];
      }

      R[i3 + (i4 << 2)] = 0.0;
      for (i5 = 0; i5 < 4; i5++) {
        R[i3 + (i4 << 2)] += A[i3 + (i5 << 2)] * Rt[i5 + (i4 << 2)];
      }
    }
  }

  memset(&b_angles[0], 0, 48U * sizeof(double));
  b_x = atan((((R[9] * -0.096 + R[1] * 0.02) + R[5] * 0.088) + I[13]) / ((((R[10]
    * -0.096 + R[2] * 0.02) + R[6] * 0.088) + I[14]) - 0.1055));
  for (i3 = 0; i3 < 8; i3++) {
    b_angles[5 + 6 * i3] = -b_x;
  }

  b_x = q4(I[12], I[13], I[14], R);
  for (i3 = 0; i3 < 4; i3++) {
    b_angles[3 + 6 * i3] = b_x;
  }

  b_x = q4(I[12], I[13], I[14], R);
  for (i3 = 0; i3 < 4; i3++) {
    b_angles[3 + 6 * (4 + i3)] = -b_x;
  }

  b_x = q5_1(I[12], I[13], I[14], R);
  for (i3 = 0; i3 < 2; i3++) {
    b_angles[4 + 6 * i3] = b_x;
  }

  t2 = (((R[10] * -0.096 + R[2] * 0.02) + R[6] * 0.088) + I[14]) - 0.1055;
  t3 = ((R[8] * -0.096 + R[0] * 0.02) + R[4] * 0.088) + I[12];
  t4 = ((R[9] * -0.096 + R[1] * 0.02) + R[5] * 0.088) + I[13];
  t10 = t2 * t2;
  t11 = t10 * 6.3775510204081627;
  t17 = t3 * t3 * 6.3775510204081627;
  t22 = t4 * t4;
  t23 = t22 * 6.3775510204081627;
  t5 = ((t11 + t17) + t23) - 1.0;
  b_x = -atan(sqrt(-(t5 * t5) + 1.0) / ((t11 + t17) + t23)) - atan(t3 / sqrt(t10
    + t22));
  for (i3 = 0; i3 < 2; i3++) {
    b_angles[4 + 6 * (2 + i3)] = b_x;
  }

  t2 = (((R[10] * -0.096 + R[2] * 0.02) + R[6] * 0.088) + I[14]) - 0.1055;
  t3 = ((R[8] * -0.096 + R[0] * 0.02) + R[4] * 0.088) + I[12];
  t4 = ((R[9] * -0.096 + R[1] * 0.02) + R[5] * 0.088) + I[13];
  t10 = t2 * t2;
  t11 = t10 * 6.3775510204081627;
  t17 = t3 * t3 * 6.3775510204081627;
  t22 = t4 * t4;
  t23 = t22 * 6.3775510204081627;
  t5 = ((t11 + t17) + t23) - 1.0;
  b_x = atan(sqrt(-(t5 * t5) + 1.0) / ((t11 + t17) + t23)) + atan(t3 / sqrt(t10
    + t22));
  for (i3 = 0; i3 < 2; i3++) {
    b_angles[4 + 6 * (4 + i3)] = b_x;
  }

  t2 = (((R[10] * -0.096 + R[2] * 0.02) + R[6] * 0.088) + I[14]) - 0.1055;
  t3 = ((R[8] * -0.096 + R[0] * 0.02) + R[4] * 0.088) + I[12];
  t4 = ((R[9] * -0.096 + R[1] * 0.02) + R[5] * 0.088) + I[13];
  t10 = t2 * t2;
  t11 = t10 * 6.3775510204081627;
  t17 = t3 * t3 * 6.3775510204081627;
  t22 = t4 * t4;
  t23 = t22 * 6.3775510204081627;
  t5 = ((t11 + t17) + t23) - 1.0;
  b_x = atan(sqrt(-(t5 * t5) + 1.0) / ((t11 + t17) + t23)) - atan(t3 / sqrt(t10
    + t22));
  for (i3 = 0; i3 < 2; i3++) {
    b_angles[4 + 6 * (6 + i3)] = b_x;
  }

  T46(b_angles[3], b_angles[4], b_angles[5], I[12], I[13], I[14], R, A);
  if (fabs(fabs(A[9]) - 1.0) >= 0.0001) {
    q1 = rt_atan2d_snf(A[1], A[5]);
    q3 = rt_atan2d_snf(A[8], A[10]);
    if (fabs(A[10]) >= 0.0001) {
      q2 = rt_atan2d_snf(-A[9] * cos(q3), A[10]);
    } else {
      q2 = rt_atan2d_snf(-A[9] * sin(q3), A[8]);
    }
  } else {
    q1 = 0.0;
    q2 = 0.0;
    q3 = 0.0;
  }

  for (i3 = 0; i3 < 2; i3++) {
    b_angles[6 * i3] = q1;
  }

  b_angles[1] = q2;
  b_angles[7] = -q2;
  for (i3 = 0; i3 < 2; i3++) {
    b_angles[2 + 6 * i3] = q3;
  }

  T46(b_angles[15], b_angles[16], b_angles[17], I[12], I[13], I[14], R, A);
  if (fabs(fabs(A[9]) - 1.0) >= 0.0001) {
    q1 = rt_atan2d_snf(A[1], A[5]);
    q3 = rt_atan2d_snf(A[8], A[10]);
    if (fabs(A[10]) >= 0.0001) {
      q2 = rt_atan2d_snf(-A[9] * cos(q3), A[10]);
    } else {
      q2 = rt_atan2d_snf(-A[9] * sin(q3), A[8]);
    }
  } else {
    q1 = 0.0;
    q2 = 0.0;
    q3 = 0.0;
  }

  for (i3 = 0; i3 < 2; i3++) {
    b_angles[6 * (2 + i3)] = q1;
  }

  b_angles[13] = q2;
  b_angles[19] = -q2;
  for (i3 = 0; i3 < 2; i3++) {
    b_angles[2 + 6 * (2 + i3)] = q3;
  }

  T46(b_angles[27], b_angles[28], b_angles[29], I[12], I[13], I[14], R, A);
  if (fabs(fabs(A[9]) - 1.0) >= 0.0001) {
    q1 = rt_atan2d_snf(A[1], A[5]);
    q3 = rt_atan2d_snf(A[8], A[10]);
    if (fabs(A[10]) >= 0.0001) {
      q2 = rt_atan2d_snf(-A[9] * cos(q3), A[10]);
    } else {
      q2 = rt_atan2d_snf(-A[9] * sin(q3), A[8]);
    }
  } else {
    q1 = 0.0;
    q2 = 0.0;
    q3 = 0.0;
  }

  for (i3 = 0; i3 < 2; i3++) {
    b_angles[6 * (4 + i3)] = q1;
  }

  b_angles[25] = q2;
  b_angles[31] = -q2;
  for (i3 = 0; i3 < 2; i3++) {
    b_angles[2 + 6 * (4 + i3)] = q3;
  }

  T46(b_angles[39], b_angles[40], b_angles[41], I[12], I[13], I[14], R, A);
  if (fabs(fabs(A[9]) - 1.0) >= 0.0001) {
    q1 = rt_atan2d_snf(A[1], A[5]);
    q3 = rt_atan2d_snf(A[8], A[10]);
    if (fabs(A[10]) >= 0.0001) {
      q2 = rt_atan2d_snf(-A[9] * cos(q3), A[10]);
    } else {
      q2 = rt_atan2d_snf(-A[9] * sin(q3), A[8]);
    }
  } else {
    q1 = 0.0;
    q2 = 0.0;
    q3 = 0.0;
  }

  for (i3 = 0; i3 < 2; i3++) {
    b_angles[6 * (6 + i3)] = q1;
  }

  b_angles[37] = q2;
  b_angles[43] = -q2;
  for (i3 = 0; i3 < 2; i3++) {
    b_angles[2 + 6 * (6 + i3)] = q3;
  }

  for (i3 = 0; i3 < 6; i3++) {
    angles[i3] = -b_angles[24 + i3];
  }
}

/*
 * File trailer for ik_right.c
 *
 * [EOF]
 */
