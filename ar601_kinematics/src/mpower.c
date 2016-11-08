/*
 * File: mpower.c
 *
 * MATLAB Coder version            : 2.8
 * C/C++ source code generated on  : 23-Jun-2016 07:20:40
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ik_right_12.h"
#include "mpower.h"
#include "inv.h"

/* Function Definitions */

/*
 * Arguments    : const double a[16]
 *                double c[16]
 * Return Type  : void
 */
void mpower(const double a[16], double c[16])
{
  invNxN(a, c);
}

/*
 * File trailer for mpower.c
 *
 * [EOF]
 */
