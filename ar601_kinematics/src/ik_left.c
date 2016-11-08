/*
 * File: ik_left.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 27-Apr-2016 13:07:02
 */

/* Include files */
#include "rt_nonfinite.h"
#include "ik_left_12.h"
#include "ik_right_12.h"
#include "ik_left.h"
#include "T46.h"
#include "q5_4.h"
#include "q5_3.h"
#include "q5_2.h"
#include "q5_1.h"
#include "q4.h"
#include "inv.h"
#include "ik_left_12_rtwutil.h"

/* Function Definitions */

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
void ik_left(double x, double y, double z, double R[16], double xt, double yt,
             double zt, const double Rt[16], double angles[6])
{
  double T[16];
  int i3;
  static const signed char iv4[4] = { 0, 0, 0, 1 };

  double c[16];
  double b_c[16];
  double dv6[16];
  int i4;
  int i5;
  double I[16];
  double b_angles[48];
  double b_x;
  double q3;
  double q2;
  T[0] = 1.0;
  T[4] = 0.0;
  T[8] = 0.0;
  T[12] = x;
  T[1] = 0.0;
  T[5] = 1.0;
  T[9] = 0.0;
  T[13] = y;
  T[2] = 0.0;
  T[6] = 0.0;
  T[10] = 1.0;
  T[14] = z;
  for (i3 = 0; i3 < 4; i3++) {
    T[3 + (i3 << 2)] = iv4[i3];
  }

  invNxN(R, c);
  invNxN(T, b_c);
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
      T[i3 + (i4 << 2)] = 0.0;
      for (i5 = 0; i5 < 4; i5++) {
        T[i3 + (i4 << 2)] += c[i3 + (i5 << 2)] * b_c[i5 + (i4 << 2)];
      }
    }

    dv6[3 + (i3 << 2)] = iv4[i3];
  }

  invNxN(R, c);
  for (i3 = 0; i3 < 4; i3++) {
    for (i4 = 0; i4 < 4; i4++) {
      b_c[i3 + (i4 << 2)] = 0.0;
      for (i5 = 0; i5 < 4; i5++) {
        b_c[i3 + (i4 << 2)] += T[i3 + (i5 << 2)] * dv6[i5 + (i4 << 2)];
      }
    }

    for (i4 = 0; i4 < 4; i4++) {
      I[i3 + (i4 << 2)] = 0.0;
      for (i5 = 0; i5 < 4; i5++) {
        I[i3 + (i4 << 2)] += b_c[i3 + (i5 << 2)] * Rt[i5 + (i4 << 2)];
      }

      R[i3 + (i4 << 2)] = 0.0;
      for (i5 = 0; i5 < 4; i5++) {
        R[i3 + (i4 << 2)] += c[i3 + (i5 << 2)] * Rt[i5 + (i4 << 2)];
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

  b_x = q5_2(I[12], I[13], I[14], R);
  for (i3 = 0; i3 < 2; i3++) {
    b_angles[4 + 6 * (2 + i3)] = b_x;
  }

  b_x = q5_3(I[12], I[13], I[14], R);
  for (i3 = 0; i3 < 2; i3++) {
    b_angles[4 + 6 * (4 + i3)] = b_x;
  }

  b_x = q5_4(I[12], I[13], I[14], R);
  for (i3 = 0; i3 < 2; i3++) {
    b_angles[4 + 6 * (6 + i3)] = b_x;
  }

  T46(b_angles[3], b_angles[4], b_angles[5], I[12], I[13], I[14], R, T);
  if (fabs(fabs(T[9]) - 1.0) >= 0.0001) {
    b_x = rt_atan2d_snf(T[1], T[5]);
    q3 = rt_atan2d_snf(T[8], T[10]);
    if (fabs(T[10]) >= 0.0001) {
      q2 = rt_atan2d_snf(-T[9] * cos(q3), T[10]);
    } else {
      q2 = rt_atan2d_snf(-T[9] * sin(q3), T[8]);
    }
  } else {
    b_x = 0.0;
    q2 = 0.0;
    q3 = 0.0;
  }

  for (i3 = 0; i3 < 2; i3++) {
    b_angles[6 * i3] = b_x;
  }

  b_angles[1] = q2;
  b_angles[7] = -q2;
  for (i3 = 0; i3 < 2; i3++) {
    b_angles[2 + 6 * i3] = q3;
  }

  T46(b_angles[15], b_angles[16], b_angles[17], I[12], I[13], I[14], R, T);
  if (fabs(fabs(T[9]) - 1.0) >= 0.0001) {
    b_x = rt_atan2d_snf(T[1], T[5]);
    q3 = rt_atan2d_snf(T[8], T[10]);
    if (fabs(T[10]) >= 0.0001) {
      q2 = rt_atan2d_snf(-T[9] * cos(q3), T[10]);
    } else {
      q2 = rt_atan2d_snf(-T[9] * sin(q3), T[8]);
    }
  } else {
    b_x = 0.0;
    q2 = 0.0;
    q3 = 0.0;
  }

  for (i3 = 0; i3 < 2; i3++) {
    b_angles[6 * (2 + i3)] = b_x;
  }

  b_angles[13] = q2;
  b_angles[19] = -q2;
  for (i3 = 0; i3 < 2; i3++) {
    b_angles[2 + 6 * (2 + i3)] = q3;
  }

  T46(b_angles[27], b_angles[28], b_angles[29], I[12], I[13], I[14], R, T);
  if (fabs(fabs(T[9]) - 1.0) >= 0.0001) {
    b_x = rt_atan2d_snf(T[1], T[5]);
    q3 = rt_atan2d_snf(T[8], T[10]);
    if (fabs(T[10]) >= 0.0001) {
      q2 = rt_atan2d_snf(-T[9] * cos(q3), T[10]);
    } else {
      q2 = rt_atan2d_snf(-T[9] * sin(q3), T[8]);
    }
  } else {
    b_x = 0.0;
    q2 = 0.0;
    q3 = 0.0;
  }

  for (i3 = 0; i3 < 2; i3++) {
    b_angles[6 * (4 + i3)] = b_x;
  }

  b_angles[25] = q2;
  b_angles[31] = -q2;
  for (i3 = 0; i3 < 2; i3++) {
    b_angles[2 + 6 * (4 + i3)] = q3;
  }

  T46(b_angles[39], b_angles[40], b_angles[41], I[12], I[13], I[14], R, T);
  if (fabs(fabs(T[9]) - 1.0) >= 0.0001) {
    b_x = rt_atan2d_snf(T[1], T[5]);
    q3 = rt_atan2d_snf(T[8], T[10]);
    if (fabs(T[10]) >= 0.0001) {
      q2 = rt_atan2d_snf(-T[9] * cos(q3), T[10]);
    } else {
      q2 = rt_atan2d_snf(-T[9] * sin(q3), T[8]);
    }
  } else {
    b_x = 0.0;
    q2 = 0.0;
    q3 = 0.0;
  }

  for (i3 = 0; i3 < 2; i3++) {
    b_angles[6 * (6 + i3)] = b_x;
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
 * File trailer for ik_left.c
 *
 * [EOF]
 */
