/*
 * File: cov.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "cov.h"
#include "ssmDetect_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const double x_data[]
 *                const int x_size[2]
 *                double xy[4]
 * Return Type  : void
 */
void b_cov(const double x_data[], const int x_size[2], double xy[4])
{
  int x_size_idx_0;
  int loop_ub;
  int j;
  static double b_x_data[5000];
  int m;
  double d;
  int fm;
  x_size_idx_0 = x_size[0];
  loop_ub = x_size[0] * x_size[1];
  for (j = 0; j < loop_ub; j++) {
    b_x_data[j] = x_data[j];
  }

  m = x_size[0];
  for (j = 0; j < 4; j++) {
    xy[j] = 0.0;
  }

  if (x_size[0] == 0) {
    for (j = 0; j < 4; j++) {
      xy[j] = rtNaN;
    }
  } else if (x_size[0] == 1) {
  } else {
    for (j = 0; j < 2; j++) {
      d = 0.0;
      for (loop_ub = 1; loop_ub <= m; loop_ub++) {
        d += b_x_data[(loop_ub + x_size_idx_0 * j) - 1];
      }

      d /= (double)x_size[0];
      for (loop_ub = 0; loop_ub + 1 <= m; loop_ub++) {
        b_x_data[loop_ub + x_size_idx_0 * j] -= d;
      }
    }

    fm = x_size[0] - 1;
    for (j = 0; j < 2; j++) {
      d = 0.0;
      for (loop_ub = 0; loop_ub + 1 <= m; loop_ub++) {
        d += b_x_data[loop_ub + x_size_idx_0 * j] * b_x_data[loop_ub +
          x_size_idx_0 * j];
      }

      xy[j + (j << 1)] = d / (double)fm;
      loop_ub = j + 2;
      while (loop_ub < 3) {
        d = 0.0;
        for (loop_ub = 0; loop_ub + 1 <= m; loop_ub++) {
          d += b_x_data[loop_ub + x_size_idx_0] * b_x_data[loop_ub +
            x_size_idx_0 * j];
        }

        xy[1 + (j << 1)] = d / (double)fm;
        xy[2 + j] = xy[1 + (j << 1)];
        loop_ub = 3;
      }
    }
  }
}

/*
 * Arguments    : const emxArray_real_T *x
 *                double xy[25]
 * Return Type  : void
 */
void cov(const emxArray_real_T *x, double xy[25])
{
  emxArray_real_T *b_x;
  int m;
  int loop_ub;
  double d;
  int i;
  int fm;
  int k;
  emxInit_real_T(&b_x, 2);
  m = b_x->size[0] * b_x->size[1];
  b_x->size[0] = x->size[0];
  b_x->size[1] = 5;
  emxEnsureCapacity((emxArray__common *)b_x, m, (int)sizeof(double));
  loop_ub = x->size[0] * x->size[1];
  for (m = 0; m < loop_ub; m++) {
    b_x->data[m] = x->data[m];
  }

  m = x->size[0];
  memset(&xy[0], 0, 25U * sizeof(double));
  if (x->size[0] == 0) {
    for (m = 0; m < 25; m++) {
      xy[m] = rtNaN;
    }
  } else if (x->size[0] == 1) {
  } else {
    for (loop_ub = 0; loop_ub < 5; loop_ub++) {
      d = 0.0;
      for (i = 1; i <= m; i++) {
        d += b_x->data[(i + b_x->size[0] * loop_ub) - 1];
      }

      d /= (double)x->size[0];
      for (i = 0; i + 1 <= m; i++) {
        b_x->data[i + b_x->size[0] * loop_ub] -= d;
      }
    }

    fm = x->size[0] - 1;
    for (loop_ub = 0; loop_ub < 5; loop_ub++) {
      d = 0.0;
      for (k = 0; k + 1 <= m; k++) {
        d += b_x->data[k + b_x->size[0] * loop_ub] * b_x->data[k + b_x->size[0] *
          loop_ub];
      }

      xy[loop_ub + 5 * loop_ub] = d / (double)fm;
      for (i = loop_ub + 1; i + 1 < 6; i++) {
        d = 0.0;
        for (k = 0; k + 1 <= m; k++) {
          d += b_x->data[k + b_x->size[0] * i] * b_x->data[k + b_x->size[0] *
            loop_ub];
        }

        xy[i + 5 * loop_ub] = d / (double)fm;
        xy[loop_ub + 5 * i] = xy[i + 5 * loop_ub];
      }
    }
  }

  emxFree_real_T(&b_x);
}

/*
 * File trailer for cov.c
 *
 * [EOF]
 */
