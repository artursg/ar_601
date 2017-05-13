#ifndef __MAIN_EMXAPI_H__
#define __MAIN_EMXAPI_H__
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "main_types.h"

extern emxArray_real_T *emxCreateND_real_T(int b_numDimensions, int *b_size);
extern emxArray_real_T *emxCreateWrapperND_real_T(double *b_data, int
  b_numDimensions, int *b_size);
extern emxArray_real_T *emxCreateWrapper_real_T(double *b_data, int rows, int
  cols);
extern emxArray_real_T *emxCreate_real_T(int rows, int cols);
extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);
extern void emxInitArray_real_T(emxArray_real_T **pEmxArray, int b_numDimensions);

#endif
