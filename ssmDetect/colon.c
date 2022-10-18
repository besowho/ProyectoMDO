/*
 * File: colon.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "colon.h"

/* Function Definitions */

/*
 * Arguments    : double b
 *                int *n
 *                double *anew
 *                double *bnew
 *                boolean_T *n_too_large
 * Return Type  : void
 */
void float_colon_length(double b, int *n, double *anew, double *bnew, boolean_T *
  n_too_large)
{
  double ndbl;
  double cdiff;
  if (rtIsNaN(b)) {
    *n = 1;
    *anew = rtNaN;
    *bnew = b;
    *n_too_large = false;
  } else if (b < 1.0) {
    *n = 0;
    *anew = 1.0;
    *bnew = 0.0;
    *n_too_large = false;
  } else if (rtIsInf(b)) {
    *n = 1;
    *anew = rtNaN;
    *bnew = b;
    *n_too_large = !(1.0 == b);
  } else {
    *anew = 1.0;
    ndbl = floor((b - 1.0) + 0.5);
    *bnew = 1.0 + ndbl;
    cdiff = (1.0 + ndbl) - b;
    if (fabs(cdiff) < 4.4408920985006262E-16 * b) {
      ndbl++;
      *bnew = b;
    } else if (cdiff > 0.0) {
      *bnew = 1.0 + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    *n_too_large = false;
    *n = (int)ndbl;
  }
}

/*
 * File trailer for colon.c
 *
 * [EOF]
 */
