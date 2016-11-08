/*
 * File: ik_right.h
 *
 * MATLAB Coder version            : 2.8
 * C/C++ source code generated on  : 23-Jun-2016 07:20:40
 */

#ifndef __IK_RIGHT_H__
#define __IK_RIGHT_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "ik_right_12_types.h"

/* Function Declarations */
extern void ik_right(double x, double y, double z, double R[16], double xt,
                     double yt, double zt, const double Rt[16], double angles[6]);

#endif

/*
 * File trailer for ik_right.h
 *
 * [EOF]
 */
