/*
 * File: ik_left.h
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 27-Apr-2016 13:07:02
 */

#ifndef __IK_LEFT_H__
#define __IK_LEFT_H__

/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "ik_left_12_types.h"

/* Function Declarations */
extern void ik_left(double x, double y, double z, double R[16], double xt,
                    double yt, double zt, const double Rt[16], double angles[6]);

#endif

/*
 * File trailer for ik_left.h
 *
 * [EOF]
 */
