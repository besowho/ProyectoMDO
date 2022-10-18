/*
 * File: svd.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "svd.h"

/* Function Declarations */
static void b_eml_xaxpy(int n, double a, const double x[25], int ix0, double y[5],
  int iy0);
static double b_eml_xdotc(const double x[4], const double y[4]);
static void b_eml_xgesvd(const double A[4], double U[4], double S[2], double V[4]);
static double b_eml_xnrm2(int n, const double x[5], int ix0);
static void b_eml_xrot(double x[4], int ix0, int iy0, double c, double s);
static void b_eml_xscal(double a, double x[4], int ix0);
static void b_eml_xswap(double x[4]);
static void c_eml_xaxpy(int n, double a, const double x[5], int ix0, double y[25],
  int iy0);
static double c_eml_xnrm2(const double x[4]);
static void d_eml_xaxpy(double a, double y[4]);
static void eml_xaxpy(int n, double a, int ix0, double y[25], int iy0);
static double eml_xdotc(int n, const double x[25], int ix0, const double y[25],
  int iy0);
static void eml_xgesvd(const double A[25], double U[25], double S[5], double V
  [25]);
static double eml_xnrm2(int n, const double x[25], int ix0);
static void eml_xrot(double x[25], int ix0, int iy0, double c, double s);
static void eml_xrotg(double *a, double *b, double *c, double *s);
static void eml_xscal(double a, double x[25], int ix0);
static void eml_xswap(double x[25], int ix0, int iy0);

/* Function Definitions */

/*
 * Arguments    : int n
 *                double a
 *                const double x[25]
 *                int ix0
 *                double y[5]
 *                int iy0
 * Return Type  : void
 */
static void b_eml_xaxpy(int n, double a, const double x[25], int ix0, double y[5],
  int iy0)
{
  int ix;
  int iy;
  int k;
  if (a == 0.0) {
  } else {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

/*
 * Arguments    : const double x[4]
 *                const double y[4]
 * Return Type  : double
 */
static double b_eml_xdotc(const double x[4], const double y[4])
{
  double d;
  int ix;
  int iy;
  int k;
  d = 0.0;
  ix = 0;
  iy = 2;
  for (k = 0; k < 2; k++) {
    d += x[ix] * y[iy];
    ix++;
    iy++;
  }

  return d;
}

/*
 * Arguments    : const double A[4]
 *                double U[4]
 *                double S[2]
 *                double V[4]
 * Return Type  : void
 */
static void b_eml_xgesvd(const double A[4], double U[4], double S[2], double V[4])
{
  double b_A[4];
  int kase;
  boolean_T apply_transform;
  double nrm;
  double ztest;
  double s[2];
  int m;
  double e[2];
  int q;
  double rt;
  int iter;
  double snorm;
  boolean_T exitg3;
  int qs;
  boolean_T exitg2;
  double f;
  double varargin_1[5];
  double mtmp;
  boolean_T exitg1;
  double sqds;
  for (kase = 0; kase < 4; kase++) {
    b_A[kase] = A[kase];
    V[kase] = 0.0;
  }

  apply_transform = false;
  nrm = c_eml_xnrm2(A);
  if (nrm > 0.0) {
    apply_transform = true;
    if (A[0] < 0.0) {
      nrm = -nrm;
    }

    if (fabs(nrm) >= 1.0020841800044864E-292) {
      ztest = 1.0 / nrm;
      for (kase = 0; kase < 2; kase++) {
        b_A[kase] *= ztest;
      }
    } else {
      for (kase = 0; kase < 2; kase++) {
        b_A[kase] /= nrm;
      }
    }

    b_A[0]++;
    s[0] = -nrm;
  } else {
    s[0] = 0.0;
  }

  if (apply_transform) {
    d_eml_xaxpy(-(b_eml_xdotc(b_A, b_A) / b_A[0]), b_A);
  }

  m = 2;
  s[1] = b_A[3];
  e[0] = b_A[2];
  e[1] = 0.0;
  for (kase = 0; kase < 2; kase++) {
    U[kase] = b_A[kase];
    U[2 + kase] = 0.0;
  }

  U[3] = 1.0;
  if (s[0] != 0.0) {
    d_eml_xaxpy(-(b_eml_xdotc(U, U) / U[0]), U);
    for (kase = 0; kase < 2; kase++) {
      U[kase] = -U[kase];
    }

    U[0]++;
  } else {
    for (kase = 0; kase < 2; kase++) {
      U[kase] = 0.0;
    }

    U[0] = 1.0;
  }

  for (q = 1; q > -1; q += -1) {
    for (kase = 0; kase < 2; kase++) {
      V[kase + (q << 1)] = 0.0;
    }

    V[q + (q << 1)] = 1.0;
  }

  nrm = b_A[2];
  for (q = 0; q < 2; q++) {
    if (s[q] != 0.0) {
      rt = fabs(s[q]);
      ztest = s[q] / rt;
      s[q] = rt;
      if (q + 1 < 2) {
        nrm /= ztest;
      }

      b_eml_xscal(ztest, U, 1 + (q << 1));
    }

    if ((q + 1 < 2) && (nrm != 0.0)) {
      rt = fabs(nrm);
      ztest = rt / nrm;
      nrm = rt;
      s[1] *= ztest;
      b_eml_xscal(ztest, V, 3);
    }

    e[0] = nrm;
  }

  iter = 0;
  snorm = 0.0;
  for (kase = 0; kase < 2; kase++) {
    nrm = fabs(s[kase]);
    ztest = fabs(e[kase]);
    if ((nrm >= ztest) || rtIsNaN(ztest)) {
    } else {
      nrm = ztest;
    }

    if ((snorm >= nrm) || rtIsNaN(nrm)) {
    } else {
      snorm = nrm;
    }
  }

  while ((m > 0) && (!(iter >= 75))) {
    q = m - 1;
    exitg3 = false;
    while (!(exitg3 || (q == 0))) {
      nrm = fabs(e[0]);
      if ((nrm <= 2.2204460492503131E-16 * (fabs(s[0]) + fabs(s[1]))) || (nrm <=
           1.0020841800044864E-292) || ((iter > 20) && (nrm <=
            2.2204460492503131E-16 * snorm))) {
        e[0] = 0.0;
        exitg3 = true;
      } else {
        q = 0;
      }
    }

    if (q == m - 1) {
      kase = 4;
    } else {
      qs = m;
      kase = m;
      exitg2 = false;
      while ((!exitg2) && (kase >= q)) {
        qs = kase;
        if (kase == q) {
          exitg2 = true;
        } else {
          nrm = 0.0;
          if (kase < m) {
            nrm = fabs(e[0]);
          }

          if (kase > q + 1) {
            nrm += fabs(e[0]);
          }

          ztest = fabs(s[kase - 1]);
          if ((ztest <= 2.2204460492503131E-16 * nrm) || (ztest <=
               1.0020841800044864E-292)) {
            s[kase - 1] = 0.0;
            exitg2 = true;
          } else {
            kase--;
          }
        }
      }

      if (qs == q) {
        kase = 3;
      } else if (qs == m) {
        kase = 1;
      } else {
        kase = 2;
        q = qs;
      }
    }

    switch (kase) {
     case 1:
      f = e[0];
      e[0] = 0.0;
      kase = m - 1;
      while (kase >= q + 1) {
        nrm = s[0];
        eml_xrotg(&nrm, &f, &ztest, &rt);
        s[0] = nrm;
        b_eml_xrot(V, 1, 1 + ((m - 1) << 1), ztest, rt);
        kase = 0;
      }
      break;

     case 2:
      f = e[q - 1];
      e[q - 1] = 0.0;
      for (kase = q; kase + 1 <= m; kase++) {
        eml_xrotg(&s[kase], &f, &ztest, &rt);
        f = -rt * e[kase];
        e[kase] *= ztest;
        b_eml_xrot(U, 1 + (kase << 1), 1 + ((q - 1) << 1), ztest, rt);
      }
      break;

     case 3:
      varargin_1[0] = fabs(s[m - 1]);
      varargin_1[1] = fabs(s[0]);
      varargin_1[2] = fabs(e[0]);
      varargin_1[3] = fabs(s[q]);
      varargin_1[4] = fabs(e[q]);
      kase = 1;
      mtmp = varargin_1[0];
      if (rtIsNaN(varargin_1[0])) {
        qs = 2;
        exitg1 = false;
        while ((!exitg1) && (qs < 6)) {
          kase = qs;
          if (!rtIsNaN(varargin_1[qs - 1])) {
            mtmp = varargin_1[qs - 1];
            exitg1 = true;
          } else {
            qs++;
          }
        }
      }

      if (kase < 5) {
        while (kase + 1 < 6) {
          if (varargin_1[kase] > mtmp) {
            mtmp = varargin_1[kase];
          }

          kase++;
        }
      }

      f = s[m - 1] / mtmp;
      nrm = s[0] / mtmp;
      ztest = e[0] / mtmp;
      sqds = s[q] / mtmp;
      rt = ((nrm + f) * (nrm - f) + ztest * ztest) / 2.0;
      nrm = f * ztest;
      nrm *= nrm;
      if ((rt != 0.0) || (nrm != 0.0)) {
        ztest = sqrt(rt * rt + nrm);
        if (rt < 0.0) {
          ztest = -ztest;
        }

        ztest = nrm / (rt + ztest);
      } else {
        ztest = 0.0;
      }

      f = (sqds + f) * (sqds - f) + ztest;
      nrm = sqds * (e[q] / mtmp);
      while (q + 1 <= 1) {
        eml_xrotg(&f, &nrm, &ztest, &rt);
        f = ztest * s[0] + rt * e[0];
        e[0] = ztest * e[0] - rt * s[0];
        nrm = rt * s[1];
        s[1] *= ztest;
        b_eml_xrot(V, 1, 3, ztest, rt);
        s[0] = f;
        eml_xrotg(&s[0], &nrm, &ztest, &rt);
        f = ztest * e[0] + rt * s[1];
        s[1] = -rt * e[0] + ztest * s[1];
        nrm = rt * e[1];
        e[1] *= ztest;
        b_eml_xrot(U, 1, 3, ztest, rt);
        q = 1;
      }

      e[0] = f;
      iter++;
      break;

     default:
      if (s[q] < 0.0) {
        s[q] = -s[q];
        b_eml_xscal(-1.0, V, 1 + (q << 1));
      }

      while ((q + 1 < 2) && (s[0] < s[1])) {
        rt = s[0];
        s[0] = s[1];
        s[1] = rt;
        b_eml_xswap(V);
        b_eml_xswap(U);
        q = 1;
      }

      iter = 0;
      m--;
      break;
    }
  }

  for (kase = 0; kase < 2; kase++) {
    S[kase] = s[kase];
  }
}

/*
 * Arguments    : int n
 *                const double x[5]
 *                int ix0
 * Return Type  : double
 */
static double b_eml_xnrm2(int n, const double x[5], int ix0)
{
  double y;
  double scale;
  int kend;
  int k;
  double absxk;
  double t;
  y = 0.0;
  scale = 2.2250738585072014E-308;
  kend = (ix0 + n) - 1;
  for (k = ix0; k <= kend; k++) {
    absxk = fabs(x[k - 1]);
    if (absxk > scale) {
      t = scale / absxk;
      y = 1.0 + y * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * sqrt(y);
}

/*
 * Arguments    : double x[4]
 *                int ix0
 *                int iy0
 *                double c
 *                double s
 * Return Type  : void
 */
static void b_eml_xrot(double x[4], int ix0, int iy0, double c, double s)
{
  int ix;
  int iy;
  int k;
  double temp;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 2; k++) {
    temp = c * x[ix] + s * x[iy];
    x[iy] = c * x[iy] - s * x[ix];
    x[ix] = temp;
    iy++;
    ix++;
  }
}

/*
 * Arguments    : double a
 *                double x[4]
 *                int ix0
 * Return Type  : void
 */
static void b_eml_xscal(double a, double x[4], int ix0)
{
  int k;
  for (k = ix0; k <= ix0 + 1; k++) {
    x[k - 1] *= a;
  }
}

/*
 * Arguments    : double x[4]
 * Return Type  : void
 */
static void b_eml_xswap(double x[4])
{
  int ix;
  int iy;
  int k;
  double temp;
  ix = 0;
  iy = 2;
  for (k = 0; k < 2; k++) {
    temp = x[ix];
    x[ix] = x[iy];
    x[iy] = temp;
    ix++;
    iy++;
  }
}

/*
 * Arguments    : int n
 *                double a
 *                const double x[5]
 *                int ix0
 *                double y[25]
 *                int iy0
 * Return Type  : void
 */
static void c_eml_xaxpy(int n, double a, const double x[5], int ix0, double y[25],
  int iy0)
{
  int ix;
  int iy;
  int k;
  if (a == 0.0) {
  } else {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

/*
 * Arguments    : const double x[4]
 * Return Type  : double
 */
static double c_eml_xnrm2(const double x[4])
{
  double y;
  double scale;
  int k;
  double absxk;
  double t;
  y = 0.0;
  scale = 2.2250738585072014E-308;
  for (k = 0; k < 2; k++) {
    absxk = fabs(x[k]);
    if (absxk > scale) {
      t = scale / absxk;
      y = 1.0 + y * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * sqrt(y);
}

/*
 * Arguments    : double a
 *                double y[4]
 * Return Type  : void
 */
static void d_eml_xaxpy(double a, double y[4])
{
  int ix;
  int iy;
  int k;
  if (a == 0.0) {
  } else {
    ix = 0;
    iy = 2;
    for (k = 0; k < 2; k++) {
      y[iy] += a * y[ix];
      ix++;
      iy++;
    }
  }
}

/*
 * Arguments    : int n
 *                double a
 *                int ix0
 *                double y[25]
 *                int iy0
 * Return Type  : void
 */
static void eml_xaxpy(int n, double a, int ix0, double y[25], int iy0)
{
  int ix;
  int iy;
  int k;
  if ((n < 1) || (a == 0.0)) {
  } else {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * y[ix];
      ix++;
      iy++;
    }
  }
}

/*
 * Arguments    : int n
 *                const double x[25]
 *                int ix0
 *                const double y[25]
 *                int iy0
 * Return Type  : double
 */
static double eml_xdotc(int n, const double x[25], int ix0, const double y[25],
  int iy0)
{
  double d;
  int ix;
  int iy;
  int k;
  d = 0.0;
  if (n < 1) {
  } else {
    ix = ix0;
    iy = iy0;
    for (k = 1; k <= n; k++) {
      d += x[ix - 1] * y[iy - 1];
      ix++;
      iy++;
    }
  }

  return d;
}

/*
 * Arguments    : const double A[25]
 *                double U[25]
 *                double S[5]
 *                double V[25]
 * Return Type  : void
 */
static void eml_xgesvd(const double A[25], double U[25], double S[5], double V
  [25])
{
  double b_A[25];
  double s[5];
  double e[5];
  double work[5];
  int i;
  int q;
  int iter;
  boolean_T apply_transform;
  double ztest0;
  int qp1jj;
  int qs;
  int m;
  double rt;
  double ztest;
  double snorm;
  int32_T exitg3;
  boolean_T exitg2;
  double f;
  double varargin_1[5];
  double mtmp;
  boolean_T exitg1;
  double sqds;
  memcpy(&b_A[0], &A[0], 25U * sizeof(double));
  for (i = 0; i < 5; i++) {
    s[i] = 0.0;
    e[i] = 0.0;
    work[i] = 0.0;
  }

  for (i = 0; i < 25; i++) {
    U[i] = 0.0;
    V[i] = 0.0;
  }

  for (q = 0; q < 4; q++) {
    iter = q + 5 * q;
    apply_transform = false;
    ztest0 = eml_xnrm2(5 - q, b_A, iter + 1);
    if (ztest0 > 0.0) {
      apply_transform = true;
      if (b_A[iter] < 0.0) {
        s[q] = -ztest0;
      } else {
        s[q] = ztest0;
      }

      if (fabs(s[q]) >= 1.0020841800044864E-292) {
        ztest0 = 1.0 / s[q];
        i = (iter - q) + 5;
        for (qp1jj = iter; qp1jj + 1 <= i; qp1jj++) {
          b_A[qp1jj] *= ztest0;
        }
      } else {
        i = (iter - q) + 5;
        for (qp1jj = iter; qp1jj + 1 <= i; qp1jj++) {
          b_A[qp1jj] /= s[q];
        }
      }

      b_A[iter]++;
      s[q] = -s[q];
    } else {
      s[q] = 0.0;
    }

    for (qs = q + 1; qs + 1 < 6; qs++) {
      i = q + 5 * qs;
      if (apply_transform) {
        eml_xaxpy(5 - q, -(eml_xdotc(5 - q, b_A, iter + 1, b_A, i + 1) / b_A[q +
                           5 * q]), iter + 1, b_A, i + 1);
      }

      e[qs] = b_A[i];
    }

    for (qp1jj = q; qp1jj + 1 < 6; qp1jj++) {
      U[qp1jj + 5 * q] = b_A[qp1jj + 5 * q];
    }

    if (q + 1 <= 3) {
      ztest0 = b_eml_xnrm2(4 - q, e, q + 2);
      if (ztest0 == 0.0) {
        e[q] = 0.0;
      } else {
        if (e[q + 1] < 0.0) {
          e[q] = -ztest0;
        } else {
          e[q] = ztest0;
        }

        ztest0 = e[q];
        if (fabs(e[q]) >= 1.0020841800044864E-292) {
          ztest0 = 1.0 / e[q];
          for (qp1jj = q + 1; qp1jj + 1 < 6; qp1jj++) {
            e[qp1jj] *= ztest0;
          }
        } else {
          for (qp1jj = q + 1; qp1jj + 1 < 6; qp1jj++) {
            e[qp1jj] /= ztest0;
          }
        }

        e[q + 1]++;
        e[q] = -e[q];
        for (qp1jj = q + 1; qp1jj + 1 < 6; qp1jj++) {
          work[qp1jj] = 0.0;
        }

        for (qs = q + 1; qs + 1 < 6; qs++) {
          b_eml_xaxpy(4 - q, e[qs], b_A, (q + 5 * qs) + 2, work, q + 2);
        }

        for (qs = q + 1; qs + 1 < 6; qs++) {
          c_eml_xaxpy(4 - q, -e[qs] / e[q + 1], work, q + 2, b_A, (q + 5 * qs) +
                      2);
        }
      }

      for (qp1jj = q + 1; qp1jj + 1 < 6; qp1jj++) {
        V[qp1jj + 5 * q] = e[qp1jj];
      }
    }
  }

  m = 3;
  s[4] = b_A[24];
  e[3] = b_A[23];
  e[4] = 0.0;
  for (qp1jj = 0; qp1jj < 5; qp1jj++) {
    U[20 + qp1jj] = 0.0;
  }

  U[24] = 1.0;
  for (q = 3; q > -1; q += -1) {
    iter = q + 5 * q;
    if (s[q] != 0.0) {
      for (qs = q + 1; qs + 1 < 6; qs++) {
        i = (q + 5 * qs) + 1;
        eml_xaxpy(5 - q, -(eml_xdotc(5 - q, U, iter + 1, U, i) / U[iter]), iter
                  + 1, U, i);
      }

      for (qp1jj = q; qp1jj + 1 < 6; qp1jj++) {
        U[qp1jj + 5 * q] = -U[qp1jj + 5 * q];
      }

      U[iter]++;
      for (qp1jj = 1; qp1jj <= q; qp1jj++) {
        U[(qp1jj + 5 * q) - 1] = 0.0;
      }
    } else {
      for (qp1jj = 0; qp1jj < 5; qp1jj++) {
        U[qp1jj + 5 * q] = 0.0;
      }

      U[iter] = 1.0;
    }
  }

  for (q = 4; q > -1; q += -1) {
    if ((q + 1 <= 3) && (e[q] != 0.0)) {
      i = (q + 5 * q) + 2;
      for (qs = q + 1; qs + 1 < 6; qs++) {
        qp1jj = (q + 5 * qs) + 2;
        eml_xaxpy(4 - q, -(eml_xdotc(4 - q, V, i, V, qp1jj) / V[i - 1]), i, V,
                  qp1jj);
      }
    }

    for (qp1jj = 0; qp1jj < 5; qp1jj++) {
      V[qp1jj + 5 * q] = 0.0;
    }

    V[q + 5 * q] = 1.0;
  }

  for (q = 0; q < 5; q++) {
    ztest0 = e[q];
    if (s[q] != 0.0) {
      rt = fabs(s[q]);
      ztest = s[q] / rt;
      s[q] = rt;
      if (q + 1 < 5) {
        ztest0 = e[q] / ztest;
      }

      eml_xscal(ztest, U, 1 + 5 * q);
    }

    if ((q + 1 < 5) && (ztest0 != 0.0)) {
      rt = fabs(ztest0);
      ztest = rt / ztest0;
      ztest0 = rt;
      s[q + 1] *= ztest;
      eml_xscal(ztest, V, 1 + 5 * (q + 1));
    }

    e[q] = ztest0;
  }

  iter = 0;
  snorm = 0.0;
  for (qp1jj = 0; qp1jj < 5; qp1jj++) {
    ztest0 = fabs(s[qp1jj]);
    ztest = fabs(e[qp1jj]);
    if ((ztest0 >= ztest) || rtIsNaN(ztest)) {
    } else {
      ztest0 = ztest;
    }

    if ((snorm >= ztest0) || rtIsNaN(ztest0)) {
    } else {
      snorm = ztest0;
    }
  }

  while ((m + 2 > 0) && (!(iter >= 75))) {
    qp1jj = m;
    do {
      exitg3 = 0;
      q = qp1jj + 1;
      if (qp1jj + 1 == 0) {
        exitg3 = 1;
      } else {
        ztest0 = fabs(e[qp1jj]);
        if ((ztest0 <= 2.2204460492503131E-16 * (fabs(s[qp1jj]) + fabs(s[qp1jj +
               1]))) || (ztest0 <= 1.0020841800044864E-292) || ((iter > 20) &&
             (ztest0 <= 2.2204460492503131E-16 * snorm))) {
          e[qp1jj] = 0.0;
          exitg3 = 1;
        } else {
          qp1jj--;
        }
      }
    } while (exitg3 == 0);

    if (qp1jj + 1 == m + 1) {
      i = 4;
    } else {
      qs = m + 2;
      i = m + 2;
      exitg2 = false;
      while ((!exitg2) && (i >= qp1jj + 1)) {
        qs = i;
        if (i == qp1jj + 1) {
          exitg2 = true;
        } else {
          ztest0 = 0.0;
          if (i < m + 2) {
            ztest0 = fabs(e[i - 1]);
          }

          if (i > qp1jj + 2) {
            ztest0 += fabs(e[i - 2]);
          }

          ztest = fabs(s[i - 1]);
          if ((ztest <= 2.2204460492503131E-16 * ztest0) || (ztest <=
               1.0020841800044864E-292)) {
            s[i - 1] = 0.0;
            exitg2 = true;
          } else {
            i--;
          }
        }
      }

      if (qs == qp1jj + 1) {
        i = 3;
      } else if (qs == m + 2) {
        i = 1;
      } else {
        i = 2;
        q = qs;
      }
    }

    switch (i) {
     case 1:
      f = e[m];
      e[m] = 0.0;
      for (qp1jj = m; qp1jj + 1 >= q + 1; qp1jj--) {
        ztest0 = s[qp1jj];
        eml_xrotg(&ztest0, &f, &ztest, &rt);
        s[qp1jj] = ztest0;
        if (qp1jj + 1 > q + 1) {
          f = -rt * e[qp1jj - 1];
          e[qp1jj - 1] *= ztest;
        }

        eml_xrot(V, 1 + 5 * qp1jj, 1 + 5 * (m + 1), ztest, rt);
      }
      break;

     case 2:
      f = e[q - 1];
      e[q - 1] = 0.0;
      for (qp1jj = q; qp1jj + 1 <= m + 2; qp1jj++) {
        eml_xrotg(&s[qp1jj], &f, &ztest, &rt);
        f = -rt * e[qp1jj];
        e[qp1jj] *= ztest;
        eml_xrot(U, 1 + 5 * qp1jj, 1 + 5 * (q - 1), ztest, rt);
      }
      break;

     case 3:
      varargin_1[0] = fabs(s[m + 1]);
      varargin_1[1] = fabs(s[m]);
      varargin_1[2] = fabs(e[m]);
      varargin_1[3] = fabs(s[q]);
      varargin_1[4] = fabs(e[q]);
      i = 1;
      mtmp = varargin_1[0];
      if (rtIsNaN(varargin_1[0])) {
        qp1jj = 2;
        exitg1 = false;
        while ((!exitg1) && (qp1jj < 6)) {
          i = qp1jj;
          if (!rtIsNaN(varargin_1[qp1jj - 1])) {
            mtmp = varargin_1[qp1jj - 1];
            exitg1 = true;
          } else {
            qp1jj++;
          }
        }
      }

      if (i < 5) {
        while (i + 1 < 6) {
          if (varargin_1[i] > mtmp) {
            mtmp = varargin_1[i];
          }

          i++;
        }
      }

      f = s[m + 1] / mtmp;
      ztest0 = s[m] / mtmp;
      ztest = e[m] / mtmp;
      sqds = s[q] / mtmp;
      rt = ((ztest0 + f) * (ztest0 - f) + ztest * ztest) / 2.0;
      ztest0 = f * ztest;
      ztest0 *= ztest0;
      if ((rt != 0.0) || (ztest0 != 0.0)) {
        ztest = sqrt(rt * rt + ztest0);
        if (rt < 0.0) {
          ztest = -ztest;
        }

        ztest = ztest0 / (rt + ztest);
      } else {
        ztest = 0.0;
      }

      f = (sqds + f) * (sqds - f) + ztest;
      ztest0 = sqds * (e[q] / mtmp);
      for (qp1jj = q + 1; qp1jj <= m + 1; qp1jj++) {
        eml_xrotg(&f, &ztest0, &ztest, &rt);
        if (qp1jj > q + 1) {
          e[qp1jj - 2] = f;
        }

        f = ztest * s[qp1jj - 1] + rt * e[qp1jj - 1];
        e[qp1jj - 1] = ztest * e[qp1jj - 1] - rt * s[qp1jj - 1];
        ztest0 = rt * s[qp1jj];
        s[qp1jj] *= ztest;
        eml_xrot(V, 1 + 5 * (qp1jj - 1), 1 + 5 * qp1jj, ztest, rt);
        s[qp1jj - 1] = f;
        eml_xrotg(&s[qp1jj - 1], &ztest0, &ztest, &rt);
        f = ztest * e[qp1jj - 1] + rt * s[qp1jj];
        s[qp1jj] = -rt * e[qp1jj - 1] + ztest * s[qp1jj];
        ztest0 = rt * e[qp1jj];
        e[qp1jj] *= ztest;
        eml_xrot(U, 1 + 5 * (qp1jj - 1), 1 + 5 * qp1jj, ztest, rt);
      }

      e[m] = f;
      iter++;
      break;

     default:
      if (s[q] < 0.0) {
        s[q] = -s[q];
        eml_xscal(-1.0, V, 1 + 5 * q);
      }

      i = q + 1;
      while ((q + 1 < 5) && (s[q] < s[i])) {
        rt = s[q];
        s[q] = s[i];
        s[i] = rt;
        eml_xswap(V, 1 + 5 * q, 1 + 5 * (q + 1));
        eml_xswap(U, 1 + 5 * q, 1 + 5 * (q + 1));
        q = i;
        i++;
      }

      iter = 0;
      m--;
      break;
    }
  }

  for (qp1jj = 0; qp1jj < 5; qp1jj++) {
    S[qp1jj] = s[qp1jj];
  }
}

/*
 * Arguments    : int n
 *                const double x[25]
 *                int ix0
 * Return Type  : double
 */
static double eml_xnrm2(int n, const double x[25], int ix0)
{
  double y;
  double scale;
  int kend;
  int k;
  double absxk;
  double t;
  y = 0.0;
  scale = 2.2250738585072014E-308;
  kend = (ix0 + n) - 1;
  for (k = ix0; k <= kend; k++) {
    absxk = fabs(x[k - 1]);
    if (absxk > scale) {
      t = scale / absxk;
      y = 1.0 + y * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * sqrt(y);
}

/*
 * Arguments    : double x[25]
 *                int ix0
 *                int iy0
 *                double c
 *                double s
 * Return Type  : void
 */
static void eml_xrot(double x[25], int ix0, int iy0, double c, double s)
{
  int ix;
  int iy;
  int k;
  double temp;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 5; k++) {
    temp = c * x[ix] + s * x[iy];
    x[iy] = c * x[iy] - s * x[ix];
    x[ix] = temp;
    iy++;
    ix++;
  }
}

/*
 * Arguments    : double *a
 *                double *b
 *                double *c
 *                double *s
 * Return Type  : void
 */
static void eml_xrotg(double *a, double *b, double *c, double *s)
{
  double roe;
  double absa;
  double absb;
  double scale;
  double ads;
  double bds;
  roe = *b;
  absa = fabs(*a);
  absb = fabs(*b);
  if (absa > absb) {
    roe = *a;
  }

  scale = absa + absb;
  if (scale == 0.0) {
    *s = 0.0;
    *c = 1.0;
    scale = 0.0;
    *b = 0.0;
  } else {
    ads = absa / scale;
    bds = absb / scale;
    scale *= sqrt(ads * ads + bds * bds);
    if (roe < 0.0) {
      scale = -scale;
    }

    *c = *a / scale;
    *s = *b / scale;
    if (absa > absb) {
      *b = *s;
    } else if (*c != 0.0) {
      *b = 1.0 / *c;
    } else {
      *b = 1.0;
    }
  }

  *a = scale;
}

/*
 * Arguments    : double a
 *                double x[25]
 *                int ix0
 * Return Type  : void
 */
static void eml_xscal(double a, double x[25], int ix0)
{
  int k;
  for (k = ix0; k <= ix0 + 4; k++) {
    x[k - 1] *= a;
  }
}

/*
 * Arguments    : double x[25]
 *                int ix0
 *                int iy0
 * Return Type  : void
 */
static void eml_xswap(double x[25], int ix0, int iy0)
{
  int ix;
  int iy;
  int k;
  double temp;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 5; k++) {
    temp = x[ix];
    x[ix] = x[iy];
    x[iy] = temp;
    ix++;
    iy++;
  }
}

/*
 * Arguments    : const double A[4]
 *                double U[4]
 *                double S[4]
 *                double V[4]
 * Return Type  : void
 */
void b_svd(const double A[4], double U[4], double S[4], double V[4])
{
  double s[2];
  int k;
  b_eml_xgesvd(A, U, s, V);
  for (k = 0; k < 4; k++) {
    S[k] = 0.0;
  }

  for (k = 0; k < 2; k++) {
    S[k + (k << 1)] = s[k];
  }
}

/*
 * Arguments    : const double A[25]
 *                double U[25]
 *                double S[25]
 *                double V[25]
 * Return Type  : void
 */
void svd(const double A[25], double U[25], double S[25], double V[25])
{
  double s[5];
  int k;
  eml_xgesvd(A, U, s, V);
  memset(&S[0], 0, 25U * sizeof(double));
  for (k = 0; k < 5; k++) {
    S[k + 5 * k] = s[k];
  }
}

/*
 * File trailer for svd.c
 *
 * [EOF]
 */
