/*
 * File: sqrt.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "sqrt.h"

/* Function Definitions */

/*
 * Arguments    : double x[25]
 * Return Type  : void
 */
void b_sqrt(double x[25])
{
  int k;
  for (k = 0; k < 25; k++) {
    x[k] = sqrt(x[k]);
  }
}

/*
 * Arguments    : double x[10000]
 * Return Type  : void
 */
void c_sqrt(double x[10000])
{
  int k;
  for (k = 0; k < 10000; k++) {
    x[k] = sqrt(x[k]);
  }
}

/*
 * Arguments    : double x_data[]
 *                int x_size[2]
 * Return Type  : void
 */
void d_sqrt(double x_data[], int x_size[2])
{
  int i38;
  int k;
  i38 = x_size[1];
  for (k = 0; k < i38; k++) {
    x_data[k] = sqrt(x_data[k]);
  }
}

/*
 * File trailer for sqrt.c
 *
 * [EOF]
 */
