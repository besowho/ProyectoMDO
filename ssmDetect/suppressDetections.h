/*
 * File: suppressDetections.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

#ifndef __SUPPRESSDETECTIONS_H__
#define __SUPPRESSDETECTIONS_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "ssmDetect_types.h"

/* Function Declarations */
extern void c_eml_li_find(const emxArray_boolean_T *x, emxArray_int32_T *y);
extern void mergeByProximity(emxArray_real_T *bbs, emxArray_real_T *bbs_out,
  emxArray_SelectedIndices *selected_out);

#endif

/*
 * File trailer for suppressDetections.h
 *
 * [EOF]
 */
