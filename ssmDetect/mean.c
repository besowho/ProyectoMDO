/*
 * File: mean.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "mean.h"
#include "combine_vector_elements.h"

/* Function Definitions */

/*
 * Arguments    : const double x[1251]
 * Return Type  : double
 */
double b_mean(const double x[1251])
{
  double y;
  int k;
  y = x[0];
  for (k = 0; k < 1250; k++) {
    y += x[k + 1];
  }

  y /= 1251.0;
  return y;
}

/*
 * Arguments    : const double x_data[]
 *                const int x_size[2]
 *                double y[2]
 * Return Type  : void
 */
void c_mean(const double x_data[], const int x_size[2], double y[2])
{
  int i23;
  combine_vector_elements(x_data, x_size, y);
  for (i23 = 0; i23 < 2; i23++) {
    y[i23] /= (double)x_size[1];
  }
}

/*
 * Arguments    : const double x[3]
 * Return Type  : double
 */
double d_mean(const double x[3])
{
  double y;
  int k;
  y = x[0];
  for (k = 0; k < 2; k++) {
    y += x[k + 1];
  }

  y /= 3.0;
  return y;
}

/*
 * Arguments    : const emxArray_real_T *x
 *                double y[5]
 * Return Type  : void
 */
void mean(const emxArray_real_T *x, double y[5])
{
  int iy;
  int ixstart;
  int j;
  int ix;
  double s;
  int k;
  if (x->size[1] == 0) {
    for (iy = 0; iy < 5; iy++) {
      y[iy] = 0.0;
    }
  } else {
    iy = -1;
    ixstart = -1;
    for (j = 0; j < 5; j++) {
      ixstart++;
      ix = ixstart;
      s = x->data[ixstart];
      for (k = 2; k <= x->size[1]; k++) {
        ix += 5;
        s += x->data[ix];
      }

      iy++;
      y[iy] = s;
    }
  }

  iy = x->size[1];
  for (ixstart = 0; ixstart < 5; ixstart++) {
    y[ixstart] /= (double)iy;
  }
}

/*
 * File trailer for mean.c
 *
 * [EOF]
 */
