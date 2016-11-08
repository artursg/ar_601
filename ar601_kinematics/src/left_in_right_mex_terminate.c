/*
 * left_in_right_mex_terminate.c
 *
 * Code generation for function 'left_in_right_mex_terminate'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "left_in_right.h"
#include "right_in_left.h"
#include "left_in_right_mex_terminate.h"

/* Function Definitions */
void left_in_right_mex_atexit(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

void left_in_right_mex_terminate(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (left_in_right_mex_terminate.c) */
