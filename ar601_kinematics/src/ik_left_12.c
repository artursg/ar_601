/*
 * File: ik_left_12.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 27-Apr-2016 13:07:02
 */

/* Include files */
#include "rt_nonfinite.h"
#include "ik_left_12.h"
#include "ik_right_12.h"
#include "ik_left.h"

/* Function Definitions */

/*
 * Arguments    : double x
 *                double y
 *                double z
 *                double phi_x
 *                double phi_y
 *                double phi_z
 *                double x_t
 *                double y_t
 *                double z_t
 *                double phi_x_t
 *                double phi_y_t
 *                double phi_z_t
 *                double angles[6]
 * Return Type  : void
 */
void ik_left_12(double x, double y, double z, double phi_x, double phi_y, double
                phi_z, double x_t, double y_t, double z_t, double phi_x_t,
                double phi_y_t, double phi_z_t, double angles[6])
{
  double dv0[16];
  double dv1[16];
  double dv2[16];
  int i0;
  static const signed char iv0[4] = { 0, 0, 1, 0 };

  static const signed char iv1[4] = { 0, 0, 0, 1 };

  static const signed char iv2[4] = { 0, 1, 0, 0 };

  double dv3[16];
  double dv4[16];
  int i1;
  int i2;
  static const signed char iv3[4] = { 1, 0, 0, 0 };

  double dv5[16];
  dv1[0] = cos(phi_z);
  dv1[4] = -sin(phi_z);
  dv1[8] = 0.0;
  dv1[12] = 0.0;
  dv1[1] = sin(phi_z);
  dv1[5] = cos(phi_z);
  dv1[9] = 0.0;
  dv1[13] = 0.0;
  dv2[0] = cos(phi_y);
  dv2[4] = 0.0;
  dv2[8] = sin(phi_y);
  dv2[12] = 0.0;
  for (i0 = 0; i0 < 4; i0++) {
    dv1[2 + (i0 << 2)] = iv0[i0];
    dv1[3 + (i0 << 2)] = iv1[i0];
    dv2[1 + (i0 << 2)] = iv2[i0];
  }

  dv2[2] = -sin(phi_y);
  dv2[6] = 0.0;
  dv2[10] = cos(phi_y);
  dv2[14] = 0.0;
  for (i0 = 0; i0 < 4; i0++) {
    dv2[3 + (i0 << 2)] = iv1[i0];
  }

  for (i0 = 0; i0 < 4; i0++) {
    for (i1 = 0; i1 < 4; i1++) {
      dv3[i0 + (i1 << 2)] = 0.0;
      for (i2 = 0; i2 < 4; i2++) {
        dv3[i0 + (i1 << 2)] += dv1[i0 + (i2 << 2)] * dv2[i2 + (i1 << 2)];
      }
    }

    dv4[i0 << 2] = iv3[i0];
  }

  dv4[1] = 0.0;
  dv4[5] = cos(phi_x);
  dv4[9] = -sin(phi_x);
  dv4[13] = 0.0;
  dv4[2] = 0.0;
  dv4[6] = sin(phi_x);
  dv4[10] = cos(phi_x);
  dv4[14] = 0.0;
  for (i0 = 0; i0 < 4; i0++) {
    dv4[3 + (i0 << 2)] = iv1[i0];
  }

  dv2[0] = cos(phi_z_t);
  dv2[4] = -sin(phi_z_t);
  dv2[8] = 0.0;
  dv2[12] = 0.0;
  dv2[1] = sin(phi_z_t);
  dv2[5] = cos(phi_z_t);
  dv2[9] = 0.0;
  dv2[13] = 0.0;
  dv5[0] = cos(phi_y_t);
  dv5[4] = 0.0;
  dv5[8] = sin(phi_y_t);
  dv5[12] = 0.0;
  for (i0 = 0; i0 < 4; i0++) {
    for (i1 = 0; i1 < 4; i1++) {
      dv0[i0 + (i1 << 2)] = 0.0;
      for (i2 = 0; i2 < 4; i2++) {
        dv0[i0 + (i1 << 2)] += dv3[i0 + (i2 << 2)] * dv4[i2 + (i1 << 2)];
      }
    }

    dv2[2 + (i0 << 2)] = iv0[i0];
    dv2[3 + (i0 << 2)] = iv1[i0];
    dv5[1 + (i0 << 2)] = iv2[i0];
  }

  dv5[2] = -sin(phi_y_t);
  dv5[6] = 0.0;
  dv5[10] = cos(phi_y_t);
  dv5[14] = 0.0;
  for (i0 = 0; i0 < 4; i0++) {
    dv5[3 + (i0 << 2)] = iv1[i0];
  }

  for (i0 = 0; i0 < 4; i0++) {
    for (i1 = 0; i1 < 4; i1++) {
      dv3[i0 + (i1 << 2)] = 0.0;
      for (i2 = 0; i2 < 4; i2++) {
        dv3[i0 + (i1 << 2)] += dv2[i0 + (i2 << 2)] * dv5[i2 + (i1 << 2)];
      }
    }

    dv4[i0 << 2] = iv3[i0];
  }

  dv4[1] = 0.0;
  dv4[5] = cos(phi_x_t);
  dv4[9] = -sin(phi_x_t);
  dv4[13] = 0.0;
  dv4[2] = 0.0;
  dv4[6] = sin(phi_x_t);
  dv4[10] = cos(phi_x_t);
  dv4[14] = 0.0;
  for (i0 = 0; i0 < 4; i0++) {
    dv4[3 + (i0 << 2)] = iv1[i0];
  }

  for (i0 = 0; i0 < 4; i0++) {
    for (i1 = 0; i1 < 4; i1++) {
      dv1[i0 + (i1 << 2)] = 0.0;
      for (i2 = 0; i2 < 4; i2++) {
        dv1[i0 + (i1 << 2)] += dv3[i0 + (i2 << 2)] * dv4[i2 + (i1 << 2)];
      }
    }
  }

  ik_left(x, y, z, dv0, x_t, y_t, z_t, dv1, angles);
}

/*
 * File trailer for ik_left_12.c
 *
 * [EOF]
 */
