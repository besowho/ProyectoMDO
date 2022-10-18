/*
 * File: suppressDetections.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "suppressDetections.h"
#include "ssmDetect_emxutil.h"
#include "eml_sort.h"

/* Function Declarations */
static void b_eml_null_assignment(emxArray_real_T *x, const emxArray_boolean_T
  *idx);
static void c_eml_null_assignment(emxArray_real_T *x, const emxArray_boolean_T
  *idx);
static int div_nzp_s32_floor(int numerator, int denominator);
static void eml_null_assignment(emxArray_real_T *x, const emxArray_boolean_T
  *idx);

/* Function Definitions */

/*
 * Arguments    : emxArray_real_T *x
 *                const emxArray_boolean_T *idx
 * Return Type  : void
 */
static void b_eml_null_assignment(emxArray_real_T *x, const emxArray_boolean_T
  *idx)
{
  int nrows;
  int k;
  int i;
  int i40;
  int j;
  emxArray_real_T *b_x;
  nrows = 0;
  for (k = 1; k <= idx->size[1]; k++) {
    nrows += idx->data[k - 1];
  }

  nrows = x->size[0] - nrows;
  i = 0;
  i40 = x->size[0];
  for (k = 1; k <= i40; k++) {
    if ((k > idx->size[1]) || (!idx->data[k - 1])) {
      for (j = 0; j < 2; j++) {
        x->data[i + x->size[0] * j] = x->data[(k + x->size[0] * j) - 1];
      }

      i++;
    }
  }

  if (1 > nrows) {
    nrows = 0;
  }

  emxInit_real_T(&b_x, 2);
  i40 = b_x->size[0] * b_x->size[1];
  b_x->size[0] = nrows;
  b_x->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)b_x, i40, (int)sizeof(double));
  for (i40 = 0; i40 < 2; i40++) {
    for (i = 0; i < nrows; i++) {
      b_x->data[i + b_x->size[0] * i40] = x->data[i + x->size[0] * i40];
    }
  }

  i40 = x->size[0] * x->size[1];
  x->size[0] = b_x->size[0];
  x->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)x, i40, (int)sizeof(double));
  for (i40 = 0; i40 < 2; i40++) {
    nrows = b_x->size[0];
    for (i = 0; i < nrows; i++) {
      x->data[i + x->size[0] * i40] = b_x->data[i + b_x->size[0] * i40];
    }
  }

  emxFree_real_T(&b_x);
}

/*
 * Arguments    : emxArray_real_T *x
 *                const emxArray_boolean_T *idx
 * Return Type  : void
 */
static void c_eml_null_assignment(emxArray_real_T *x, const emxArray_boolean_T
  *idx)
{
  int nxin;
  int k0;
  int k;
  int nxout;
  emxArray_real_T *b_x;
  nxin = x->size[0];
  k0 = 0;
  for (k = 1; k <= idx->size[1]; k++) {
    k0 += idx->data[k - 1];
  }

  nxout = x->size[0] - k0;
  k0 = -1;
  for (k = 1; k <= nxin; k++) {
    if ((k > idx->size[1]) || (!idx->data[k - 1])) {
      k0++;
      x->data[k0] = x->data[k - 1];
    }
  }

  if (x->size[0] != 1) {
    if (1 > nxout) {
      k0 = 0;
    } else {
      k0 = nxout;
    }

    c_emxInit_real_T(&b_x, 1);
    nxout = b_x->size[0];
    b_x->size[0] = k0;
    emxEnsureCapacity((emxArray__common *)b_x, nxout, (int)sizeof(double));
    for (nxout = 0; nxout < k0; nxout++) {
      b_x->data[nxout] = x->data[nxout];
    }

    nxout = x->size[0];
    x->size[0] = b_x->size[0];
    emxEnsureCapacity((emxArray__common *)x, nxout, (int)sizeof(double));
    k0 = b_x->size[0];
    for (nxout = 0; nxout < k0; nxout++) {
      x->data[nxout] = b_x->data[nxout];
    }

    emxFree_real_T(&b_x);
  } else {
    if (1 > nxout) {
      k0 = -1;
    } else {
      k0 = 0;
    }

    c_emxInit_real_T(&b_x, 1);
    nxout = b_x->size[0];
    b_x->size[0] = k0 + 1;
    emxEnsureCapacity((emxArray__common *)b_x, nxout, (int)sizeof(double));
    nxout = 0;
    while (nxout <= k0) {
      b_x->data[0] = x->data[0];
      nxout = 1;
    }

    nxout = x->size[0];
    x->size[0] = b_x->size[0];
    emxEnsureCapacity((emxArray__common *)x, nxout, (int)sizeof(double));
    k0 = b_x->size[0];
    for (nxout = 0; nxout < k0; nxout++) {
      x->data[nxout] = b_x->data[nxout];
    }

    emxFree_real_T(&b_x);
  }
}

/*
 * Arguments    : int numerator
 *                int denominator
 * Return Type  : int
 */
static int div_nzp_s32_floor(int numerator, int denominator)
{
  int quotient;
  unsigned int absNumerator;
  unsigned int absDenominator;
  boolean_T quotientNeedsNegation;
  unsigned int tempAbsQuotient;
  if (numerator >= 0) {
    absNumerator = (unsigned int)numerator;
  } else {
    absNumerator = (unsigned int)-numerator;
  }

  if (denominator >= 0) {
    absDenominator = (unsigned int)denominator;
  } else {
    absDenominator = (unsigned int)-denominator;
  }

  quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
  tempAbsQuotient = absNumerator / absDenominator;
  if (quotientNeedsNegation) {
    absNumerator %= absDenominator;
    if (absNumerator > 0U) {
      tempAbsQuotient++;
    }
  }

  if (quotientNeedsNegation) {
    quotient = -(int)tempAbsQuotient;
  } else {
    quotient = (int)tempAbsQuotient;
  }

  return quotient;
}

/*
 * Arguments    : emxArray_real_T *x
 *                const emxArray_boolean_T *idx
 * Return Type  : void
 */
static void eml_null_assignment(emxArray_real_T *x, const emxArray_boolean_T
  *idx)
{
  int nrows;
  int k;
  int i;
  int i39;
  int j;
  emxArray_real_T *b_x;
  nrows = 0;
  for (k = 1; k <= idx->size[1]; k++) {
    nrows += idx->data[k - 1];
  }

  nrows = x->size[0] - nrows;
  i = 0;
  i39 = x->size[0];
  for (k = 1; k <= i39; k++) {
    if ((k > idx->size[1]) || (!idx->data[k - 1])) {
      for (j = 0; j < 4; j++) {
        x->data[i + x->size[0] * j] = x->data[(k + x->size[0] * j) - 1];
      }

      i++;
    }
  }

  if (1 > nrows) {
    nrows = 0;
  }

  emxInit_real_T(&b_x, 2);
  i39 = b_x->size[0] * b_x->size[1];
  b_x->size[0] = nrows;
  b_x->size[1] = 4;
  emxEnsureCapacity((emxArray__common *)b_x, i39, (int)sizeof(double));
  for (i39 = 0; i39 < 4; i39++) {
    for (i = 0; i < nrows; i++) {
      b_x->data[i + b_x->size[0] * i39] = x->data[i + x->size[0] * i39];
    }
  }

  i39 = x->size[0] * x->size[1];
  x->size[0] = b_x->size[0];
  x->size[1] = 4;
  emxEnsureCapacity((emxArray__common *)x, i39, (int)sizeof(double));
  for (i39 = 0; i39 < 4; i39++) {
    nrows = b_x->size[0];
    for (i = 0; i < nrows; i++) {
      x->data[i + x->size[0] * i39] = b_x->data[i + b_x->size[0] * i39];
    }
  }

  emxFree_real_T(&b_x);
}

/*
 * Arguments    : const emxArray_boolean_T *x
 *                emxArray_int32_T *y
 * Return Type  : void
 */
void c_eml_li_find(const emxArray_boolean_T *x, emxArray_int32_T *y)
{
  int n;
  int k;
  int i;
  int j;
  n = x->size[1];
  k = 0;
  for (i = 1; i <= n; i++) {
    if (x->data[i - 1]) {
      k++;
    }
  }

  j = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = k;
  emxEnsureCapacity((emxArray__common *)y, j, (int)sizeof(int));
  j = 0;
  for (i = 1; i <= n; i++) {
    if (x->data[i - 1]) {
      y->data[j] = i;
      j++;
    }
  }
}

/*
 * Arguments    : emxArray_real_T *bbs
 *                emxArray_real_T *bbs_out
 *                emxArray_SelectedIndices *selected_out
 * Return Type  : void
 */
void mergeByProximity(emxArray_real_T *bbs, emxArray_real_T *bbs_out,
                      emxArray_SelectedIndices *selected_out)
{
  emxArray_real_T *b_bbs;
  int numbbs;
  int iy;
  int i27;
  emxArray_real_T *ordr;
  emxArray_int32_T *iidx;
  emxArray_real_T *c_bbs;
  int i28;
  emxArray_real_T *Mu;
  emxArray_real_T *d_bbs;
  double sz[2];
  emxArray_real_T *box_sizes;
  int ixstart;
  int j;
  int i29;
  int i30;
  double s;
  emxArray_real_T *a;
  emxArray_real_T *Covs;
  unsigned int counter;
  emxArray_real_T *ratios;
  emxArray_boolean_T *id_remove;
  emxArray_real_T *e_bbs;
  emxArray_real_T *minx;
  emxArray_real_T *maxx;
  emxArray_real_T *miny;
  emxArray_real_T *maxy;
  emxArray_int32_T *r6;
  emxArray_real_T *b_ordr;
  int32_T exitg1;
  int32_T exitg6;
  double y[2];
  boolean_T exitg5;
  double mtmp;
  boolean_T exitg4;
  double b_mtmp;
  boolean_T exitg3;
  double c_mtmp;
  boolean_T exitg2;
  emxArray_real_T *b_bbs_out;
  c_emxInit_real_T(&b_bbs, 1);

  /* -------------------------------------------------------------------------- */
  numbbs = bbs->size[0];
  iy = bbs->size[0];
  i27 = b_bbs->size[0];
  b_bbs->size[0] = iy;
  emxEnsureCapacity((emxArray__common *)b_bbs, i27, (int)sizeof(double));
  for (i27 = 0; i27 < iy; i27++) {
    b_bbs->data[i27] = bbs->data[i27 + (bbs->size[0] << 1)] * bbs->data[i27 +
      bbs->size[0] * 3];
  }

  c_emxInit_real_T(&ordr, 1);
  b_emxInit_int32_T(&iidx, 1);
  b_eml_sort(b_bbs, ordr, iidx);
  i27 = ordr->size[0];
  ordr->size[0] = iidx->size[0];
  emxEnsureCapacity((emxArray__common *)ordr, i27, (int)sizeof(double));
  iy = iidx->size[0];
  emxFree_real_T(&b_bbs);
  for (i27 = 0; i27 < iy; i27++) {
    ordr->data[i27] = iidx->data[i27];
  }

  emxFree_int32_T(&iidx);
  emxInit_real_T(&c_bbs, 2);
  i27 = c_bbs->size[0] * c_bbs->size[1];
  c_bbs->size[0] = ordr->size[0];
  c_bbs->size[1] = 4;
  emxEnsureCapacity((emxArray__common *)c_bbs, i27, (int)sizeof(double));
  for (i27 = 0; i27 < 4; i27++) {
    iy = ordr->size[0];
    for (i28 = 0; i28 < iy; i28++) {
      c_bbs->data[i28 + c_bbs->size[0] * i27] = bbs->data[((int)ordr->data[i28]
        + bbs->size[0] * i27) - 1];
    }
  }

  i27 = bbs->size[0] * bbs->size[1];
  bbs->size[0] = c_bbs->size[0];
  bbs->size[1] = 4;
  emxEnsureCapacity((emxArray__common *)bbs, i27, (int)sizeof(double));
  for (i27 = 0; i27 < 4; i27++) {
    iy = c_bbs->size[0];
    for (i28 = 0; i28 < iy; i28++) {
      bbs->data[i28 + bbs->size[0] * i27] = c_bbs->data[i28 + c_bbs->size[0] *
        i27];
    }
  }

  emxFree_real_T(&c_bbs);
  emxInit_real_T(&Mu, 2);

  /* Mu = bsxfun(@plus, bbs(:,1:2), bbs(:,3:4)/2) ; */
  iy = bbs->size[0];
  i27 = Mu->size[0] * Mu->size[1];
  Mu->size[0] = iy;
  Mu->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)Mu, i27, (int)sizeof(double));
  for (i27 = 0; i27 < 2; i27++) {
    for (i28 = 0; i28 < iy; i28++) {
      Mu->data[i28 + Mu->size[0] * i27] = bbs->data[i28 + bbs->size[0] * i27] +
        bbs->data[i28 + bbs->size[0] * (2 + i27)] / 2.0;
    }
  }

  emxInit_real_T(&d_bbs, 2);
  iy = bbs->size[0];
  i27 = d_bbs->size[0] * d_bbs->size[1];
  d_bbs->size[0] = iy;
  d_bbs->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)d_bbs, i27, (int)sizeof(double));
  for (i27 = 0; i27 < 2; i27++) {
    for (i28 = 0; i28 < iy; i28++) {
      d_bbs->data[i28 + d_bbs->size[0] * i27] = bbs->data[i28 + bbs->size[0] *
        (2 + i27)];
    }
  }

  for (i27 = 0; i27 < 2; i27++) {
    sz[i27] = d_bbs->size[i27];
  }

  emxFree_real_T(&d_bbs);
  c_emxInit_real_T(&box_sizes, 1);
  i27 = box_sizes->size[0];
  box_sizes->size[0] = (int)sz[0];
  emxEnsureCapacity((emxArray__common *)box_sizes, i27, (int)sizeof(double));
  i27 = bbs->size[0];
  if (i27 == 0) {
    i27 = box_sizes->size[0];
    box_sizes->size[0] = (int)sz[0];
    emxEnsureCapacity((emxArray__common *)box_sizes, i27, (int)sizeof(double));
    iy = (int)sz[0];
    for (i27 = 0; i27 < iy; i27++) {
      box_sizes->data[i27] = 0.0;
    }
  } else {
    i27 = bbs->size[0];
    iy = -1;
    ixstart = -1;
    for (j = 1; j <= i27; j++) {
      ixstart++;
      i28 = bbs->size[0];
      i29 = bbs->size[0];
      i30 = ixstart + i27;
      s = bbs->data[ixstart % i28 + bbs->size[0] * (div_nzp_s32_floor(ixstart,
        i28) + 2)] + bbs->data[i30 % i29 + bbs->size[0] * (div_nzp_s32_floor(i30,
        i29) + 2)];
      iy++;
      box_sizes->data[iy] = s;
    }
  }

  i27 = box_sizes->size[0];
  emxEnsureCapacity((emxArray__common *)box_sizes, i27, (int)sizeof(double));
  iy = box_sizes->size[0];
  for (i27 = 0; i27 < iy; i27++) {
    box_sizes->data[i27] /= 2.0;
  }

  emxInit_real_T(&a, 2);
  iy = bbs->size[0];
  i27 = a->size[0] * a->size[1];
  a->size[0] = iy;
  a->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)a, i27, (int)sizeof(double));
  for (i27 = 0; i27 < 2; i27++) {
    for (i28 = 0; i28 < iy; i28++) {
      a->data[i28 + a->size[0] * i27] = bbs->data[i28 + bbs->size[0] * (2 + i27)]
        + 5.0;
    }
  }

  for (i27 = 0; i27 < 2; i27++) {
    sz[i27] = a->size[i27];
  }

  emxInit_real_T(&Covs, 2);
  i27 = Covs->size[0] * Covs->size[1];
  Covs->size[0] = (int)sz[0];
  Covs->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)Covs, i27, (int)sizeof(double));
  i27 = (int)sz[0] << 1;
  for (iy = 0; iy < i27; iy++) {
    Covs->data[iy] = a->data[iy] * a->data[iy];
  }

  i27 = selected_out->size[0];
  selected_out->size[0] = numbbs;
  c_emxEnsureCapacity_SelectedInd(selected_out, i27);
  for (j = 0; j < numbbs; j++) {
    i27 = selected_out->data[j].idx->size[0] * selected_out->data[j].idx->size[1];
    selected_out->data[j].idx->size[0] = 0;
    selected_out->data[j].idx->size[1] = 0;
    emxEnsureCapacity((emxArray__common *)selected_out->data[j].idx, i27, (int)
                      sizeof(double));
  }

  i27 = bbs_out->size[0] * bbs_out->size[1];
  bbs_out->size[0] = numbbs;
  bbs_out->size[1] = 4;
  emxEnsureCapacity((emxArray__common *)bbs_out, i27, (int)sizeof(double));
  iy = numbbs << 2;
  for (i27 = 0; i27 < iy; i27++) {
    bbs_out->data[i27] = 0.0;
  }

  counter = 1U;
  emxInit_real_T(&ratios, 2);
  emxInit_boolean_T(&id_remove, 2);
  emxInit_real_T(&e_bbs, 2);
  c_emxInit_real_T(&minx, 1);
  c_emxInit_real_T(&maxx, 1);
  c_emxInit_real_T(&miny, 1);
  c_emxInit_real_T(&maxy, 1);
  emxInit_int32_T(&r6, 2);
  c_emxInit_real_T(&b_ordr, 1);
  do {
    exitg1 = 0;
    i27 = ratios->size[0] * ratios->size[1];
    ratios->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)ratios, i27, (int)sizeof(double));
    iy = bbs->size[0];
    i27 = ratios->size[0] * ratios->size[1];
    ratios->size[1] = iy;
    emxEnsureCapacity((emxArray__common *)ratios, i27, (int)sizeof(double));
    iy = bbs->size[0];
    for (i27 = 0; i27 < iy; i27++) {
      ratios->data[i27] = 0.0;
    }

    j = 0;
    do {
      exitg6 = 0;
      iy = bbs->size[0];
      if (j <= iy - 1) {
        for (i27 = 0; i27 < 2; i27++) {
          sz[i27] = Mu->data[Mu->size[0] * i27] - Mu->data[j + Mu->size[0] * i27];
        }

        for (iy = 0; iy < 2; iy++) {
          y[iy] = sz[iy] * sz[iy];
        }

        for (i27 = 0; i27 < 2; i27++) {
          s = y[i27] / (Covs->data[Covs->size[0] * i27] + Covs->data[j +
                        Covs->size[0] * i27]);
          y[i27] = s;
        }

        ratios->data[j] = sqrt(y[0] + y[1]);
        j++;
      } else {
        exitg6 = 1;
      }
    } while (exitg6 == 0);

    i27 = id_remove->size[0] * id_remove->size[1];
    id_remove->size[0] = 1;
    id_remove->size[1] = ratios->size[1];
    emxEnsureCapacity((emxArray__common *)id_remove, i27, (int)sizeof(boolean_T));
    iy = ratios->size[0] * ratios->size[1];
    for (i27 = 0; i27 < iy; i27++) {
      id_remove->data[i27] = (ratios->data[i27] <= 1.0);
    }

    /* -------------------------------------------------------------------------- */
    c_eml_li_find(id_remove, r6);
    i27 = e_bbs->size[0] * e_bbs->size[1];
    e_bbs->size[0] = r6->size[1];
    e_bbs->size[1] = 4;
    emxEnsureCapacity((emxArray__common *)e_bbs, i27, (int)sizeof(double));
    for (i27 = 0; i27 < 4; i27++) {
      iy = r6->size[1];
      for (i28 = 0; i28 < iy; i28++) {
        e_bbs->data[i28 + e_bbs->size[0] * i27] = bbs->data[(r6->data[r6->size[0]
          * i28] + bbs->size[0] * i27) - 1];
      }
    }

    c_eml_li_find(id_remove, r6);
    i27 = a->size[0] * a->size[1];
    a->size[0] = r6->size[1];
    a->size[1] = 2;
    emxEnsureCapacity((emxArray__common *)a, i27, (int)sizeof(double));
    for (i27 = 0; i27 < 2; i27++) {
      iy = r6->size[1];
      for (i28 = 0; i28 < iy; i28++) {
        a->data[i28 + a->size[0] * i27] = Mu->data[(r6->data[r6->size[0] * i28]
          + Mu->size[0] * i27) - 1];
      }
    }

    iy = a->size[0];
    i27 = minx->size[0];
    minx->size[0] = iy;
    emxEnsureCapacity((emxArray__common *)minx, i27, (int)sizeof(double));
    for (i27 = 0; i27 < iy; i27++) {
      minx->data[i27] = a->data[i27] - e_bbs->data[i27 + (e_bbs->size[0] << 1)] /
        2.0;
    }

    iy = a->size[0];
    i27 = maxx->size[0];
    maxx->size[0] = iy;
    emxEnsureCapacity((emxArray__common *)maxx, i27, (int)sizeof(double));
    for (i27 = 0; i27 < iy; i27++) {
      maxx->data[i27] = a->data[i27] + e_bbs->data[i27 + (e_bbs->size[0] << 1)] /
        2.0;
    }

    iy = a->size[0];
    i27 = miny->size[0];
    miny->size[0] = iy;
    emxEnsureCapacity((emxArray__common *)miny, i27, (int)sizeof(double));
    for (i27 = 0; i27 < iy; i27++) {
      miny->data[i27] = a->data[i27 + a->size[0]] - e_bbs->data[i27 +
        e_bbs->size[0] * 3] / 2.0;
    }

    iy = a->size[0];
    i27 = maxy->size[0];
    maxy->size[0] = iy;
    emxEnsureCapacity((emxArray__common *)maxy, i27, (int)sizeof(double));
    for (i27 = 0; i27 < iy; i27++) {
      maxy->data[i27] = a->data[i27 + a->size[0]] + e_bbs->data[i27 +
        e_bbs->size[0] * 3] / 2.0;
    }

    ixstart = 1;
    iy = minx->size[0];
    s = minx->data[0];
    if (minx->size[0] > 1) {
      if (rtIsNaN(minx->data[0])) {
        j = 2;
        exitg5 = false;
        while ((!exitg5) && (j <= iy)) {
          ixstart = j;
          if (!rtIsNaN(minx->data[j - 1])) {
            s = minx->data[j - 1];
            exitg5 = true;
          } else {
            j++;
          }
        }
      }

      if (ixstart < minx->size[0]) {
        while (ixstart + 1 <= iy) {
          if (minx->data[ixstart] < s) {
            s = minx->data[ixstart];
          }

          ixstart++;
        }
      }
    }

    ixstart = 1;
    iy = miny->size[0];
    mtmp = miny->data[0];
    if (miny->size[0] > 1) {
      if (rtIsNaN(miny->data[0])) {
        j = 2;
        exitg4 = false;
        while ((!exitg4) && (j <= iy)) {
          ixstart = j;
          if (!rtIsNaN(miny->data[j - 1])) {
            mtmp = miny->data[j - 1];
            exitg4 = true;
          } else {
            j++;
          }
        }
      }

      if (ixstart < miny->size[0]) {
        while (ixstart + 1 <= iy) {
          if (miny->data[ixstart] < mtmp) {
            mtmp = miny->data[ixstart];
          }

          ixstart++;
        }
      }
    }

    ixstart = 1;
    iy = maxx->size[0];
    b_mtmp = maxx->data[0];
    if (maxx->size[0] > 1) {
      if (rtIsNaN(maxx->data[0])) {
        j = 2;
        exitg3 = false;
        while ((!exitg3) && (j <= iy)) {
          ixstart = j;
          if (!rtIsNaN(maxx->data[j - 1])) {
            b_mtmp = maxx->data[j - 1];
            exitg3 = true;
          } else {
            j++;
          }
        }
      }

      if (ixstart < maxx->size[0]) {
        while (ixstart + 1 <= iy) {
          if (maxx->data[ixstart] > b_mtmp) {
            b_mtmp = maxx->data[ixstart];
          }

          ixstart++;
        }
      }
    }

    ixstart = 1;
    iy = maxy->size[0];
    c_mtmp = maxy->data[0];
    if (maxy->size[0] > 1) {
      if (rtIsNaN(maxy->data[0])) {
        j = 2;
        exitg2 = false;
        while ((!exitg2) && (j <= iy)) {
          ixstart = j;
          if (!rtIsNaN(maxy->data[j - 1])) {
            c_mtmp = maxy->data[j - 1];
            exitg2 = true;
          } else {
            j++;
          }
        }
      }

      if (ixstart < maxy->size[0]) {
        while (ixstart + 1 <= iy) {
          if (maxy->data[ixstart] > c_mtmp) {
            c_mtmp = maxy->data[ixstart];
          }

          ixstart++;
        }
      }
    }

    bbs_out->data[(int)counter - 1] = s;
    bbs_out->data[((int)counter + bbs_out->size[0]) - 1] = mtmp;
    bbs_out->data[((int)counter + (bbs_out->size[0] << 1)) - 1] = b_mtmp - s;
    bbs_out->data[((int)counter + bbs_out->size[0] * 3) - 1] = c_mtmp - mtmp;
    c_eml_li_find(id_remove, r6);
    i27 = b_ordr->size[0];
    b_ordr->size[0] = r6->size[1];
    emxEnsureCapacity((emxArray__common *)b_ordr, i27, (int)sizeof(double));
    iy = r6->size[1];
    for (i27 = 0; i27 < iy; i27++) {
      b_ordr->data[i27] = ordr->data[r6->data[r6->size[0] * i27] - 1];
    }

    iy = r6->size[1];
    i27 = selected_out->data[(int)counter - 1].idx->size[0] * selected_out->
      data[(int)counter - 1].idx->size[1];
    selected_out->data[(int)counter - 1].idx->size[0] = iy;
    selected_out->data[(int)counter - 1].idx->size[1] = 1;
    emxEnsureCapacity((emxArray__common *)selected_out->data[(int)counter - 1].
                      idx, i27, (int)sizeof(double));
    i27 = 0;
    while (i27 <= 0) {
      for (i27 = 0; i27 < iy; i27++) {
        selected_out->data[(int)counter - 1].idx->data[i27] = b_ordr->data[i27];
      }

      i27 = 1;
    }

    eml_null_assignment(bbs, id_remove);
    b_eml_null_assignment(Mu, id_remove);
    c_eml_null_assignment(ordr, id_remove);
    b_eml_null_assignment(Covs, id_remove);
    c_eml_null_assignment(box_sizes, id_remove);
    if (Mu->size[0] == 0) {
      exitg1 = 1;
    } else {
      counter++;
    }
  } while (exitg1 == 0);

  emxFree_real_T(&b_ordr);
  emxFree_int32_T(&r6);
  emxFree_real_T(&maxy);
  emxFree_real_T(&miny);
  emxFree_real_T(&maxx);
  emxFree_real_T(&minx);
  emxFree_real_T(&e_bbs);
  emxFree_real_T(&a);
  emxFree_boolean_T(&id_remove);
  emxFree_real_T(&ratios);
  emxFree_real_T(&Covs);
  emxFree_real_T(&box_sizes);
  emxFree_real_T(&Mu);
  emxFree_real_T(&ordr);
  emxInit_real_T(&b_bbs_out, 2);
  i27 = selected_out->size[0];
  selected_out->size[0] = (int)counter;
  c_emxEnsureCapacity_SelectedInd(selected_out, i27);
  i27 = b_bbs_out->size[0] * b_bbs_out->size[1];
  b_bbs_out->size[0] = (int)counter;
  b_bbs_out->size[1] = 4;
  emxEnsureCapacity((emxArray__common *)b_bbs_out, i27, (int)sizeof(double));
  for (i27 = 0; i27 < 4; i27++) {
    iy = (int)counter;
    for (i28 = 0; i28 < iy; i28++) {
      b_bbs_out->data[i28 + b_bbs_out->size[0] * i27] = bbs_out->data[i28 +
        bbs_out->size[0] * i27];
    }
  }

  i27 = bbs_out->size[0] * bbs_out->size[1];
  bbs_out->size[0] = b_bbs_out->size[0];
  bbs_out->size[1] = 4;
  emxEnsureCapacity((emxArray__common *)bbs_out, i27, (int)sizeof(double));
  for (i27 = 0; i27 < 4; i27++) {
    iy = b_bbs_out->size[0];
    for (i28 = 0; i28 < iy; i28++) {
      bbs_out->data[i28 + bbs_out->size[0] * i27] = b_bbs_out->data[i28 +
        b_bbs_out->size[0] * i27];
    }
  }

  emxFree_real_T(&b_bbs_out);
}

/*
 * File trailer for suppressDetections.c
 *
 * [EOF]
 */
