/*
 * File: eml_sort.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

#ifndef __EML_SORT_H__
#define __EML_SORT_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "ssmDetect_types.h"

/* Function Declarations */
extern void b_eml_sort(const emxArray_real_T *x, emxArray_real_T *y,
  emxArray_int32_T *idx);
extern void eml_sort(const double x[2500], double y[2500]);

#endif

/*
 * File trailer for eml_sort.h
 *
 * [EOF]
 */
