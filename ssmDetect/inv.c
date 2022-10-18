/*
 * File: inv.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "inv.h"

/* Function Definitions */

/*
 * Arguments    : const double x[25]
 *                double y[25]
 * Return Type  : void
 */
void inv(const double x[25], double y[25])
{
  double A[25];
  int i1;
  signed char ipiv[5];
  int j;
  int c;
  int jBcol;
  int ix;
  double smax;
  int k;
  double s;
  int i;
  int kAcol;
  signed char p[5];
  for (i1 = 0; i1 < 25; i1++) {
    y[i1] = 0.0;
    A[i1] = x[i1];
  }

  for (i1 = 0; i1 < 5; i1++) {
    ipiv[i1] = (signed char)(1 + i1);
  }

  for (j = 0; j < 4; j++) {
    c = j * 6;
    jBcol = 0;
    ix = c;
    smax = fabs(A[c]);
    for (k = 1; k + 1 <= 5 - j; k++) {
      ix++;
      s = fabs(A[ix]);
      if (s > smax) {
        jBcol = k;
        smax = s;
      }
    }

    if (A[c + jBcol] != 0.0) {
      if (jBcol != 0) {
        ipiv[j] = (signed char)((j + jBcol) + 1);
        ix = j;
        jBcol += j;
        for (k = 0; k < 5; k++) {
          smax = A[ix];
          A[ix] = A[jBcol];
          A[jBcol] = smax;
          ix += 5;
          jBcol += 5;
        }
      }

      i1 = (c - j) + 5;
      for (i = c + 1; i + 1 <= i1; i++) {
        A[i] /= A[c];
      }
    }

    jBcol = c;
    kAcol = c + 5;
    for (i = 1; i <= 4 - j; i++) {
      smax = A[kAcol];
      if (A[kAcol] != 0.0) {
        ix = c + 1;
        i1 = (jBcol - j) + 10;
        for (k = 6 + jBcol; k + 1 <= i1; k++) {
          A[k] += A[ix] * -smax;
          ix++;
        }
      }

      kAcol += 5;
      jBcol += 5;
    }
  }

  for (i1 = 0; i1 < 5; i1++) {
    p[i1] = (signed char)(1 + i1);
  }

  for (k = 0; k < 4; k++) {
    if (ipiv[k] > 1 + k) {
      jBcol = p[ipiv[k] - 1];
      p[ipiv[k] - 1] = p[k];
      p[k] = (signed char)jBcol;
    }
  }

  for (k = 0; k < 5; k++) {
    c = p[k] - 1;
    y[k + 5 * (p[k] - 1)] = 1.0;
    for (j = k; j + 1 < 6; j++) {
      if (y[j + 5 * c] != 0.0) {
        for (i = j + 1; i + 1 < 6; i++) {
          y[i + 5 * c] -= y[j + 5 * c] * A[i + 5 * j];
        }
      }
    }
  }

  for (j = 0; j < 5; j++) {
    jBcol = 5 * j;
    for (k = 4; k > -1; k += -1) {
      kAcol = 5 * k;
      if (y[k + jBcol] != 0.0) {
        y[k + jBcol] /= A[k + kAcol];
        for (i = 0; i + 1 <= k; i++) {
          y[i + jBcol] -= y[k + jBcol] * A[i + kAcol];
        }
      }
    }
  }
}

/*
 * File trailer for inv.c
 *
 * [EOF]
 */
