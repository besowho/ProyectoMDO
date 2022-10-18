/*
 * File: mean.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

#ifndef __MEAN_H__
#define __MEAN_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "ssmDetect_types.h"

/* Function Declarations */
extern double b_mean(const double x[1251]);
extern void c_mean(const double x_data[], const int x_size[2], double y[2]);
extern double d_mean(const double x[3]);
extern void mean(const emxArray_real_T *x, double y[5]);

#endif

/*
 * File trailer for mean.h
 *
 * [EOF]
 */
