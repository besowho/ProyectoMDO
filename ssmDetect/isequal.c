/*
 * File: isequal.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "isequal.h"

/* Function Definitions */

/*
 * Arguments    : const double varargin_1_data[]
 *                const int varargin_1_size[2]
 *                const double varargin_2_data[]
 *                const int varargin_2_size[2]
 * Return Type  : boolean_T
 */
boolean_T isequal(const double varargin_1_data[], const int varargin_1_size[2],
                  const double varargin_2_data[], const int varargin_2_size[2])
{
  boolean_T p;
  boolean_T b_p;
  int k;
  int32_T exitg2;
  boolean_T exitg1;
  p = false;
  b_p = false;
  k = 0;
  do {
    exitg2 = 0;
    if (k < 2) {
      if (varargin_1_size[k] != varargin_2_size[k]) {
        exitg2 = 1;
      } else {
        k++;
      }
    } else {
      b_p = true;
      exitg2 = 1;
    }
  } while (exitg2 == 0);

  if (b_p && (!((varargin_1_size[0] == 0) || (varargin_1_size[1] == 0))) &&
      (!((varargin_2_size[0] == 0) || (varargin_2_size[1] == 0)))) {
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= varargin_1_size[0] * varargin_1_size[1] - 1)) {
      if (!(varargin_1_data[k] == varargin_2_data[k])) {
        b_p = false;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (!b_p) {
  } else {
    p = true;
  }

  return p;
}

/*
 * File trailer for isequal.c
 *
 * [EOF]
 */
