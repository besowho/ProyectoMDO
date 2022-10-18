/*
 * File: mergePd.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "mergePd.h"
#include "mldivide.h"
#include "inv.h"

/* Function Definitions */

/*
 * Arguments    : const double Mu_d[5]
 *                const double C_d[25]
 *                const double Mu_0[5]
 *                const double iC0[25]
 *                double Mu[5]
 * Return Type  : void
 */
void mergePd(const double Mu_d[5], const double C_d[25], const double Mu_0[5],
             const double iC0[25], double Mu[5])
{
  double tmpB[5];
  int i;
  double y;
  double tmpC[25];
  static const signed char a[25] = { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 1 };

  double dv9[25];
  int i9;

  /*  approximately robust */
  for (i = 0; i < 5; i++) {
    tmpB[i] = C_d[i * 6];
  }

  y = tmpB[0];
  for (i = 0; i < 4; i++) {
    y += tmpB[i + 1];
  }

  y /= 5.0;
  for (i = 0; i < 25; i++) {
    tmpC[i] = C_d[i] + (double)a[i] * y * 1.0E-10;
  }

  inv(tmpC, dv9);
  for (i = 0; i < 5; i++) {
    tmpB[i] = Mu_d[i];
  }

  mldivide(tmpC, tmpB);
  for (i = 0; i < 5; i++) {
    y = 0.0;
    for (i9 = 0; i9 < 5; i9++) {
      y += iC0[i + 5 * i9] * Mu_0[i9];
    }

    Mu[i] = tmpB[i] + y;
  }

  for (i = 0; i < 25; i++) {
    tmpC[i] = dv9[i] + iC0[i];
  }

  mldivide(tmpC, Mu);
}

/*
 * File trailer for mergePd.c
 *
 * [EOF]
 */
