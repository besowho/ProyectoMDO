/*
 * File: bsxfun.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "bsxfun.h"

/* Function Definitions */

/*
 * Arguments    : const double a[10000]
 *                const double b[2500]
 *                double c[10000]
 * Return Type  : void
 */
void b_bsxfun(const double a[10000], const double b[2500], double c[10000])
{
  int asub[2];
  int bsub[2];
  int i;
  int bk;
  int ck;
  double cv[50];
  int k;
  for (i = 0; i < 2; i++) {
    asub[i] = 1;
    bsub[i] = 1;
  }

  i = 0;
  bk = 0;
  for (ck = 0; ck < 9952; ck += 50) {
    for (k = 0; k < 50; k++) {
      cv[k] = a[i + k] * b[bk + k];
    }

    memcpy(&c[ck], &cv[0], 50U * sizeof(double));
    if (asub[0] < 50) {
      i += 50;
      bk += 50;
      bsub[0]++;
      asub[0]++;
    } else if (bsub[0] < 50) {
      bk += 50;
      bsub[0]++;
    } else {
      asub[0] = 1;
      bsub[0] = 1;
      if (asub[1] < 4) {
        i += 50;
        bk -= 2450;
        asub[1]++;
      } else {
        asub[1] = 1;
      }
    }
  }
}

/*
 * Arguments    : const double a[12500]
 *                const double b[5]
 *                double c[12500]
 * Return Type  : void
 */
void bsxfun(const double a[12500], const double b[5], double c[12500])
{
  int ak;
  int ck;
  double cv[5];
  int k;
  ak = 0;
  for (ck = 0; ck < 12497; ck += 5) {
    for (k = 0; k < 5; k++) {
      cv[k] = a[ak + k] - b[k];
    }

    for (k = 0; k < 5; k++) {
      c[ck + k] = cv[k];
    }

    ak += 5;
  }
}

/*
 * Arguments    : const double a[10000]
 *                const double b[2500]
 *                double c[10000]
 * Return Type  : void
 */
void c_bsxfun(const double a[10000], const double b[2500], double c[10000])
{
  int ak;
  int bk;
  int ck;
  double cv[4];
  int k;
  ak = 0;
  bk = 0;
  for (ck = 0; ck < 9998; ck += 4) {
    for (k = 0; k < 4; k++) {
      cv[k] = a[ak + k] / b[bk];
    }

    for (k = 0; k < 4; k++) {
      c[ck + k] = cv[k];
    }

    ak += 4;
    bk++;
  }
}

/*
 * Arguments    : const double a[12500]
 *                const double b[2500]
 *                double c[12500]
 * Return Type  : void
 */
void d_bsxfun(const double a[12500], const double b[2500], double c[12500])
{
  int ak;
  int bk;
  int ck;
  double cv[5];
  int k;
  ak = 0;
  bk = 0;
  for (ck = 0; ck < 12497; ck += 5) {
    for (k = 0; k < 5; k++) {
      cv[k] = a[ak + k] * b[bk];
    }

    for (k = 0; k < 5; k++) {
      c[ck + k] = cv[k];
    }

    ak += 5;
    bk++;
  }
}

/*
 * Arguments    : const double a_data[]
 *                const int a_size[2]
 *                const double b[2]
 *                double c_data[]
 *                int c_size[2]
 * Return Type  : void
 */
void e_bsxfun(const double a_data[], const int a_size[2], const double b[2],
              double c_data[], int c_size[2])
{
  int asub;
  int ak;
  int a;
  int ck;
  double cv[2];
  int k;
  c_size[0] = 2;
  c_size[1] = a_size[1];
  if (a_size[1] == 0) {
  } else {
    asub = 1;
    ak = 0;
    a = a_size[1] << 1;
    for (ck = 0; ck <= a - 2; ck += 2) {
      for (k = 0; k < 2; k++) {
        cv[k] = a_data[ak + k] - b[k];
      }

      for (k = 0; k < 2; k++) {
        c_data[ck + k] = cv[k];
      }

      if (asub < a_size[1]) {
        ak += 2;
        asub++;
      } else {
        asub = 1;
      }
    }
  }
}

/*
 * File trailer for bsxfun.c
 *
 * [EOF]
 */
