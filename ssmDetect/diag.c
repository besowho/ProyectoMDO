/*
 * File: diag.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "diag.h"

/* Function Definitions */

/*
 * Arguments    : const double v[25]
 *                double d[5]
 * Return Type  : void
 */
void b_diag(const double v[25], double d[5])
{
  int j;
  for (j = 0; j < 5; j++) {
    d[j] = v[j * 6];
  }
}

/*
 * Arguments    : const double v[2]
 *                double d[4]
 * Return Type  : void
 */
void c_diag(const double v[2], double d[4])
{
  int j;
  for (j = 0; j < 4; j++) {
    d[j] = 0.0;
  }

  for (j = 0; j < 2; j++) {
    d[j + (j << 1)] = v[j];
  }
}

/*
 * Arguments    : const double v[4]
 *                double d[2]
 * Return Type  : void
 */
void d_diag(const double v[4], double d[2])
{
  int j;
  for (j = 0; j < 2; j++) {
    d[j] = v[j * 3];
  }
}

/*
 * Arguments    : const double v[5]
 *                double d[25]
 * Return Type  : void
 */
void diag(const double v[5], double d[25])
{
  int j;
  memset(&d[0], 0, 25U * sizeof(double));
  for (j = 0; j < 5; j++) {
    d[j + 5 * j] = v[j];
  }
}

/*
 * File trailer for diag.c
 *
 * [EOF]
 */
