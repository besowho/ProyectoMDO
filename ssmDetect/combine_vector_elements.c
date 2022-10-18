/*
 * File: combine_vector_elements.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "combine_vector_elements.h"

/* Function Definitions */

/*
 * Arguments    : const double x_data[]
 *                const int x_size[2]
 *                double y[2]
 * Return Type  : void
 */
void combine_vector_elements(const double x_data[], const int x_size[2], double
  y[2])
{
  int iy;
  int ixstart;
  int j;
  int ix;
  double s;
  int k;
  if (x_size[1] == 0) {
    for (iy = 0; iy < 2; iy++) {
      y[iy] = 0.0;
    }
  } else {
    iy = -1;
    ixstart = -1;
    for (j = 0; j < 2; j++) {
      ixstart++;
      ix = ixstart;
      s = x_data[ixstart];
      for (k = 2; k <= x_size[1]; k++) {
        ix += 2;
        s += x_data[ix];
      }

      iy++;
      y[iy] = s;
    }
  }
}

/*
 * File trailer for combine_vector_elements.c
 *
 * [EOF]
 */
