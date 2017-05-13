/*
 * File: main.h
 *
 * MATLAB Coder version            : 2.8
 * C/C++ source code generated on  : 22-Jun-2016 08:09:34
 */

#ifndef __MAIN_H__
#define __MAIN_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "main_types.h"

/* Function Declarations */
void main_trajectory(emxArray_real_T *x_left, emxArray_real_T *y_left,
                 emxArray_real_T *z_left, emxArray_real_T *teta_left,
                 emxArray_real_T *x_right, emxArray_real_T *y_right,
                 emxArray_real_T *z_right, emxArray_real_T *teta_right,
                 emxArray_real_T *zmp_x, emxArray_real_T *zmp_y, emxArray_real_T *teta_torso, double *a_size);
#endif

/*
 * File trailer for main.h
 *
 * [EOF]
 */
