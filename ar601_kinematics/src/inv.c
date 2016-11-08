/*
 * File: inv.c
 *
 * MATLAB Coder version            : 2.8
 * C/C++ source code generated on  : 23-Jun-2016 07:20:40
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ik_right_12.h"
#include "inv.h"

/* Function Definitions */

/*
 * Arguments    : const double x[16]
 *                double y[16]
 * Return Type  : void
 */
void invNxN(const double x[16], double y[16])
{
  double A[16];
  int i6;
  signed char ipiv[4];
  int j;
  int c;
  int jBcol;
  int ix;
  double smax;
  int ijA;
  double s;
  int i;
  int kAcol;
  signed char p[4];
  for (i6 = 0; i6 < 16; i6++) {
    y[i6] = 0.0;
    A[i6] = x[i6];
  }

  for (i6 = 0; i6 < 4; i6++) {
    ipiv[i6] = (signed char)(1 + i6);
  }

  for (j = 0; j < 3; j++) {
    c = j * 5;
    jBcol = 0;
    ix = c;
    smax = fabs(A[c]);
    for (ijA = 2; ijA <= 4 - j; ijA++) {
      ix++;
      s = fabs(A[ix]);
      if (s > smax) {
        jBcol = ijA - 1;
        smax = s;
      }
    }

    if (A[c + jBcol] != 0.0) {
      if (jBcol != 0) {
        ipiv[j] = (signed char)((j + jBcol) + 1);
        ix = j;
        jBcol += j;
        for (ijA = 0; ijA < 4; ijA++) {
          smax = A[ix];
          A[ix] = A[jBcol];
          A[jBcol] = smax;
          ix += 4;
          jBcol += 4;
        }
      }

      i6 = (c - j) + 4;
      for (i = c + 1; i + 1 <= i6; i++) {
        A[i] /= A[c];
      }
    }

    jBcol = c;
    kAcol = c + 4;
    for (i = 1; i <= 3 - j; i++) {
      smax = A[kAcol];
      if (A[kAcol] != 0.0) {
        ix = c + 1;
        i6 = (jBcol - j) + 8;
        for (ijA = 5 + jBcol; ijA + 1 <= i6; ijA++) {
          A[ijA] += A[ix] * -smax;
          ix++;
        }
      }

      kAcol += 4;
      jBcol += 4;
    }
  }

  for (i6 = 0; i6 < 4; i6++) {
    p[i6] = (signed char)(1 + i6);
  }

  for (ijA = 0; ijA < 3; ijA++) {
    if (ipiv[ijA] > 1 + ijA) {
      jBcol = p[ipiv[ijA] - 1];
      p[ipiv[ijA] - 1] = p[ijA];
      p[ijA] = (signed char)jBcol;
    }
  }

  for (ijA = 0; ijA < 4; ijA++) {
    c = p[ijA] - 1;
    y[ijA + ((p[ijA] - 1) << 2)] = 1.0;
    for (j = ijA; j + 1 < 5; j++) {
      if (y[j + (c << 2)] != 0.0) {
        for (i = j + 1; i + 1 < 5; i++) {
          y[i + (c << 2)] -= y[j + (c << 2)] * A[i + (j << 2)];
        }
      }
    }
  }

  for (j = 0; j < 4; j++) {
    jBcol = j << 2;
    for (ijA = 3; ijA > -1; ijA += -1) {
      kAcol = ijA << 2;
      if (y[ijA + jBcol] != 0.0) {
        y[ijA + jBcol] /= A[ijA + kAcol];
        for (i = 0; i + 1 <= ijA; i++) {
          y[i + jBcol] -= y[ijA + jBcol] * A[i + kAcol];
        }
      }
    }
  }
}

/*
 * File trailer for inv.c
 *
 * [EOF]
 */
