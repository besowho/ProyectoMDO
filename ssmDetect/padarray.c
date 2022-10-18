/*
 * File: padarray.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "padarray.h"
#include "colon.h"
#include "ssmDetect_emxutil.h"

/* Function Declarations */
static double rt_roundd_snf(double u);

/* Function Definitions */

/*
 * Arguments    : double u
 * Return Type  : double
 */
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/*
 * Arguments    : const double varargin_1[10000]
 *                emxArray_real_T *b
 * Return Type  : void
 */
void padarray(const double varargin_1[10000], emxArray_real_T *b)
{
  signed char sizeB[3];
  int idxA[156];
  signed char sizeIdxDir[3];
  int k;
  static const signed char iv0[3] = { 1, 1, 0 };

  int p;
  boolean_T n_too_large;
  double bnew;
  double anew;
  int n;
  static const signed char iv1[3] = { 50, 50, 4 };

  double y_data[2500];
  int i6;
  int nm1d2;
  int b_k;
  int i;
  unsigned int idxDir_data[52];
  unsigned int u0;
  signed char tmp_data[52];
  int b_idxDir_data[52];
  for (k = 0; k < 3; k++) {
    p = iv0[k];
    float_colon_length(iv1[k], &n, &anew, &bnew, &n_too_large);
    if (n > 0) {
      y_data[0] = anew;
      if (n > 1) {
        y_data[n - 1] = bnew;
        i6 = n - 1;
        nm1d2 = i6 >> 1;
        for (b_k = 1; b_k < nm1d2; b_k++) {
          y_data[b_k] = anew + (double)b_k;
          y_data[(n - b_k) - 1] = bnew - (double)b_k;
        }

        if (nm1d2 << 1 == n - 1) {
          y_data[nm1d2] = (anew + bnew) / 2.0;
        } else {
          y_data[nm1d2] = anew + (double)nm1d2;
          y_data[nm1d2 + 1] = bnew - (double)nm1d2;
        }
      }
    }

    i = (iv0[k] + n) + iv0[k];
    nm1d2 = iv0[k];
    i6 = 0;
    while (i6 <= nm1d2 - 1) {
      idxDir_data[0] = 1U;
      i6 = 1;
    }

    for (i6 = 0; i6 < n; i6++) {
      anew = rt_roundd_snf(y_data[i6]);
      if (anew < 4.294967296E+9) {
        if (anew >= 0.0) {
          u0 = (unsigned int)anew;
        } else {
          u0 = 0U;
        }
      } else if (anew >= 4.294967296E+9) {
        u0 = MAX_uint32_T;
      } else {
        u0 = 0U;
      }

      idxDir_data[i6 + p] = u0;
    }

    nm1d2 = iv0[k];
    i6 = 0;
    while (i6 <= nm1d2 - 1) {
      idxDir_data[p + n] = (unsigned int)rt_roundd_snf(iv1[k]);
      i6 = 1;
    }

    sizeIdxDir[k] = (signed char)i;
    nm1d2 = sizeIdxDir[k];
    for (i6 = 0; i6 < nm1d2; i6++) {
      tmp_data[i6] = (signed char)i6;
    }

    for (i6 = 0; i6 < i; i6++) {
      b_idxDir_data[i6] = (int)idxDir_data[i6];
    }

    nm1d2 = sizeIdxDir[k];
    for (i6 = 0; i6 < nm1d2; i6++) {
      idxA[tmp_data[i6] + 52 * k] = b_idxDir_data[i6];
    }

    sizeB[k] = (signed char)(iv1[k] + (iv0[k] << 1));
  }

  i6 = b->size[0] * b->size[1] * b->size[2];
  b->size[0] = sizeB[0];
  b->size[1] = sizeB[1];
  b->size[2] = sizeB[2];
  emxEnsureCapacity((emxArray__common *)b, i6, (int)sizeof(double));
  for (k = 0; k < sizeB[2]; k++) {
    i6 = b->size[1];
    for (nm1d2 = 0; nm1d2 < i6; nm1d2++) {
      b_k = b->size[0];
      for (i = 0; i < b_k; i++) {
        b->data[(i + b->size[0] * nm1d2) + b->size[0] * b->size[1] * k] =
          varargin_1[((idxA[i] + 50 * (idxA[52 + nm1d2] - 1)) + 2500 * (idxA[104
          + k] - 1)) - 1];
      }
    }
  }
}

/*
 * File trailer for padarray.c
 *
 * [EOF]
 */
