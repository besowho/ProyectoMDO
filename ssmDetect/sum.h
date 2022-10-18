/*
 * File: sum.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

#ifndef __SUM_H__
#define __SUM_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "ssmDetect_types.h"

/* Function Declarations */
extern void b_sum(const double x[10000], double y[2500]);
extern void c_sum(const double x[10000], double y[2500]);
extern void d_sum(const double x[10000], double y[200]);
extern void e_sum(const double x[200], double y[4]);
extern double f_sum(const double x[4]);
extern void g_sum(const double x[12500], double y[5]);
extern double h_sum(const double x[2500]);
extern double i_sum(const boolean_T x_data[], const int x_size[1]);
extern double j_sum(const double x_data[], const int x_size[2]);
extern void sum(const double x[12500], double y[2500]);

#endif

/*
 * File trailer for sum.h
 *
 * [EOF]
 */
