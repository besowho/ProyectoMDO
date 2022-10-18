/*
 * File: mldivide.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "mldivide.h"

/* Function Definitions */

/*
 * Arguments    : const double A[25]
 *                double B[5]
 * Return Type  : void
 */
void mldivide(const double A[25], double B[5])
{
  double b_A[25];
  signed char ipiv[5];
  int i34;
  int j;
  int c;
  int kAcol;
  int ix;
  double temp;
  int k;
  double s;
  int jy;
  int ijA;
  memcpy(&b_A[0], &A[0], 25U * sizeof(double));
  for (i34 = 0; i34 < 5; i34++) {
    ipiv[i34] = (signed char)(1 + i34);
  }

  for (j = 0; j < 4; j++) {
    c = j * 6;
    kAcol = 0;
    ix = c;
    temp = fabs(b_A[c]);
    for (k = 1; k + 1 <= 5 - j; k++) {
      ix++;
      s = fabs(b_A[ix]);
      if (s > temp) {
        kAcol = k;
        temp = s;
      }
    }

    if (b_A[c + kAcol] != 0.0) {
      if (kAcol != 0) {
        ipiv[j] = (signed char)((j + kAcol) + 1);
        ix = j;
        kAcol += j;
        for (k = 0; k < 5; k++) {
          temp = b_A[ix];
          b_A[ix] = b_A[kAcol];
          b_A[kAcol] = temp;
          ix += 5;
          kAcol += 5;
        }
      }

      i34 = (c - j) + 5;
      for (jy = c + 1; jy + 1 <= i34; jy++) {
        b_A[jy] /= b_A[c];
      }
    }

    kAcol = c;
    jy = c + 5;
    for (k = 1; k <= 4 - j; k++) {
      temp = b_A[jy];
      if (b_A[jy] != 0.0) {
        ix = c + 1;
        i34 = (kAcol - j) + 10;
        for (ijA = 6 + kAcol; ijA + 1 <= i34; ijA++) {
          b_A[ijA] += b_A[ix] * -temp;
          ix++;
        }
      }

      jy += 5;
      kAcol += 5;
    }
  }

  for (kAcol = 0; kAcol < 4; kAcol++) {
    if (ipiv[kAcol] != kAcol + 1) {
      temp = B[kAcol];
      B[kAcol] = B[ipiv[kAcol] - 1];
      B[ipiv[kAcol] - 1] = temp;
    }
  }

  for (k = 0; k < 5; k++) {
    kAcol = 5 * k;
    if (B[k] != 0.0) {
      for (jy = k + 1; jy + 1 < 6; jy++) {
        B[jy] -= B[k] * b_A[jy + kAcol];
      }
    }
  }

  for (k = 4; k > -1; k += -1) {
    kAcol = 5 * k;
    if (B[k] != 0.0) {
      B[k] /= b_A[k + kAcol];
      for (jy = 0; jy + 1 <= k; jy++) {
        B[jy] -= B[k] * b_A[jy + kAcol];
      }
    }
  }
}

/*
 * File trailer for mldivide.c
 *
 * [EOF]
 */
