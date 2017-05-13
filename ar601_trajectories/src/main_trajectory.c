
/*
 * File: main.c
 *
 * MATLAB Coder version            : 2.8
 * C/C++ source code generated on  : 22-Jun-2016 08:09:34
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "main_trajectory.h"
#include "f_x.h"
#include "f_zmp_x.h"
#include "f_z.h"
#include "main_emxutil.h"
#include "main_data.h"

/* Function Declarations */
static double rt_atan2d_snf(double u0, double u1);

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_atan2d_snf(double u0, double u1)
{
  double b_y;
  int b_u0;
  int b_u1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    b_y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      b_u0 = 1;
    } else {
      b_u0 = -1;
    }

    if (u1 > 0.0) {
      b_u1 = 1;
    } else {
      b_u1 = -1;
    }

    b_y = atan2(b_u0, b_u1);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      b_y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      b_y = -(double)(RT_PI / 2.0);
    } else {
      b_y = 0.0;
    }
  } else {
    b_y = atan2(u0, u1);
  }

  return b_y;
}

/*
 * Arguments    : emxArray_real_T *x_left
 *                emxArray_real_T *y_left
 *                emxArray_real_T *z_left
 *                emxArray_real_T *teta_left
 *                emxArray_real_T *x_right
 *                emxArray_real_T *y_right
 *                emxArray_real_T *z_right
 *                emxArray_real_T *teta_right
 *                emxArray_real_T *zmp_x
 *                emxArray_real_T *zmp_y
 *                emxArray_real_T *teta_torso
 *                double *a_size
 * Return Type  : void
 */
void main_trajectory(emxArray_real_T *x_left, emxArray_real_T *y_left, emxArray_real_T
          *z_left, emxArray_real_T *teta_left, emxArray_real_T *x_right,
          emxArray_real_T *y_right, emxArray_real_T *z_right, emxArray_real_T
          *teta_right, emxArray_real_T *zmp_x, emxArray_real_T *zmp_y,
          emxArray_real_T *teta_torso, double *a_size)
{
  int i1;
  static const double dv1[101] = { 0.0, 0.031410759078128292,
    0.062790519529313374, 0.094108313318514311, 0.12533323356430426,
    0.15643446504023087, 0.1873813145857246, 0.21814324139654254,
    0.24868988716485479, 0.27899110603922928, 0.3090169943749474,
    0.33873792024529137, 0.36812455268467792, 0.39714789063478062,
    0.42577929156507266, 0.45399049973954675, 0.48175367410171532,
    0.50904141575037132, 0.53582679497899666, 0.56208337785213058,
    0.58778525229247314, 0.61290705365297649, 0.63742398974868963,
    0.66131186532365183, 0.68454710592868862, 0.70710678118654746,
    0.72896862742141155, 0.75011106963045948, 0.77051324277578925,
    0.79015501237569041, 0.80901699437494734, 0.82708057427456183,
    0.84432792550201508, 0.86074202700394364, 0.87630668004386369,
    0.89100652418836779, 0.90482705246601958, 0.91775462568398114,
    0.92977648588825135, 0.94088076895422545, 0.95105651629515353,
    0.960293685676943, 0.96858316112863108, 0.97591676193874732,
    0.98228725072868861, 0.98768834059513777, 0.99211470131447776,
    0.99556196460308, 0.99802672842827156, 0.9995065603657316, 1.0,
    0.9995065603657316, 0.99802672842827156, 0.99556196460308,
    0.99211470131447788, 0.98768834059513777, 0.98228725072868872,
    0.97591676193874743, 0.96858316112863108, 0.96029368567694307,
    0.95105651629515364, 0.94088076895422545, 0.92977648588825146,
    0.91775462568398114, 0.90482705246601947, 0.8910065241883679,
    0.87630668004386347, 0.86074202700394364, 0.844327925502015,
    0.82708057427456172, 0.80901699437494745, 0.7901550123756903,
    0.77051324277578925, 0.75011106963045959, 0.72896862742141144,
    0.70710678118654757, 0.68454710592868884, 0.66131186532365183,
    0.63742398974868986, 0.61290705365297637, 0.58778525229247325,
    0.56208337785213081, 0.535826794978997, 0.5090414157503711,
    0.48175367410171521, 0.45399049973954686, 0.42577929156507288,
    0.39714789063478106, 0.36812455268467814, 0.33873792024529131,
    0.30901699437494751, 0.27899110603922955, 0.24868988716485524,
    0.21814324139654276, 0.18738131458572457, 0.15643446504023098,
    0.12533323356430454, 0.094108313318514353, 0.062790519529313582,
    0.031410759078128236, 1.2246467991473532E-16 };

  double left_flag_s;
  double k;
  double x_p;
  double y_p;
  double teta;
  double steps;
  double left[3];
  double right[3];
  double l_max_f;
  double b_k;
  double b_teta;
  boolean_T exitg1;
  double b_x;
  double c_k[4];
  double c_x;
  double res_data[4];
  int32_T exitg2;
  double b_y;
  double a;
  double r;
  double d_k[4];
  emxArray_real_T *x_left_next;
  int loop_ub;
  emxArray_real_T *y_left_next;
  emxArray_real_T *z_left_next;
  emxArray_real_T *teta_left_next;
  emxArray_real_T *x_right_next;
  emxArray_real_T *y_right_next;
  emxArray_real_T *z_right_next;
  emxArray_real_T *teta_right_next;
  emxArray_real_T *zmp_x_next;
  emxArray_real_T *zmp_y_next;
  emxArray_real_T *teta_torso_next;
  int e_k;
  double t;
  int cs;
  emxArray_real_T *b_x_left;
  emxArray_real_T *b_y_left;
  emxArray_real_T *b_z_left;
  emxArray_real_T *b_x_right;
  emxArray_real_T *b_y_right;
  emxArray_real_T *b_z_right;
  double b_zmp_x_next[500];
  double b_zmp_y_next[500];
  l_max = 0.1;
  teta_max = 0.087266462599716474;
  offset = 0.088;
  for (i1 = 0; i1 < 101; i1++) {
    y[i1] = dv1[i1];
    x[i1] = 0;//0.01 * (double)i1;
  }

  /* y=0.02*t; */
  left_flag = 1.0;

  /* center=zeros(1,3); */
  left_flag_s = left_flag;
  k = 1.0;
  x_p = 0.0;
  y_p = 0.0;
  teta = 0.0;
  steps = 1.0;
  left[0] = -offset;
  left[1] = 0.0;
  left[2] = 0.0;
  right[0] = offset;
  right[1] = 0.0;
  right[2] = 0.0;

  /* center(i,:)=[0 0 0]; */
  while (k < 101.0) {
    l_max_f = l_max;
    b_k = k;
    b_teta = 0.0;
    exitg1 = false;
    while ((!exitg1) && (l_max_f >= 0.0)) {
      if (l_max_f <= 1.0E-5) {
        b_x = b_teta - teta;
        c_k[0] = k;
        c_k[1] = x_p;
        c_k[2] = y_p;
        if (b_x < 0.0) {
          c_x = -1.0;
        } else if (b_x > 0.0) {
          c_x = 1.0;
        } else if (b_x == 0.0) {
          c_x = 0.0;
        } else {
          c_x = b_x;
        }

        c_k[3] = teta + teta_max * c_x;
        for (i1 = 0; i1 < 4; i1++) {
          res_data[i1] = c_k[i1];
        }

        exitg1 = true;
      } else {
        do {
          exitg2 = 0;
          b_y = x[(int)b_k - 1] - x_p;
          a = y[(int)b_k - 1] - y_p;
          if ((sqrt(b_y * b_y + a * a) >= l_max_f) || (b_k == 101.0)) {
            exitg2 = 1;
          } else {
            b_k++;
          }
        } while (exitg2 == 0);

        b_y = y[(int)b_k - 1] - y[(int)b_k - 2];
        b_x = x[(int)b_k - 1] - x[(int)b_k - 2];
        r = rt_atan2d_snf(b_y, b_x);
        b_teta = rt_atan2d_snf(b_y, b_x) - 1.5707963267948966;
        if (fabs((r - 1.5707963267948966) - teta) <= teta_max) {
          d_k[0] = b_k;
          d_k[1] = x[(int)b_k - 1];
          d_k[2] = y[(int)b_k - 1];
          d_k[3] = r - 1.5707963267948966;
          for (i1 = 0; i1 < 4; i1++) {
            res_data[i1] = d_k[i1];
          }

          exitg1 = true;
        } else {
          l_max_f -= 0.01;
          b_k = k;
        }
      }
    }

    steps++;

    /* center(i,:)=[res(2) res(3) res(4)]; */
    if (left_flag_s == 1.0) {
      left[0] = res_data[1] - offset * cos(res_data[3]);
      left[1] = res_data[2] - offset * sin(res_data[3]);
      left[2] = res_data[3];
    } else {
      right[0] = res_data[1] + offset * cos(res_data[3]);
      right[1] = res_data[2] + offset * sin(res_data[3]);
      right[2] = res_data[3];
    }

    k = res_data[0];
    x_p = res_data[1];
    y_p = res_data[2];
    teta = res_data[3];
    left_flag_s = -left_flag_s;
  }

  steps++;
  if (left_flag_s == 1.0) {
    left[0] = res_data[1] - offset * cos(res_data[3]);
    left[1] = res_data[2] - offset * sin(res_data[3]);
    left[2] = res_data[3];
  } else {
    right[0] = res_data[1] + offset * cos(res_data[3]);
    right[1] = res_data[2] + offset * sin(res_data[3]);
    right[2] = res_data[3];
  }

  emxInit_real_T(&x_left_next, 2);

  t0 = 10.0;
  p_ds = 0.5;
  h = 0.05;
  i1 = x_left->size[0] * x_left->size[1];
  x_left->size[0] = 1;
  x_left->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)x_left, i1, (int)sizeof(double));
  i1 = y_left->size[0] * y_left->size[1];
  y_left->size[0] = 1;
  y_left->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)y_left, i1, (int)sizeof(double));
  i1 = z_left->size[0] * z_left->size[1];
  z_left->size[0] = 1;
  z_left->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)z_left, i1, (int)sizeof(double));
  i1 = teta_left->size[0] * teta_left->size[1];
  teta_left->size[0] = 1;
  teta_left->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)teta_left, i1, (int)sizeof(double));
  b_y = t0 / 0.004;
  i1 = x_left_next->size[0] * x_left_next->size[1];
  x_left_next->size[0] = 1;
  x_left_next->size[1] = (int)b_y;
  emxEnsureCapacity((emxArray__common *)x_left_next, i1, (int)sizeof(double));
  loop_ub = (int)b_y;
  for (i1 = 0; i1 < loop_ub; i1++) {
    x_left_next->data[i1] = 0.0;
  }

  emxInit_real_T(&y_left_next, 2);
  b_y = t0 / 0.004;
  i1 = y_left_next->size[0] * y_left_next->size[1];
  y_left_next->size[0] = 1;
  y_left_next->size[1] = (int)b_y;
  emxEnsureCapacity((emxArray__common *)y_left_next, i1, (int)sizeof(double));
  loop_ub = (int)b_y;
  for (i1 = 0; i1 < loop_ub; i1++) {
    y_left_next->data[i1] = 0.0;
  }

  emxInit_real_T(&z_left_next, 2);
  b_y = t0 / 0.004;
  i1 = z_left_next->size[0] * z_left_next->size[1];
  z_left_next->size[0] = 1;
  z_left_next->size[1] = (int)b_y;
  emxEnsureCapacity((emxArray__common *)z_left_next, i1, (int)sizeof(double));
  loop_ub = (int)b_y;
  for (i1 = 0; i1 < loop_ub; i1++) {
    z_left_next->data[i1] = 0.0;
  }

  emxInit_real_T(&teta_left_next, 2);
  b_y = t0 / 0.004;
  i1 = teta_left_next->size[0] * teta_left_next->size[1];
  teta_left_next->size[0] = 1;
  teta_left_next->size[1] = (int)b_y;
  emxEnsureCapacity((emxArray__common *)teta_left_next, i1, (int)sizeof(double));
  loop_ub = (int)b_y;
  for (i1 = 0; i1 < loop_ub; i1++) {
    teta_left_next->data[i1] = 0.0;
  }

  emxInit_real_T(&x_right_next, 2);
  i1 = x_right->size[0] * x_right->size[1];
  x_right->size[0] = 1;
  x_right->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)x_right, i1, (int)sizeof(double));
  i1 = y_right->size[0] * y_right->size[1];
  y_right->size[0] = 1;
  y_right->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)y_right, i1, (int)sizeof(double));
  i1 = z_right->size[0] * z_right->size[1];
  z_right->size[0] = 1;
  z_right->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)z_right, i1, (int)sizeof(double));
  i1 = teta_right->size[0] * teta_right->size[1];
  teta_right->size[0] = 1;
  teta_right->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)teta_right, i1, (int)sizeof(double));
  b_y = t0 / 0.004;
  i1 = x_right_next->size[0] * x_right_next->size[1];
  x_right_next->size[0] = 1;
  x_right_next->size[1] = (int)b_y;
  emxEnsureCapacity((emxArray__common *)x_right_next, i1, (int)sizeof(double));
  loop_ub = (int)b_y;
  for (i1 = 0; i1 < loop_ub; i1++) {
    x_right_next->data[i1] = 0.0;
  }

  emxInit_real_T(&y_right_next, 2);
  b_y = t0 / 0.004;
  i1 = y_right_next->size[0] * y_right_next->size[1];
  y_right_next->size[0] = 1;
  y_right_next->size[1] = (int)b_y;
  emxEnsureCapacity((emxArray__common *)y_right_next, i1, (int)sizeof(double));
  loop_ub = (int)b_y;
  for (i1 = 0; i1 < loop_ub; i1++) {
    y_right_next->data[i1] = 0.0;
  }

  emxInit_real_T(&z_right_next, 2);
  b_y = t0 / 0.004;
  i1 = z_right_next->size[0] * z_right_next->size[1];
  z_right_next->size[0] = 1;
  z_right_next->size[1] = (int)b_y;
  emxEnsureCapacity((emxArray__common *)z_right_next, i1, (int)sizeof(double));
  loop_ub = (int)b_y;
  for (i1 = 0; i1 < loop_ub; i1++) {
    z_right_next->data[i1] = 0.0;
  }

  emxInit_real_T(&teta_right_next, 2);
  b_y = t0 / 0.004;
  i1 = teta_right_next->size[0] * teta_right_next->size[1];
  teta_right_next->size[0] = 1;
  teta_right_next->size[1] = (int)b_y;
  emxEnsureCapacity((emxArray__common *)teta_right_next, i1, (int)sizeof(double));
  loop_ub = (int)b_y;
  for (i1 = 0; i1 < loop_ub; i1++) {
    teta_right_next->data[i1] = 0.0;
  }

  emxInit_real_T(&zmp_x_next, 2);
  i1 = zmp_x->size[0] * zmp_x->size[1];
  zmp_x->size[0] = 1;
  zmp_x->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)zmp_x, i1, (int)sizeof(double));
  i1 = zmp_y->size[0] * zmp_y->size[1];
  zmp_y->size[0] = 1;
  zmp_y->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)zmp_y, i1, (int)sizeof(double));
  b_y = t0 / 0.004;
  i1 = zmp_x_next->size[0] * zmp_x_next->size[1];
  zmp_x_next->size[0] = 1;
  zmp_x_next->size[1] = (int)b_y;
  emxEnsureCapacity((emxArray__common *)zmp_x_next, i1, (int)sizeof(double));
  loop_ub = (int)b_y;
  for (i1 = 0; i1 < loop_ub; i1++) {
    zmp_x_next->data[i1] = 0.0;
  }

  emxInit_real_T(&zmp_y_next, 2);
  b_y = t0 / 0.004;
  i1 = zmp_y_next->size[0] * zmp_y_next->size[1];
  zmp_y_next->size[0] = 1;
  zmp_y_next->size[1] = (int)b_y;
  emxEnsureCapacity((emxArray__common *)zmp_y_next, i1, (int)sizeof(double));
  loop_ub = (int)b_y;
  for (i1 = 0; i1 < loop_ub; i1++) {
    zmp_y_next->data[i1] = 0.0;
  }

  emxInit_real_T(&teta_torso_next, 2);
  i1 = teta_torso->size[0] * teta_torso->size[1];
  teta_torso->size[0] = 1;
  teta_torso->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)teta_torso, i1, (int)sizeof(double));
  b_y = t0 / 0.004;
  i1 = teta_torso_next->size[0] * teta_torso_next->size[1];
  teta_torso_next->size[0] = 1;
  teta_torso_next->size[1] = (int)b_y;
  emxEnsureCapacity((emxArray__common *)teta_torso_next, i1, (int)sizeof(double));
  loop_ub = (int)b_y;
  for (i1 = 0; i1 < loop_ub; i1++) {
    teta_torso_next->data[i1] = 0.0;
  }

  for (i1 = 0; i1 < 500; i1++) {
    x_left->data[i1] = left[1];
  }

  for (i1 = 0; i1 < 500; i1++) {
    y_left->data[i1] = -left[0];
  }

  for (i1 = 0; i1 < 500; i1++) {
    z_left->data[i1] = 0.0;
  }

  for (i1 = 0; i1 < 500; i1++) {
    teta_left->data[i1] = 0.0;
  }

  for (i1 = 0; i1 < 500; i1++) {
    x_right->data[i1] = right[1];
  }

  for (i1 = 0; i1 < 500; i1++) {
    y_right->data[i1] = -right[0];
  }

  for (i1 = 0; i1 < 500; i1++) {
    z_right->data[i1] = 0.0;
  }

  for (i1 = 0; i1 < 500; i1++) {
    teta_right->data[i1] = 0.0;
  }

  for (i1 = 0; i1 < 500; i1++) {
    zmp_x->data[i1] = 0.0;
  }

  for (i1 = 0; i1 < 500; i1++) {
    zmp_y->data[i1] = 0.0;
  }

  for (i1 = 0; i1 < 500; i1++) {
    teta_torso->data[i1] = 0.0;
  }

  for (e_k = 0; e_k < (int)(steps - 1.0); e_k++) {
    b_y = t0 / 0.004 - 1.0;
    for (loop_ub = 0; loop_ub < (int)(b_y + 1.0); loop_ub++) {
      t = (double)loop_ub * 0.004;
      x_left_next->data[loop_ub] = f_x(t, left[1], left[1]);
      y_left_next->data[loop_ub] = f_x(t, -left[0], -left[1]);
      z_left_next->data[loop_ub] = f_z(t, left_flag);
      teta_left_next->data[loop_ub] = f_x(t, left[2], left[3]);
      x_right_next->data[loop_ub] = f_x(t, right[1], right[2]);
      y_right_next->data[loop_ub] = f_x(t, -right[0], -right[1]);
      z_right_next->data[loop_ub] = f_z(t, -left_flag);
      teta_right_next->data[loop_ub] = f_x(t, right[2], right[3]);
      zmp_x_next->data[loop_ub] = f_zmp_x(t);
      if (left_flag == 1.0) {
        zmp_y_next->data[loop_ub] = f_zmp_x(t);
      } else {
        zmp_y_next->data[loop_ub] = f_zmp_x(t);
      }

      if (left_flag == 1.0) {
        teta_torso_next->data[loop_ub] = f_x(t, right[2], left[3]);
      } else {
        teta_torso_next->data[loop_ub] = f_x(t, left[2], right[3]);
      }
    }

    loop_ub = x_left->size[1];
    cs = x_left_next->size[1];
    i1 = x_left->size[0] * x_left->size[1];
    x_left->size[1] = loop_ub + cs;
    emxEnsureCapacity((emxArray__common *)x_left, i1, (int)sizeof(double));
    for (i1 = 0; i1 < cs; i1++) {
      x_left->data[loop_ub + i1] = x_left_next->data[i1];
    }

    loop_ub = y_left->size[1];
    cs = y_left_next->size[1];
    i1 = y_left->size[0] * y_left->size[1];
    y_left->size[1] = loop_ub + cs;
    emxEnsureCapacity((emxArray__common *)y_left, i1, (int)sizeof(double));
    for (i1 = 0; i1 < cs; i1++) {
      y_left->data[loop_ub + i1] = y_left_next->data[i1];
    }

    loop_ub = z_left->size[1];
    cs = z_left_next->size[1];
    i1 = z_left->size[0] * z_left->size[1];
    z_left->size[1] = loop_ub + cs;
    emxEnsureCapacity((emxArray__common *)z_left, i1, (int)sizeof(double));
    for (i1 = 0; i1 < cs; i1++) {
      z_left->data[loop_ub + i1] = z_left_next->data[i1];
    }

    loop_ub = teta_left->size[1];
    cs = teta_left_next->size[1];
    i1 = teta_left->size[0] * teta_left->size[1];
    teta_left->size[1] = loop_ub + cs;
    emxEnsureCapacity((emxArray__common *)teta_left, i1, (int)sizeof(double));
    for (i1 = 0; i1 < cs; i1++) {
      teta_left->data[loop_ub + i1] = teta_left_next->data[i1];
    }

    loop_ub = x_right->size[1];
    cs = x_right_next->size[1];
    i1 = x_right->size[0] * x_right->size[1];
    x_right->size[1] = loop_ub + cs;
    emxEnsureCapacity((emxArray__common *)x_right, i1, (int)sizeof(double));
    for (i1 = 0; i1 < cs; i1++) {
      x_right->data[loop_ub + i1] = x_right_next->data[i1];
    }

    loop_ub = y_right->size[1];
    cs = y_right_next->size[1];
    i1 = y_right->size[0] * y_right->size[1];
    y_right->size[1] = loop_ub + cs;
    emxEnsureCapacity((emxArray__common *)y_right, i1, (int)sizeof(double));
    for (i1 = 0; i1 < cs; i1++) {
      y_right->data[loop_ub + i1] = y_right_next->data[i1];
    }

    loop_ub = z_right->size[1];
    cs = z_right_next->size[1];
    i1 = z_right->size[0] * z_right->size[1];
    z_right->size[1] = loop_ub + cs;
    emxEnsureCapacity((emxArray__common *)z_right, i1, (int)sizeof(double));
    for (i1 = 0; i1 < cs; i1++) {
      z_right->data[loop_ub + i1] = z_right_next->data[i1];
    }

    loop_ub = teta_right->size[1];
    cs = teta_right_next->size[1];
    i1 = teta_right->size[0] * teta_right->size[1];
    teta_right->size[1] = loop_ub + cs;
    emxEnsureCapacity((emxArray__common *)teta_right, i1, (int)sizeof(double));
    for (i1 = 0; i1 < cs; i1++) {
      teta_right->data[loop_ub + i1] = teta_right_next->data[i1];
    }

    loop_ub = zmp_x->size[1];
    cs = zmp_x_next->size[1];
    i1 = zmp_x->size[0] * zmp_x->size[1];
    zmp_x->size[1] = loop_ub + cs;
    emxEnsureCapacity((emxArray__common *)zmp_x, i1, (int)sizeof(double));
    for (i1 = 0; i1 < cs; i1++) {
      zmp_x->data[loop_ub + i1] = zmp_x_next->data[i1];
    }

    loop_ub = zmp_y->size[1];
    cs = zmp_y_next->size[1];
    i1 = zmp_y->size[0] * zmp_y->size[1];
    zmp_y->size[1] = loop_ub + cs;
    emxEnsureCapacity((emxArray__common *)zmp_y, i1, (int)sizeof(double));
    for (i1 = 0; i1 < cs; i1++) {
      zmp_y->data[loop_ub + i1] = zmp_y_next->data[i1];
    }

    loop_ub = teta_torso->size[1];
    cs = teta_torso_next->size[1];
    i1 = teta_torso->size[0] * teta_torso->size[1];
    teta_torso->size[1] = loop_ub + cs;
    emxEnsureCapacity((emxArray__common *)teta_torso, i1, (int)sizeof(double));
    for (i1 = 0; i1 < cs; i1++) {
      teta_torso->data[loop_ub + i1] = teta_torso_next->data[i1];
    }

    left_flag = -left_flag;
  }

  emxFree_real_T(&teta_torso_next);
  emxFree_real_T(&zmp_y_next);
  emxFree_real_T(&zmp_x_next);
  emxFree_real_T(&teta_right_next);
  emxFree_real_T(&z_right_next);
  emxFree_real_T(&y_right_next);
  emxFree_real_T(&x_right_next);
  emxFree_real_T(&teta_left_next);
  emxFree_real_T(&z_left_next);
  emxFree_real_T(&y_left_next);
  emxFree_real_T(&x_left_next);
  emxInit_real_T(&b_x_left, 2);
  loop_ub = x_left->size[1] - 1;
  b_y = x_left->data[loop_ub];
  i1 = b_x_left->size[0] * b_x_left->size[1];
  b_x_left->size[0] = 1;
  b_x_left->size[1] = x_left->size[1] + 500;
  emxEnsureCapacity((emxArray__common *)b_x_left, i1, (int)sizeof(double));
  loop_ub = x_left->size[1];
  for (i1 = 0; i1 < loop_ub; i1++) {
    b_x_left->data[b_x_left->size[0] * i1] = x_left->data[x_left->size[0] * i1];
  }

  for (i1 = 0; i1 < 500; i1++) {
    b_x_left->data[b_x_left->size[0] * (i1 + x_left->size[1])] = b_y;
  }

  i1 = x_left->size[0] * x_left->size[1];
  x_left->size[0] = 1;
  x_left->size[1] = b_x_left->size[1];
  emxEnsureCapacity((emxArray__common *)x_left, i1, (int)sizeof(double));
  loop_ub = b_x_left->size[1];
  for (i1 = 0; i1 < loop_ub; i1++) {
    x_left->data[x_left->size[0] * i1] = b_x_left->data[b_x_left->size[0] * i1];
  }

  emxFree_real_T(&b_x_left);
  emxInit_real_T(&b_y_left, 2);
  loop_ub = y_left->size[1] - 1;
  b_y = y_left->data[loop_ub];
  i1 = b_y_left->size[0] * b_y_left->size[1];
  b_y_left->size[0] = 1;
  b_y_left->size[1] = y_left->size[1] + 500;
  emxEnsureCapacity((emxArray__common *)b_y_left, i1, (int)sizeof(double));
  loop_ub = y_left->size[1];
  for (i1 = 0; i1 < loop_ub; i1++) {
    b_y_left->data[b_y_left->size[0] * i1] = y_left->data[y_left->size[0] * i1];
  }

  for (i1 = 0; i1 < 500; i1++) {
    b_y_left->data[b_y_left->size[0] * (i1 + y_left->size[1])] = b_y;
  }

  i1 = y_left->size[0] * y_left->size[1];
  y_left->size[0] = 1;
  y_left->size[1] = b_y_left->size[1];
  emxEnsureCapacity((emxArray__common *)y_left, i1, (int)sizeof(double));
  loop_ub = b_y_left->size[1];
  for (i1 = 0; i1 < loop_ub; i1++) {
    y_left->data[y_left->size[0] * i1] = b_y_left->data[b_y_left->size[0] * i1];
  }

  emxFree_real_T(&b_y_left);
  emxInit_real_T(&b_z_left, 2);
  loop_ub = z_left->size[1] - 1;
  b_y = z_left->data[loop_ub];
  i1 = b_z_left->size[0] * b_z_left->size[1];
  b_z_left->size[0] = 1;
  b_z_left->size[1] = z_left->size[1] + 500;
  emxEnsureCapacity((emxArray__common *)b_z_left, i1, (int)sizeof(double));
  loop_ub = z_left->size[1];
  for (i1 = 0; i1 < loop_ub; i1++) {
    b_z_left->data[b_z_left->size[0] * i1] = z_left->data[z_left->size[0] * i1];
  }

  for (i1 = 0; i1 < 500; i1++) {
    b_z_left->data[b_z_left->size[0] * (i1 + z_left->size[1])] = b_y;
  }

  i1 = z_left->size[0] * z_left->size[1];
  z_left->size[0] = 1;
  z_left->size[1] = b_z_left->size[1];
  emxEnsureCapacity((emxArray__common *)z_left, i1, (int)sizeof(double));
  loop_ub = b_z_left->size[1];
  for (i1 = 0; i1 < loop_ub; i1++) {
    z_left->data[z_left->size[0] * i1] = b_z_left->data[b_z_left->size[0] * i1];
  }

  emxFree_real_T(&b_z_left);
  loop_ub = teta_left->size[1];
  i1 = teta_left->size[0] * teta_left->size[1];
  teta_left->size[1] = loop_ub + 500;
  emxEnsureCapacity((emxArray__common *)teta_left, i1, (int)sizeof(double));
  for (i1 = 0; i1 < 500; i1++) {
    teta_left->data[loop_ub + i1] = 0.0;
  }

  emxInit_real_T(&b_x_right, 2);
  loop_ub = x_right->size[1] - 1;
  b_y = x_right->data[loop_ub];
  i1 = b_x_right->size[0] * b_x_right->size[1];
  b_x_right->size[0] = 1;
  b_x_right->size[1] = x_right->size[1] + 500;
  emxEnsureCapacity((emxArray__common *)b_x_right, i1, (int)sizeof(double));
  loop_ub = x_right->size[1];
  for (i1 = 0; i1 < loop_ub; i1++) {
    b_x_right->data[b_x_right->size[0] * i1] = x_right->data[x_right->size[0] *
      i1];
  }

  for (i1 = 0; i1 < 500; i1++) {
    b_x_right->data[b_x_right->size[0] * (i1 + x_right->size[1])] = b_y;
  }

  i1 = x_right->size[0] * x_right->size[1];
  x_right->size[0] = 1;
  x_right->size[1] = b_x_right->size[1];
  emxEnsureCapacity((emxArray__common *)x_right, i1, (int)sizeof(double));
  loop_ub = b_x_right->size[1];
  for (i1 = 0; i1 < loop_ub; i1++) {
    x_right->data[x_right->size[0] * i1] = b_x_right->data[b_x_right->size[0] *
      i1];
  }

  emxFree_real_T(&b_x_right);
  emxInit_real_T(&b_y_right, 2);
  loop_ub = y_right->size[1] - 1;
  b_y = y_right->data[loop_ub];
  i1 = b_y_right->size[0] * b_y_right->size[1];
  b_y_right->size[0] = 1;
  b_y_right->size[1] = y_right->size[1] + 500;
  emxEnsureCapacity((emxArray__common *)b_y_right, i1, (int)sizeof(double));
  loop_ub = y_right->size[1];
  for (i1 = 0; i1 < loop_ub; i1++) {
    b_y_right->data[b_y_right->size[0] * i1] = y_right->data[y_right->size[0] *
      i1];
  }

  for (i1 = 0; i1 < 500; i1++) {
    b_y_right->data[b_y_right->size[0] * (i1 + y_right->size[1])] = b_y;
  }

  i1 = y_right->size[0] * y_right->size[1];
  y_right->size[0] = 1;
  y_right->size[1] = b_y_right->size[1];
  emxEnsureCapacity((emxArray__common *)y_right, i1, (int)sizeof(double));
  loop_ub = b_y_right->size[1];
  for (i1 = 0; i1 < loop_ub; i1++) {
    y_right->data[y_right->size[0] * i1] = b_y_right->data[b_y_right->size[0] *
      i1];
  }

  emxFree_real_T(&b_y_right);
  emxInit_real_T(&b_z_right, 2);
  loop_ub = z_right->size[1] - 1;
  b_y = z_right->data[loop_ub];
  i1 = b_z_right->size[0] * b_z_right->size[1];
  b_z_right->size[0] = 1;
  b_z_right->size[1] = z_right->size[1] + 500;
  emxEnsureCapacity((emxArray__common *)b_z_right, i1, (int)sizeof(double));
  loop_ub = z_right->size[1];
  for (i1 = 0; i1 < loop_ub; i1++) {
    b_z_right->data[b_z_right->size[0] * i1] = z_right->data[z_right->size[0] *
      i1];
  }

  for (i1 = 0; i1 < 500; i1++) {
    b_z_right->data[b_z_right->size[0] * (i1 + z_right->size[1])] = b_y;
  }

  i1 = z_right->size[0] * z_right->size[1];
  z_right->size[0] = 1;
  z_right->size[1] = b_z_right->size[1];
  emxEnsureCapacity((emxArray__common *)z_right, i1, (int)sizeof(double));
  loop_ub = b_z_right->size[1];
  for (i1 = 0; i1 < loop_ub; i1++) {
    z_right->data[z_right->size[0] * i1] = b_z_right->data[b_z_right->size[0] *
      i1];
  }

  emxFree_real_T(&b_z_right);
  loop_ub = teta_right->size[1];
  i1 = teta_right->size[0] * teta_right->size[1];
  teta_right->size[1] = loop_ub + 500;
  emxEnsureCapacity((emxArray__common *)teta_right, i1, (int)sizeof(double));
  for (i1 = 0; i1 < 500; i1++) {
    teta_right->data[loop_ub + i1] = 0.0;
  }

  loop_ub = teta_torso->size[1];
  i1 = teta_torso->size[0] * teta_torso->size[1];
  teta_torso->size[1] = loop_ub + 500;
  emxEnsureCapacity((emxArray__common *)teta_torso, i1, (int)sizeof(double));
  for (i1 = 0; i1 < 500; i1++) {
    teta_torso->data[loop_ub + i1] = 0.0;
  }

  for (loop_ub = 0; loop_ub < 500; loop_ub++) {
    t = (double)loop_ub * 0.004;
    b_zmp_x_next[loop_ub] = f_zmp_x(t);
    b_zmp_y_next[loop_ub] = f_zmp_x(t);
  }

  loop_ub = zmp_x->size[1];
  i1 = zmp_x->size[0] * zmp_x->size[1];
  zmp_x->size[1] = loop_ub + 500;
  emxEnsureCapacity((emxArray__common *)zmp_x, i1, (int)sizeof(double));
  for (i1 = 0; i1 < 500; i1++) {
    zmp_x->data[loop_ub + i1] = b_zmp_x_next[i1];
  }

  loop_ub = zmp_y->size[1];
  i1 = zmp_y->size[0] * zmp_y->size[1];
  zmp_y->size[1] = loop_ub + 500;
  emxEnsureCapacity((emxArray__common *)zmp_y, i1, (int)sizeof(double));
  for (i1 = 0; i1 < 500; i1++) {
    zmp_y->data[loop_ub + i1] = b_zmp_y_next[i1];
  }

  *a_size = zmp_x->size[1];

  /* zmp_x=[zmp_x,ones(1,t_preview/T)*zmp_x(length(zmp_x))]; */
  /* zmp_y=[zmp_y,ones(1,t_preview/T)*zmp_y(length(zmp_y))]; */
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
