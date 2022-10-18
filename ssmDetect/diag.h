/*
 * File: diag.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

#ifndef __DIAG_H__
#define __DIAG_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "ssmDetect_types.h"

/* Function Declarations */
extern void b_diag(const double v[25], double d[5]);
extern void c_diag(const double v[2], double d[4]);
extern void d_diag(const double v[4], double d[2]);
extern void diag(const double v[5], double d[25]);

#endif

/*
 * File trailer for diag.h
 *
 * [EOF]
 */
