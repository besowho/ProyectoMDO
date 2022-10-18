/*
 * File: rdivide.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "rdivide.h"

/* Function Definitions */

/*
 * Arguments    : const double x[2]
 *                const double y[2]
 *                double z[2]
 * Return Type  : void
 */
void rdivide(const double x[2], const double y[2], double z[2])
{
  int i10;
  for (i10 = 0; i10 < 2; i10++) {
    z[i10] = x[i10] / y[i10];
  }
}

/*
 * File trailer for rdivide.c
 *
 * [EOF]
 */
