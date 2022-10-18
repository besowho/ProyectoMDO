/*
 * File: getEdgeAndObjectsNoScaling.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

#ifndef __GETEDGEANDOBJECTSNOSCALING_H__
#define __GETEDGEANDOBJECTSNOSCALING_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "ssmDetect_types.h"

/* Function Declarations */
extern void getEdgeAndObjectsNoScaling(const emxArray_real_T *P_edge,
  emxArray_Object *objs_out, double pts[4], double xy_subset_data[], int
  xy_subset_size[2], boolean_T masked_Sea_data[], int masked_Sea_size[2]);

#endif

/*
 * File trailer for getEdgeAndObjectsNoScaling.h
 *
 * [EOF]
 */
