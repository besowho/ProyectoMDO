/*
 * File: normpdf.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "normpdf.h"
#include "exp.h"
#include "prod.h"
#include "diag.h"
#include "sum.h"
#include "sqrt.h"
#include "bsxfun.h"
#include "svd.h"

/* Function Declarations */
static void eml_li_find(const boolean_T x[5], int y_data[], int y_size[1]);

/* Function Definitions */

/*
 * Arguments    : const boolean_T x[5]
 *                int y_data[]
 *                int y_size[1]
 * Return Type  : void
 */
static void eml_li_find(const boolean_T x[5], int y_data[], int y_size[1])
{
  int k;
  int i;
  k = 0;
  for (i = 0; i < 5; i++) {
    if (x[i]) {
      k++;
    }
  }

  y_size[0] = k;
  k = 0;
  for (i = 0; i < 5; i++) {
    if (x[i]) {
      y_data[k] = i + 1;
      k++;
    }
  }
}

/*
 * Arguments    : const double x[12500]
 *                const double mu[5]
 *                const double sigma[25]
 *                double y[2500]
 * Return Type  : void
 */
void normpdf(const double x[12500], const double mu[5], const double sigma[25],
             double y[2500])
{
  double unusedU1[25];
  double S[25];
  double U[25];
  double s[5];
  boolean_T b_s[5];
  int i;
  int tmp_size[1];
  int tmp_data[5];
  int i2;
  static double A[12500];
  static double a[12500];
  double dv5[5];
  double b_U[25];
  int i3;
  static double b_A[12500];
  double dv6[5];
  double B;
  svd(sigma, U, S, unusedU1);
  b_diag(S, s);
  for (i = 0; i < 5; i++) {
    b_s[i] = (s[i] < 2.2204460492503131E-16);
  }

  eml_li_find(b_s, tmp_data, tmp_size);
  i = tmp_size[0];
  for (i2 = 0; i2 < i; i2++) {
    s[tmp_data[i2] - 1] = 1.0;
  }

  diag(s, S);
  bsxfun(x, mu, A);
  for (i2 = 0; i2 < 5; i2++) {
    for (i = 0; i < 2500; i++) {
      a[i + 2500 * i2] = A[i2 + 5 * i];
    }
  }

  memcpy(&unusedU1[0], &S[0], 25U * sizeof(double));
  b_sqrt(unusedU1);
  b_diag(unusedU1, s);
  for (i = 0; i < 5; i++) {
    dv5[i] = 1.0 / s[i];
  }

  diag(dv5, unusedU1);
  for (i2 = 0; i2 < 5; i2++) {
    for (i = 0; i < 5; i++) {
      b_U[i2 + 5 * i] = 0.0;
      for (i3 = 0; i3 < 5; i3++) {
        b_U[i2 + 5 * i] += U[i2 + 5 * i3] * unusedU1[i3 + 5 * i];
      }
    }
  }

  for (i2 = 0; i2 < 2500; i2++) {
    for (i = 0; i < 5; i++) {
      b_A[i2 + 2500 * i] = 0.0;
      for (i3 = 0; i3 < 5; i3++) {
        b_A[i2 + 2500 * i] += a[i2 + 2500 * i3] * b_U[i3 + 5 * i];
      }
    }
  }

  for (i2 = 0; i2 < 12500; i2++) {
    A[i2] = b_A[i2] * b_A[i2];
  }

  sum(A, y);
  b_diag(S, dv6);
  B = 2.5066282746310002 * prod(dv6);
  for (i2 = 0; i2 < 2500; i2++) {
    y[i2] *= -0.5;
  }

  b_exp(y);
  for (i2 = 0; i2 < 2500; i2++) {
    y[i2] /= B;
  }
}

/*
 * File trailer for normpdf.c
 *
 * [EOF]
 */
