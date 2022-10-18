/*
 * File: svd.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

#ifndef __SVD_H__
#define __SVD_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "ssmDetect_types.h"

/* Function Declarations */
extern void b_svd(const double A[4], double U[4], double S[4], double V[4]);
extern void svd(const double A[25], double U[25], double S[25], double V[25]);

#endif

/*
 * File trailer for svd.h
 *
 * [EOF]
 */
