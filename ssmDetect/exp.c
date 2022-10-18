/*
 * File: exp.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "exp.h"

/* Function Definitions */

/*
 * Arguments    : double x[2500]
 * Return Type  : void
 */
void b_exp(double x[2500])
{
  int k;
  for (k = 0; k < 2500; k++) {
    x[k] = exp(x[k]);
  }
}

/*
 * Arguments    : double x_data[]
 *                int x_size[2]
 * Return Type  : void
 */
void c_exp(double x_data[], int x_size[2])
{
  int i37;
  int k;
  i37 = x_size[1];
  for (k = 0; k < i37; k++) {
    x_data[k] = exp(x_data[k]);
  }
}

/*
 * File trailer for exp.c
 *
 * [EOF]
 */
