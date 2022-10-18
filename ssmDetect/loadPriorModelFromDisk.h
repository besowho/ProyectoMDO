/*
 * File: loadPriorModelFromDisk.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

#ifndef __LOADPRIORMODELFROMDISK_H__
#define __LOADPRIORMODELFROMDISK_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "ssmDetect_types.h"

/* Function Declarations */
extern void loadPriorModelFromDisk(Colorspace type_colorspace, Colorspace
  *model_prior_type_colorspace, struct1_T model_prior_mixture[3], boolean_T
  *model_prior_is_initialized, double em_image_size[2]);

#endif

/*
 * File trailer for loadPriorModelFromDisk.h
 *
 * [EOF]
 */
