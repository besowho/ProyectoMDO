/*
 * File: power.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "power.h"

/* Function Declarations */
static void eml_scalexp_alloc(const int varargin_1_size[2], int z_size[2]);

/* Function Definitions */

/*
 * Arguments    : const int varargin_1_size[2]
 *                int z_size[2]
 * Return Type  : void
 */
static void eml_scalexp_alloc(const int varargin_1_size[2], int z_size[2])
{
  short iv8[2];
  int i24;
  for (i24 = 0; i24 < 2; i24++) {
    iv8[i24] = (short)varargin_1_size[i24];
  }

  z_size[0] = 1;
  z_size[1] = iv8[1];
}

/*
 * Arguments    : const double a_data[]
 *                const int a_size[2]
 *                double y_data[]
 *                int y_size[2]
 * Return Type  : void
 */
void power(const double a_data[], const int a_size[2], double y_data[], int
           y_size[2])
{
  int k;
  eml_scalexp_alloc(a_size, y_size);
  for (k = 0; k < y_size[1]; k++) {
    y_data[k] = a_data[k] * a_data[k];
  }
}

/*
 * File trailer for power.c
 *
 * [EOF]
 */
