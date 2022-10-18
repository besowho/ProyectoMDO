/*
 * File: ObjectPart.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

#ifndef __OBJECTPART_H__
#define __OBJECTPART_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "ssmDetect_types.h"

/* Function Declarations */
extern void ObjectPart(double num, emxArray_ObjectPart *parts);
extern void b_ObjectPart(double parts_bounding_box[4], double *parts_area,
  double parts_features[6], double parts_uncertainty_score[2]);

#endif

/*
 * File trailer for ObjectPart.h
 *
 * [EOF]
 */
