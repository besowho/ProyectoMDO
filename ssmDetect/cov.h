/*
 * File: cov.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

#ifndef __COV_H__
#define __COV_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "ssmDetect_types.h"

/* Function Declarations */
extern void b_cov(const double x_data[], const int x_size[2], double xy[4]);
extern void cov(const emxArray_real_T *x, double xy[25]);

#endif

/*
 * File trailer for cov.h
 *
 * [EOF]
 */
