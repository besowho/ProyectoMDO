/*
 * File: eml_sort.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "eml_sort.h"
#include "ssmDetect_emxutil.h"

/* Function Declarations */
static void c_eml_sort(const emxArray_real_T *x, int dim, emxArray_real_T *y,
  emxArray_int32_T *idx);

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                int dim
 *                emxArray_real_T *y
 *                emxArray_int32_T *idx
 * Return Type  : void
 */
static void c_eml_sort(const emxArray_real_T *x, int dim, emxArray_real_T *y,
  emxArray_int32_T *idx)
{
  int vlen;
  emxArray_real_T *vwork;
  int ix;
  unsigned int unnamed_idx_0;
  int vstride;
  int k;
  int i1;
  int j;
  emxArray_int32_T *iidx;
  emxArray_int32_T *idx0;
  int n;
  boolean_T p;
  int i2;
  int b_j;
  int pEnd;
  int b_p;
  int q;
  int qEnd;
  int kEnd;
  if (dim <= 1) {
    vlen = x->size[0];
  } else {
    vlen = 1;
  }

  c_emxInit_real_T(&vwork, 1);
  ix = vwork->size[0];
  vwork->size[0] = vlen;
  emxEnsureCapacity((emxArray__common *)vwork, ix, (int)sizeof(double));
  ix = y->size[0];
  y->size[0] = x->size[0];
  emxEnsureCapacity((emxArray__common *)y, ix, (int)sizeof(double));
  unnamed_idx_0 = (unsigned int)x->size[0];
  ix = idx->size[0];
  idx->size[0] = (int)unnamed_idx_0;
  emxEnsureCapacity((emxArray__common *)idx, ix, (int)sizeof(int));
  vstride = 1;
  k = 1;
  while (k <= dim - 1) {
    vstride *= x->size[0];
    k = 2;
  }

  i1 = -1;
  j = 1;
  b_emxInit_int32_T(&iidx, 1);
  b_emxInit_int32_T(&idx0, 1);
  while (j <= vstride) {
    i1++;
    ix = i1;
    for (k = 0; k < vlen; k++) {
      vwork->data[k] = x->data[ix];
      ix += vstride;
    }

    n = vwork->size[0];
    unnamed_idx_0 = (unsigned int)vwork->size[0];
    ix = iidx->size[0];
    iidx->size[0] = (int)unnamed_idx_0;
    emxEnsureCapacity((emxArray__common *)iidx, ix, (int)sizeof(int));
    if (vwork->size[0] == 0) {
      for (k = 1; k <= n; k++) {
        iidx->data[k - 1] = k;
      }
    } else {
      for (k = 1; k <= n; k++) {
        iidx->data[k - 1] = k;
      }

      for (k = 1; k <= n - 1; k += 2) {
        if ((vwork->data[k - 1] >= vwork->data[k]) || rtIsNaN(vwork->data[k - 1]))
        {
          p = true;
        } else {
          p = false;
        }

        if (p) {
        } else {
          iidx->data[k - 1] = k + 1;
          iidx->data[k] = k;
        }
      }

      ix = idx0->size[0];
      idx0->size[0] = vwork->size[0];
      emxEnsureCapacity((emxArray__common *)idx0, ix, (int)sizeof(int));
      i2 = vwork->size[0];
      for (ix = 0; ix < i2; ix++) {
        idx0->data[ix] = 1;
      }

      ix = 2;
      while (ix < n) {
        i2 = ix << 1;
        b_j = 1;
        for (pEnd = 1 + ix; pEnd < n + 1; pEnd = qEnd + ix) {
          b_p = b_j - 1;
          q = pEnd;
          qEnd = b_j + i2;
          if (qEnd > n + 1) {
            qEnd = n + 1;
          }

          k = 0;
          kEnd = qEnd - b_j;
          while (k + 1 <= kEnd) {
            if ((vwork->data[iidx->data[b_p] - 1] >= vwork->data[iidx->data[q -
                 1] - 1]) || rtIsNaN(vwork->data[iidx->data[b_p] - 1])) {
              p = true;
            } else {
              p = false;
            }

            if (p) {
              idx0->data[k] = iidx->data[b_p];
              b_p++;
              if (b_p + 1 == pEnd) {
                while (q < qEnd) {
                  k++;
                  idx0->data[k] = iidx->data[q - 1];
                  q++;
                }
              }
            } else {
              idx0->data[k] = iidx->data[q - 1];
              q++;
              if (q == qEnd) {
                while (b_p + 1 < pEnd) {
                  k++;
                  idx0->data[k] = iidx->data[b_p];
                  b_p++;
                }
              }
            }

            k++;
          }

          for (k = 0; k + 1 <= kEnd; k++) {
            iidx->data[(b_j + k) - 1] = idx0->data[k];
          }

          b_j = qEnd;
        }

        ix = i2;
      }
    }

    ix = i1;
    for (k = 0; k < vlen; k++) {
      y->data[ix] = vwork->data[iidx->data[k] - 1];
      idx->data[ix] = iidx->data[k];
      ix += vstride;
    }

    j++;
  }

  emxFree_int32_T(&idx0);
  emxFree_int32_T(&iidx);
  emxFree_real_T(&vwork);
}

/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_real_T *y
 *                emxArray_int32_T *idx
 * Return Type  : void
 */
void b_eml_sort(const emxArray_real_T *x, emxArray_real_T *y, emxArray_int32_T
                *idx)
{
  int dim;
  dim = 2;
  if (x->size[0] != 1) {
    dim = 1;
  }

  c_eml_sort(x, dim, y, idx);
}

/*
 * Arguments    : const double x[2500]
 *                double y[2500]
 * Return Type  : void
 */
void eml_sort(const double x[2500], double y[2500])
{
  short idx[2500];
  int k;
  boolean_T p;
  short idx0[2500];
  int i;
  int i2;
  int j;
  int pEnd;
  int b_p;
  int q;
  int qEnd;
  int kEnd;
  for (k = 0; k < 2500; k++) {
    idx[k] = (short)(k + 1);
  }

  for (k = 0; k < 2500; k += 2) {
    if ((x[k] <= x[k + 1]) || rtIsNaN(x[k + 1])) {
      p = true;
    } else {
      p = false;
    }

    if (p) {
    } else {
      idx[k] = (short)(k + 2);
      idx[k + 1] = (short)(k + 1);
    }
  }

  for (i = 0; i < 2500; i++) {
    idx0[i] = 1;
  }

  i = 2;
  while (i < 2500) {
    i2 = i << 1;
    j = 1;
    for (pEnd = 1 + i; pEnd < 2501; pEnd = qEnd + i) {
      b_p = j;
      q = pEnd - 1;
      qEnd = j + i2;
      if (qEnd > 2501) {
        qEnd = 2501;
      }

      k = 0;
      kEnd = qEnd - j;
      while (k + 1 <= kEnd) {
        if ((x[idx[b_p - 1] - 1] <= x[idx[q] - 1]) || rtIsNaN(x[idx[q] - 1])) {
          p = true;
        } else {
          p = false;
        }

        if (p) {
          idx0[k] = idx[b_p - 1];
          b_p++;
          if (b_p == pEnd) {
            while (q + 1 < qEnd) {
              k++;
              idx0[k] = idx[q];
              q++;
            }
          }
        } else {
          idx0[k] = idx[q];
          q++;
          if (q + 1 == qEnd) {
            while (b_p < pEnd) {
              k++;
              idx0[k] = idx[b_p - 1];
              b_p++;
            }
          }
        }

        k++;
      }

      for (k = 0; k + 1 <= kEnd; k++) {
        idx[(j + k) - 1] = idx0[k];
      }

      j = qEnd;
    }

    i = i2;
  }

  for (k = 0; k < 2500; k++) {
    y[k] = x[idx[k] - 1];
  }
}

/*
 * File trailer for eml_sort.c
 *
 * [EOF]
 */
