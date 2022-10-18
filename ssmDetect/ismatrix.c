/*
 * File: ismatrix.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "ismatrix.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 * Return Type  : boolean_T
 */
boolean_T ismatrix(const emxArray_real_T *x)
{
  int k;
  k = 3;
  while ((k > 2) && (x->size[2] == 1)) {
    k = 2;
  }

  return k == 2;
}

/*
 * File trailer for ismatrix.c
 *
 * [EOF]
 */
