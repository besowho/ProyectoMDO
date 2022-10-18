/*
 * File: getOptimalLineImage_constrained.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

#ifndef __GETOPTIMALLINEIMAGE_CONSTRAINED_H__
#define __GETOPTIMALLINEIMAGE_CONSTRAINED_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "ssmDetect_types.h"

/* Function Declarations */
extern void getOptimalLineImage_constrained(const double xy_data[], const int
  xy_size[2], const double ptsinit_data[], const int ptsinit_size[2], double
  delta, double a[3], double sel_xy_data[], int sel_xy_size[2]);

#endif

/*
 * File trailer for getOptimalLineImage_constrained.h
 *
 * [EOF]
 */
