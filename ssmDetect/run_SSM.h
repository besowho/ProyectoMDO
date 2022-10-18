/*
 * File: run_SSM.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

#ifndef __RUN_SSM_H__
#define __RUN_SSM_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "ssmDetect_types.h"

/* Function Declarations */
extern void run_SSM(struct0_T *detector_state, const double data[12500],
                    emxArray_real_T *Q_sum_large);

#endif

/*
 * File trailer for run_SSM.h
 *
 * [EOF]
 */
