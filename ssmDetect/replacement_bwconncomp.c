/*
 * File: replacement_bwconncomp.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "replacement_bwconncomp.h"
#include "ssmDetect_emxutil.h"
#include "colon.h"
#include "unique.h"
#include "isequal.h"

/* Function Declarations */
static void b_eml_li_find(const boolean_T x_data[], const int x_size[2], int
  y_data[], int y_size[1]);
static void cast(const emxArray_struct_T *x, emxArray_ConnectedComponent *y);
static int compute_nones(const boolean_T x_data[], int n);
static void eml_sort_idx(const double x_data[], const int x_size[1], int
  idx_data[], int idx_size[1]);
static void label(const boolean_T I_data[], const int I_size[2], double L_data[],
                  int L_size[2], double *num);

/* Function Definitions */

/*
 * Arguments    : const boolean_T x_data[]
 *                const int x_size[2]
 *                int y_data[]
 *                int y_size[1]
 * Return Type  : void
 */
static void b_eml_li_find(const boolean_T x_data[], const int x_size[2], int
  y_data[], int y_size[1])
{
  int n;
  int k;
  int i;
  n = x_size[0] * x_size[1];
  k = compute_nones(x_data, n);
  y_size[0] = k;
  k = 0;
  for (i = 1; i <= n; i++) {
    if (x_data[i - 1]) {
      y_data[k] = i;
      k++;
    }
  }
}

/*
 * Arguments    : const emxArray_struct_T *x
 *                emxArray_ConnectedComponent *y
 * Return Type  : void
 */
static void cast(const emxArray_struct_T *x, emxArray_ConnectedComponent *y)
{
  int j;
  j = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = x->size[1];
  c_emxEnsureCapacity_ConnectedCo(y, j);
  for (j = 0; j < x->size[1]; j++) {
    y->data[j].label = x->data[j].label;
    y->data[j].pixel_idx.size[0] = 0;
    y->data[j].pixel_idx.size[1] = 0;
    y->data[j].area = x->data[j].area;
  }
}

/*
 * Arguments    : const boolean_T x_data[]
 *                int n
 * Return Type  : int
 */
static int compute_nones(const boolean_T x_data[], int n)
{
  int k;
  int i;
  k = 0;
  for (i = 1; i <= n; i++) {
    if (x_data[i - 1]) {
      k++;
    }
  }

  return k;
}

/*
 * Arguments    : const double x_data[]
 *                const int x_size[1]
 *                int idx_data[]
 *                int idx_size[1]
 * Return Type  : void
 */
static void eml_sort_idx(const double x_data[], const int x_size[1], int
  idx_data[], int idx_size[1])
{
  int n;
  int k;
  boolean_T p;
  int i;
  int idx0_data[2500];
  int i2;
  int j;
  int pEnd;
  int b_p;
  int q;
  int qEnd;
  int kEnd;
  n = x_size[0];
  idx_size[0] = (short)x_size[0];
  if (x_size[0] == 0) {
    for (k = 1; k <= n; k++) {
      idx_data[k - 1] = k;
    }
  } else {
    for (k = 1; k <= n; k++) {
      idx_data[k - 1] = k;
    }

    for (k = 1; k <= n - 1; k += 2) {
      if ((x_data[k - 1] <= x_data[k]) || rtIsNaN(x_data[k])) {
        p = true;
      } else {
        p = false;
      }

      if (p) {
      } else {
        idx_data[k - 1] = k + 1;
        idx_data[k] = k;
      }
    }

    k = x_size[0];
    for (i = 0; i < k; i++) {
      idx0_data[i] = 1;
    }

    i = 2;
    while (i < n) {
      i2 = i << 1;
      j = 1;
      for (pEnd = 1 + i; pEnd < n + 1; pEnd = qEnd + i) {
        b_p = j;
        q = pEnd - 1;
        qEnd = j + i2;
        if (qEnd > n + 1) {
          qEnd = n + 1;
        }

        k = 0;
        kEnd = qEnd - j;
        while (k + 1 <= kEnd) {
          if ((x_data[idx_data[b_p - 1] - 1] <= x_data[idx_data[q] - 1]) ||
              rtIsNaN(x_data[idx_data[q] - 1])) {
            p = true;
          } else {
            p = false;
          }

          if (p) {
            idx0_data[k] = idx_data[b_p - 1];
            b_p++;
            if (b_p == pEnd) {
              while (q + 1 < qEnd) {
                k++;
                idx0_data[k] = idx_data[q];
                q++;
              }
            }
          } else {
            idx0_data[k] = idx_data[q];
            q++;
            if (q + 1 == qEnd) {
              while (b_p < pEnd) {
                k++;
                idx0_data[k] = idx_data[b_p - 1];
                b_p++;
              }
            }
          }

          k++;
        }

        for (k = 0; k + 1 <= kEnd; k++) {
          idx_data[(j + k) - 1] = idx0_data[k];
        }

        j = qEnd;
      }

      i = i2;
    }
  }
}

/*
 * LABEL Label connected components in 2-D arrays.
 *    LABEL is a generalization of BWLABEL: BWLABEL works with 2-D binary
 *    images only, whereas LABEL works with 2-D arrays of any class. Use
 *    BWLABEL if the input is binary since BWLABEL will be much faster.
 *
 *    L = LABEL(I,N) returns a matrix L, of the same size as I, containing
 *    labels for the connected components in I. Two adjacent components
 *    (pixels), of respective indexes IDX1 and IDX2, are connected if I(IDX1)
 *    and I(IDX2) are equal.
 *
 *    N can have a value of either 4 or 8, where 4 specifies 4-connected
 *    objects and 8 specifies 8-connected objects; if the argument is
 *    omitted, it defaults to 8.
 *
 *    Important remark:
 *    ----------------
 *    NaN values are ignored and considered as background. Because LABEL
 *    works with arrays of any class, the 0s are NOT considered as the
 *    background.
 *
 *    Note:
 *    ----
 *    The elements of L are integer values greater than or equal to 0. The
 *    pixels labeled 0 are the background (corresponding to the NaN
 *    components of the input array). The pixels labeled 1 make up one
 *    object, the pixels labeled 2 make up a second object, and so on.
 *
 *    [L,NUM] = LABEL(...) returns in NUM the number of connected objects
 *    found in I.
 *
 *    [L,NUM,SZ] = LABEL(...) returns a matrix SZ, of the same size as I,
 *    that contains the sizes of the connected objects. For a pixel whose
 *    index is IDX, we have: SZ(IDX) = NNZ(L==L(IDX)).
 *
 *    Class Support
 *    -------------
 *    I can be logical or numeric. L is double.
 *
 *    Example
 *    -------
 *        I = [3 3 3 0 0 0 0 0
 *             3 3 1 0 6.1 6.1 9 0
 *             1 3 1 3 6.1 6.1 0 0
 *             1 3 1 3 0 0 1 0
 *             1 3 3 3 3 3 1 0
 *             1 3 1 0 0 3 1 0
 *             1 3 1 0 0 1 1 0
 *             1 1 1 1 1 0 0 0];
 *        L4 = label(I,4);
 *        L8 = label(I,8);
 *        subplot(211), imagesc(L4), axis image off
 *        title('Pixels of same color belong to the same region (4-connection)')
 *        subplot(212), imagesc(L8), axis image off
 *        title('Pixels of same color belong to the same region (8-connection)')
 *
 *    Note
 *    ----
 *        % Comparison between BWLABEL and LABEL:
 *        BW = logical([1 1 1 0 0 0 0 0
 *                      1 1 1 0 1 1 0 0
 *                      1 1 1 0 1 1 0 0
 *                      1 1 1 0 0 0 1 0
 *                      1 1 1 0 0 0 1 0
 *                      1 1 1 0 0 0 1 0
 *                      1 1 1 0 0 1 1 0
 *                      1 1 1 0 0 0 0 0]);
 *        L = bwlabel(BW,4);
 *        % The same result can be obtained with LABEL:
 *        BW2 = double(BW);
 *        BW2(~BW) = NaN;
 *        L2 = label(BW2,4);
 *
 *    See also BWLABEL, BWLABELN, LABEL2RGB
 *
 *    -- Damien Garcia -- 2010/02, revised 2011/01
 *    http://www.biomecardio.com
 * Arguments    : const boolean_T I_data[]
 *                const int I_size[2]
 *                double L_data[]
 *                int L_size[2]
 *                double *num
 * Return Type  : void
 */
static void label(const boolean_T I_data[], const int I_size[2], double L_data[],
                  int L_size[2], double *num)
{
  signed char sizI[2];
  int i12;
  boolean_T n_too_large;
  double root1;
  double absxk;
  int k0;
  static double b_I_data[2500];
  int nm1d2;
  int k;
  signed char sz[2];
  static double id_data[2500];
  int id_size[2];
  int loop_ub;
  static double sz_data[2500];
  int b_loop_ub;
  int i13;
  int i14;
  int i15;
  int nb;
  int i16;
  int i17;
  int c_loop_ub;
  static double b_id_data[2500];
  int i18;
  int i19;
  int unnamed_idx_0;
  static double c_id_data[2500];
  double d_id_data[2500];
  int id_size_idx_0;
  emxArray_real_T *idx1;
  int nNaN;
  int j;
  emxArray_real_T *idx2;
  int id0_size[2];
  double id0_data[2500];
  int isNaNI_size[2];
  boolean_T isNaNI_data[2500];
  int ipos_size[1];
  int ipos_data[2500];
  int id[1];
  int idx_size[1];
  int idx_data[2500];
  double x;
  int32_T exitg1;
  int exponent;
  int n_data[2500];
  boolean_T s_data[2500];
  int i20;

  /*  ------------------------------------------------------------------------- */
  /* http://www.mathworks.com/matlabcentral/fileexchange/26946-label-connected-components-in-2-d-array */
  /*  ------------------------------------------------------------------------- */
  /*  Check input arguments */
  /* narginchk(1,2); */
  /* if nargin==1, */
  /*     n=8; */
  /* end */
  /*  */
  /* assert(ismatrix(I),'The input I must be a 2-D array') */
  /*  ----- */
  /*  The Union-Find algorithm is based on the following document: */
  /*  http://www.cs.duke.edu/courses/cps100e/fall09/notes/UnionFind.pdf */
  /*  ----- */
  /*  Initialization of the two arrays (ID & SZ) required during the */
  /*  Union-Find algorithm. */
  for (i12 = 0; i12 < 2; i12++) {
    sizI[i12] = (signed char)I_size[i12];
  }

  float_colon_length(sizI[0] * sizI[1], &k0, &absxk, &root1, &n_too_large);
  if (k0 > 0) {
    b_I_data[0] = absxk;
    if (k0 > 1) {
      b_I_data[k0 - 1] = root1;
      i12 = k0 - 1;
      nm1d2 = i12 >> 1;
      for (k = 1; k < nm1d2; k++) {
        b_I_data[k] = absxk + (double)k;
        b_I_data[(k0 - k) - 1] = root1 - (double)k;
      }

      if (nm1d2 << 1 == k0 - 1) {
        b_I_data[nm1d2] = (absxk + root1) / 2.0;
      } else {
        b_I_data[nm1d2] = absxk + (double)nm1d2;
        b_I_data[nm1d2 + 1] = root1 - (double)nm1d2;
      }
    }
  }

  for (i12 = 0; i12 < 2; i12++) {
    sz[i12] = sizI[i12];
  }

  id_size[0] = sz[0];
  id_size[1] = sz[1];
  for (k = 0; k + 1 <= k0; k++) {
    id_data[k] = b_I_data[k];
  }

  loop_ub = sizI[0] * sizI[1];
  for (i12 = 0; i12 < loop_ub; i12++) {
    sz_data[i12] = 1.0;
  }

  /*  Indexes of the adjacent pixels */
  /* vec = @(x) x(:); */
  /*  8-connected neighborhood */
  if (1 > sz[1] - 1) {
    loop_ub = 0;
  } else {
    loop_ub = sz[1] - 1;
  }

  if (1 > sz[0] - 1) {
    b_loop_ub = 0;
  } else {
    b_loop_ub = sz[0] - 1;
  }

  if (2 > sz[1]) {
    i12 = 0;
    i13 = 0;
  } else {
    i12 = 1;
    i13 = sz[1];
  }

  if (2 > sz[0]) {
    i14 = 0;
    i15 = 0;
  } else {
    i14 = 1;
    i15 = sz[0];
  }

  if (1 > sz[0] - 1) {
    nb = 0;
  } else {
    nb = sz[0] - 1;
  }

  if (1 > sz[1] - 1) {
    k0 = 0;
  } else {
    k0 = sz[1] - 1;
  }

  if (2 > sz[0]) {
    i16 = 0;
    i17 = 0;
  } else {
    i16 = 1;
    i17 = sz[0];
  }

  if (1 > sz[1] - 1) {
    c_loop_ub = 0;
  } else {
    c_loop_ub = sz[1] - 1;
  }

  nm1d2 = sz[0];
  for (i18 = 0; i18 < loop_ub; i18++) {
    for (i19 = 0; i19 < nm1d2; i19++) {
      b_id_data[i19 + nm1d2 * i18] = id_data[i19 + id_size[0] * i18];
    }
  }

  k = sz[0] * loop_ub;
  loop_ub = sz[1];
  for (i18 = 0; i18 < loop_ub; i18++) {
    for (i19 = 0; i19 < b_loop_ub; i19++) {
      b_I_data[i19 + b_loop_ub * i18] = id_data[i19 + id_size[0] * i18];
    }
  }

  unnamed_idx_0 = b_loop_ub * sz[1];
  for (i18 = 0; i18 < k0; i18++) {
    for (i19 = 0; i19 < nb; i19++) {
      c_id_data[i19 + nb * i18] = id_data[i19 + id_size[0] * i18];
    }
  }

  k0 *= nb;
  id_size_idx_0 = i17 - i16;
  for (i18 = 0; i18 < c_loop_ub; i18++) {
    loop_ub = i17 - i16;
    for (i19 = 0; i19 < loop_ub; i19++) {
      d_id_data[i19 + id_size_idx_0 * i18] = id_data[(i16 + i19) + id_size[0] *
        i18];
    }
  }

  c_emxInit_real_T(&idx1, 1);
  nm1d2 = (i17 - i16) * c_loop_ub;
  i16 = idx1->size[0];
  idx1->size[0] = ((k + unnamed_idx_0) + k0) + nm1d2;
  emxEnsureCapacity((emxArray__common *)idx1, i16, (int)sizeof(double));
  for (i16 = 0; i16 < k; i16++) {
    idx1->data[i16] = b_id_data[i16];
  }

  for (i16 = 0; i16 < unnamed_idx_0; i16++) {
    idx1->data[i16 + k] = b_I_data[i16];
  }

  for (i16 = 0; i16 < k0; i16++) {
    idx1->data[(i16 + k) + unnamed_idx_0] = c_id_data[i16];
  }

  for (i16 = 0; i16 < nm1d2; i16++) {
    idx1->data[((i16 + k) + unnamed_idx_0) + k0] = d_id_data[i16];
  }

  if (2 > sz[0]) {
    i16 = 0;
    i17 = 0;
  } else {
    i16 = 1;
    i17 = sz[0];
  }

  if (2 > sz[1]) {
    i18 = 0;
    i19 = 0;
  } else {
    i18 = 1;
    i19 = sz[1];
  }

  if (1 > sz[0] - 1) {
    loop_ub = 0;
  } else {
    loop_ub = sz[0] - 1;
  }

  if (2 > sz[1]) {
    nNaN = 0;
    j = 0;
  } else {
    nNaN = 1;
    j = sz[1];
  }

  b_loop_ub = sz[0];
  nb = i13 - i12;
  for (nm1d2 = 0; nm1d2 < nb; nm1d2++) {
    for (k0 = 0; k0 < b_loop_ub; k0++) {
      b_id_data[k0 + b_loop_ub * nm1d2] = id_data[k0 + id_size[0] * (i12 + nm1d2)];
    }
  }

  k = sz[0] * (i13 - i12);
  b_loop_ub = sz[1];
  id_size_idx_0 = i15 - i14;
  for (i12 = 0; i12 < b_loop_ub; i12++) {
    nb = i15 - i14;
    for (i13 = 0; i13 < nb; i13++) {
      b_I_data[i13 + id_size_idx_0 * i12] = id_data[(i14 + i13) + id_size[0] *
        i12];
    }
  }

  unnamed_idx_0 = (i15 - i14) * sz[1];
  id_size_idx_0 = i17 - i16;
  b_loop_ub = i19 - i18;
  for (i12 = 0; i12 < b_loop_ub; i12++) {
    nb = i17 - i16;
    for (i13 = 0; i13 < nb; i13++) {
      c_id_data[i13 + id_size_idx_0 * i12] = id_data[(i16 + i13) + id_size[0] *
        (i18 + i12)];
    }
  }

  k0 = (i17 - i16) * (i19 - i18);
  b_loop_ub = j - nNaN;
  for (i12 = 0; i12 < b_loop_ub; i12++) {
    for (i13 = 0; i13 < loop_ub; i13++) {
      d_id_data[i13 + loop_ub * i12] = id_data[i13 + id_size[0] * (nNaN + i12)];
    }
  }

  c_emxInit_real_T(&idx2, 1);
  nm1d2 = loop_ub * (j - nNaN);
  i12 = idx2->size[0];
  idx2->size[0] = ((k + unnamed_idx_0) + k0) + nm1d2;
  emxEnsureCapacity((emxArray__common *)idx2, i12, (int)sizeof(double));
  for (i12 = 0; i12 < k; i12++) {
    idx2->data[i12] = b_id_data[i12];
  }

  for (i12 = 0; i12 < unnamed_idx_0; i12++) {
    idx2->data[i12 + k] = b_I_data[i12];
  }

  for (i12 = 0; i12 < k0; i12++) {
    idx2->data[(i12 + k) + unnamed_idx_0] = c_id_data[i12];
  }

  for (i12 = 0; i12 < nm1d2; i12++) {
    idx2->data[((i12 + k) + unnamed_idx_0) + k0] = d_id_data[i12];
  }

  /*  Create the groups and merge them (Union/Find Algorithm) */
  for (k = 0; k < idx1->size[0]; k++) {
    root1 = idx1->data[k];
    absxk = idx2->data[k];
    while (root1 != id_data[(int)root1 - 1]) {
      id_data[(int)root1 - 1] = id_data[(int)id_data[(int)root1 - 1] - 1];
      root1 = id_data[(int)root1 - 1];
    }

    while (absxk != id_data[(int)absxk - 1]) {
      id_data[(int)absxk - 1] = id_data[(int)id_data[(int)absxk - 1] - 1];
      absxk = id_data[(int)absxk - 1];
    }

    if ((root1 == absxk) || (!(I_data[(int)root1 - 1] == I_data[(int)absxk - 1])))
    {
    } else {
      /*  (The two pixels belong to the same group) */
      /*  size of the group belonging to root1 */
      /*  size of the group belonging to root2 */
      /*  then merge the two groups */
      if (sz_data[(int)root1 - 1] < sz_data[(int)absxk - 1]) {
        id_data[(int)root1 - 1] = absxk;
        sz_data[(int)absxk - 1] += sz_data[(int)root1 - 1];
      } else {
        id_data[(int)absxk - 1] = root1;
        sz_data[(int)root1 - 1] += sz_data[(int)absxk - 1];
      }
    }
  }

  emxFree_real_T(&idx2);
  emxFree_real_T(&idx1);
  do {
    id0_size[0] = id_size[0];
    id0_size[1] = id_size[1];
    loop_ub = id_size[0] * id_size[1];
    for (i12 = 0; i12 < loop_ub; i12++) {
      id0_data[i12] = id_data[i12];
    }

    id_size_idx_0 = id_size[0];
    unnamed_idx_0 = id_size[1];
    loop_ub = id_size[1];
    for (i12 = 0; i12 < loop_ub; i12++) {
      b_loop_ub = id_size[0];
      for (i13 = 0; i13 < b_loop_ub; i13++) {
        b_id_data[i13 + id_size_idx_0 * i12] = id_data[(int)id_data[i13 +
          id_size[0] * i12] - 1];
      }
    }

    id_size[1] = unnamed_idx_0;
    for (i12 = 0; i12 < unnamed_idx_0; i12++) {
      for (i13 = 0; i13 < id_size_idx_0; i13++) {
        id_data[i13 + id_size[0] * i12] = b_id_data[i13 + id_size_idx_0 * i12];
      }
    }
  } while (!isequal(id0_data, id0_size, id_data, id_size));

  /*  Label matrix */
  /* isNaNI = isnan(I); */
  isNaNI_size[0] = I_size[0];
  isNaNI_size[1] = I_size[1];
  loop_ub = I_size[0] * I_size[1];
  for (i12 = 0; i12 < loop_ub; i12++) {
    isNaNI_data[i12] = (I_data[i12] == 0);
  }

  /*  We operate on logicals */
  b_eml_li_find(isNaNI_data, isNaNI_size, ipos_data, ipos_size);
  loop_ub = ipos_size[0];
  for (i12 = 0; i12 < loop_ub; i12++) {
    id_data[ipos_data[i12] - 1] = rtNaN;
  }

  ipos_size[0] = id_size[0] * unnamed_idx_0;
  id[0] = id_size_idx_0 * unnamed_idx_0;
  eml_sort_idx(id_data, id, idx_data, idx_size);
  for (k = 0; k + 1 <= id_size[0] * unnamed_idx_0; k++) {
    b_id_data[k] = id_data[idx_data[k] - 1];
  }

  count_nonfinites(b_id_data, id_size[0] * unnamed_idx_0, &k, &nm1d2, &c_loop_ub,
                   &nNaN);
  nb = -1;
  if (k > 0) {
    nb = 0;
    for (j = 1; j <= k; j++) {
      ipos_data[idx_data[j - 1] - 1] = 1;
    }
  }

  nm1d2 += k;
  while (k + 1 <= nm1d2) {
    x = b_id_data[k];
    k0 = k;
    do {
      exitg1 = 0;
      k++;
      if (k + 1 > nm1d2) {
        exitg1 = 1;
      } else {
        absxk = x / 2.0;
        if ((!rtIsInf(absxk)) && (!rtIsNaN(absxk))) {
          if (absxk <= 2.2250738585072014E-308) {
            root1 = 4.94065645841247E-324;
          } else {
            frexp(absxk, &exponent);
            root1 = ldexp(1.0, exponent - 53);
          }
        } else {
          root1 = rtNaN;
        }

        if ((fabs(x - b_id_data[k]) < root1) || (rtIsInf(b_id_data[k]) &&
             rtIsInf(x) && ((b_id_data[k] > 0.0) == (x > 0.0)))) {
          n_too_large = true;
        } else {
          n_too_large = false;
        }

        if (!n_too_large) {
          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);

    nb++;
    b_id_data[nb] = x;
    for (j = k0 + 1; j <= k; j++) {
      ipos_data[idx_data[j - 1] - 1] = nb + 1;
    }

    idx_data[nb] = idx_data[k0];
  }

  if (c_loop_ub > 0) {
    nb++;
    b_id_data[nb] = b_id_data[nm1d2];
    for (j = 1; j <= c_loop_ub; j++) {
      ipos_data[idx_data[(nm1d2 + j) - 1] - 1] = nb + 1;
    }

    idx_data[nb] = idx_data[nm1d2];
  }

  k = (nm1d2 + c_loop_ub) - 1;
  for (j = 1; j <= nNaN; j++) {
    nb++;
    b_id_data[nb] = b_id_data[k + j];
    ipos_data[idx_data[k + j] - 1] = nb + 1;
    idx_data[nb] = idx_data[k + j];
  }

  if (1 > nb + 1) {
    i12 = -1;
  } else {
    i12 = nb;
  }

  loop_ub = id_size_idx_0 * unnamed_idx_0;
  for (i13 = 0; i13 < loop_ub; i13++) {
    n_data[i13] = ipos_data[i13];
  }

  float_colon_length(i12 + 1, &k0, &absxk, &root1, &n_too_large);
  if (k0 > 0) {
    b_I_data[0] = absxk;
    if (k0 > 1) {
      b_I_data[k0 - 1] = root1;
      i13 = k0 - 1;
      nm1d2 = i13 >> 1;
      for (k = 1; k < nm1d2; k++) {
        b_I_data[k] = absxk + (double)k;
        b_I_data[(k0 - k) - 1] = root1 - (double)k;
      }

      if (nm1d2 << 1 == k0 - 1) {
        b_I_data[nm1d2] = (absxk + root1) / 2.0;
      } else {
        b_I_data[nm1d2] = absxk + (double)nm1d2;
        b_I_data[nm1d2 + 1] = root1 - (double)nm1d2;
      }
    }
  }

  for (i13 = 0; i13 < 2; i13++) {
    sz[i13] = sizI[i13];
  }

  L_size[0] = sz[0];
  L_size[1] = sz[1];
  for (k = 0; k + 1 <= ipos_size[0]; k++) {
    L_data[k] = b_I_data[n_data[k] - 1];
  }

  b_eml_li_find(isNaNI_data, isNaNI_size, ipos_data, ipos_size);
  loop_ub = ipos_size[0];
  for (i13 = 0; i13 < loop_ub; i13++) {
    L_data[ipos_data[i13] - 1] = 0.0;
  }

  loop_ub = i12 + 1;
  for (i13 = 0; i13 < loop_ub; i13++) {
    s_data[i13] = rtIsNaN(b_id_data[i13]);
  }

  if (1 > nb + 1) {
    i20 = -1;
  } else {
    i20 = nb;
  }

  loop_ub = i20 + 1;
  for (i13 = 0; i13 < loop_ub; i13++) {
    s_data[i13] = !s_data[i13];
  }

  k0 = 0;
  for (k = 0; k <= i12; k++) {
    if (s_data[k]) {
      k0++;
    }
  }

  *num = k0;
}

/*
 * A MATLAB Coder friendly implementation of BWCONNCOMP
 * Arguments    : const boolean_T I_data[]
 *                const int I_size[2]
 *                emxArray_ConnectedComponent *CC
 * Return Type  : void
 */
void replacement_bwconncomp(const boolean_T I_data[], const int I_size[2],
  emxArray_ConnectedComponent *CC)
{
  emxArray_struct_T *r3;
  double num;
  int L_size[2];
  static double L_data[2500];
  int idx;
  int loop_ub;
  static const struct_T r4 = { 0.0, 0.0 };

  int i;
  int x_size_idx_0;
  boolean_T x_data[2500];
  int ii_data[2500];
  boolean_T exitg1;
  boolean_T guard1 = false;
  int tmp_data[2500];
  emxInit_struct_T(&r3, 2);

  /*  Use label implementation to label connected components */
  label(I_data, I_size, L_data, L_size, &num);
  idx = r3->size[0] * r3->size[1];
  r3->size[0] = 1;
  r3->size[1] = (int)num;
  emxEnsureCapacity((emxArray__common *)r3, idx, (int)sizeof(struct_T));
  loop_ub = (int)num;
  for (idx = 0; idx < loop_ub; idx++) {
    r3->data[idx] = r4;
  }

  cast(r3, CC);
  i = 0;
  emxFree_struct_T(&r3);
  while (i <= (int)num - 1) {
    CC->data[i].label = 1.0 + (double)i;
    x_size_idx_0 = L_size[0] * L_size[1];
    loop_ub = L_size[0] * L_size[1];
    for (idx = 0; idx < loop_ub; idx++) {
      x_data[idx] = (L_data[idx] == 1.0 + (double)i);
    }

    idx = 0;
    loop_ub = 1;
    exitg1 = false;
    while ((!exitg1) && (loop_ub <= x_size_idx_0)) {
      guard1 = false;
      if (x_data[loop_ub - 1]) {
        idx++;
        ii_data[idx - 1] = loop_ub;
        if (idx >= x_size_idx_0) {
          exitg1 = true;
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }

      if (guard1) {
        loop_ub++;
      }
    }

    if (x_size_idx_0 == 1) {
      if (idx == 0) {
        x_size_idx_0 = 0;
      }
    } else if (1 > idx) {
      x_size_idx_0 = 0;
    } else {
      x_size_idx_0 = idx;
    }

    for (idx = 0; idx < x_size_idx_0; idx++) {
      tmp_data[idx] = ii_data[idx];
    }

    CC->data[i].pixel_idx.size[0] = x_size_idx_0;
    CC->data[i].pixel_idx.size[1] = 1;
    for (idx = 0; idx < x_size_idx_0; idx++) {
      CC->data[i].pixel_idx.data[idx] = tmp_data[idx];
    }

    CC->data[i].area = CC->data[i].pixel_idx.size[0] * CC->data[i].
      pixel_idx.size[1];
    i++;
  }
}

/*
 * File trailer for replacement_bwconncomp.c
 *
 * [EOF]
 */
