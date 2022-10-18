/*
 * File: imfilter.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "imfilter.h"
#include "ssmDetect_emxutil.h"
#include "ismatrix.h"
#include "convn.h"
#include "rot90.h"
#include "padarray.h"

/* Function Definitions */

/*
 * Arguments    : const double varargin_1[10000]
 *                emxArray_real_T *b
 * Return Type  : void
 */
void b_imfilter(const double varargin_1[10000], emxArray_real_T *b)
{
  emxArray_real_T *a;
  emxArray_real_T *result1;
  double dv8[9];
  static const double h[9] = { 0.0613, 0.1887, 0.0613, 0.1887, 1.0, 0.1887,
    0.0613, 0.1887, 0.0613 };

  int result1_idx_0;
  int i7;
  int i8;
  b_emxInit_real_T(&a, 3);
  b_emxInit_real_T(&result1, 3);
  padarray(varargin_1, a);
  rot90(h, dv8);
  convn(a, dv8, result1);
  if (ismatrix(a)) {
    result1_idx_0 = result1->size[0];
    i7 = b->size[0] * b->size[1] * b->size[2];
    b->size[0] = 50;
    b->size[1] = 50;
    b->size[2] = 1;
    emxEnsureCapacity((emxArray__common *)b, i7, (int)sizeof(double));
    for (i7 = 0; i7 < 50; i7++) {
      for (i8 = 0; i8 < 50; i8++) {
        b->data[i8 + b->size[0] * i7] = result1->data[(i8 + result1_idx_0 * (i7
          + 1)) + 1];
      }
    }
  } else {
    i7 = b->size[0] * b->size[1] * b->size[2];
    b->size[0] = 50;
    b->size[1] = 50;
    b->size[2] = 4;
    emxEnsureCapacity((emxArray__common *)b, i7, (int)sizeof(double));
    for (i7 = 0; i7 < 4; i7++) {
      for (i8 = 0; i8 < 50; i8++) {
        for (result1_idx_0 = 0; result1_idx_0 < 50; result1_idx_0++) {
          b->data[(result1_idx_0 + b->size[0] * i8) + b->size[0] * b->size[1] *
            i7] = result1->data[((result1_idx_0 + result1->size[0] * (i8 + 1)) +
            result1->size[0] * result1->size[1] * i7) + 1];
        }
      }
    }
  }

  emxFree_real_T(&result1);
  emxFree_real_T(&a);
}

/*
 * Arguments    : const double varargin_1[10000]
 *                emxArray_real_T *b
 * Return Type  : void
 */
void imfilter(const double varargin_1[10000], emxArray_real_T *b)
{
  emxArray_real_T *a;
  emxArray_real_T *result1;
  double dv7[9];
  static const double h[9] = { 0.0613, 0.1887, 0.0613, 0.1887, 0.0, 0.1887,
    0.0613, 0.1887, 0.0613 };

  int result1_idx_0;
  int i4;
  int i5;
  b_emxInit_real_T(&a, 3);
  b_emxInit_real_T(&result1, 3);
  padarray(varargin_1, a);
  rot90(h, dv7);
  convn(a, dv7, result1);
  if (ismatrix(a)) {
    result1_idx_0 = result1->size[0];
    i4 = b->size[0] * b->size[1] * b->size[2];
    b->size[0] = 50;
    b->size[1] = 50;
    b->size[2] = 1;
    emxEnsureCapacity((emxArray__common *)b, i4, (int)sizeof(double));
    for (i4 = 0; i4 < 50; i4++) {
      for (i5 = 0; i5 < 50; i5++) {
        b->data[i5 + b->size[0] * i4] = result1->data[(i5 + result1_idx_0 * (i4
          + 1)) + 1];
      }
    }
  } else {
    i4 = b->size[0] * b->size[1] * b->size[2];
    b->size[0] = 50;
    b->size[1] = 50;
    b->size[2] = 4;
    emxEnsureCapacity((emxArray__common *)b, i4, (int)sizeof(double));
    for (i4 = 0; i4 < 4; i4++) {
      for (i5 = 0; i5 < 50; i5++) {
        for (result1_idx_0 = 0; result1_idx_0 < 50; result1_idx_0++) {
          b->data[(result1_idx_0 + b->size[0] * i5) + b->size[0] * b->size[1] *
            i4] = result1->data[((result1_idx_0 + result1->size[0] * (i5 + 1)) +
            result1->size[0] * result1->size[1] * i4) + 1];
        }
      }
    }
  }

  emxFree_real_T(&result1);
  emxFree_real_T(&a);
}

/*
 * File trailer for imfilter.c
 *
 * [EOF]
 */
