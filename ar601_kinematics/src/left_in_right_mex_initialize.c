/*
 * left_in_right_mex_initialize.c
 *
 * Code generation for function 'left_in_right_mex_initialize'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "left_in_right.h"
#include "right_in_left.h"
#include "left_in_right_mex_initialize.h"

/* Variable Definitions */
static const volatile char_T *emlrtBreakCheckR2012bFlagVar;

/* Function Definitions */
void left_in_right_mex_initialize(emlrtContext *aContext)
{
  emlrtStack st = { NULL, NULL, NULL };

  emlrtBreakCheckR2012bFlagVar = emlrtGetBreakCheckFlagAddressR2012b();
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, aContext, NULL, 1);
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (left_in_right_mex_initialize.c) */
