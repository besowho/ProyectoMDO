/*
 * File: rot90.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "rot90.h"

/* Function Definitions */

/*
 * Arguments    : const double A[9]
 *                double B[9]
 * Return Type  : void
 */
void rot90(const double A[9], double B[9])
{
  int j;
  int i;
  for (j = 0; j < 3; j++) {
    for (i = 0; i < 3; i++) {
      B[i + 3 * j] = A[(3 * (2 - j) - i) + 2];
    }
  }
}

/*
 * File trailer for rot90.c
 *
 * [EOF]
 */
