/*
 * File: prod.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "prod.h"

/* Function Definitions */

/*
 * Arguments    : const double x[5]
 * Return Type  : double
 */
double prod(const double x[5])
{
  double y;
  int k;
  y = x[0];
  for (k = 0; k < 4; k++) {
    y *= x[k + 1];
  }

  return y;
}

/*
 * File trailer for prod.c
 *
 * [EOF]
 */
