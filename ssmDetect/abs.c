/*
 * File: abs.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "abs.h"

/* Function Definitions */

/*
 * Arguments    : const double x_data[]
 *                const int x_size[2]
 *                double y_data[]
 *                int y_size[2]
 * Return Type  : void
 */
void b_abs(const double x_data[], const int x_size[2], double y_data[], int
           y_size[2])
{
  short iv7[2];
  int k;
  for (k = 0; k < 2; k++) {
    iv7[k] = (short)x_size[k];
  }

  y_size[0] = 1;
  y_size[1] = iv7[1];
  for (k = 0; k < x_size[1]; k++) {
    y_data[k] = fabs(x_data[k]);
  }
}

/*
 * Arguments    : const double x[3]
 *                double y[3]
 * Return Type  : void
 */
void c_abs(const double x[3], double y[3])
{
  int k;
  for (k = 0; k < 3; k++) {
    y[k] = fabs(x[k]);
  }
}

/*
 * File trailer for abs.c
 *
 * [EOF]
 */
