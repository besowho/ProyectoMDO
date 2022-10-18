/*
 * File: unique.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "unique.h"

/* Function Definitions */

/*
 * Arguments    : const double b_data[]
 *                int nb
 *                int *nMInf
 *                int *nFinite
 *                int *nPInf
 *                int *nNaN
 * Return Type  : void
 */
void count_nonfinites(const double b_data[], int nb, int *nMInf, int *nFinite,
                      int *nPInf, int *nNaN)
{
  *nMInf = 0;
  *nFinite = nb;
  while ((*nFinite >= 1) && rtIsNaN(b_data[*nFinite - 1])) {
    (*nFinite)--;
  }

  *nNaN = nb - *nFinite;
  while ((*nFinite >= 1) && rtIsInf(b_data[*nFinite - 1]) && (b_data[*nFinite -
          1] > 0.0)) {
    (*nFinite)--;
  }

  *nPInf = (nb - *nFinite) - *nNaN;
}

/*
 * File trailer for unique.c
 *
 * [EOF]
 */
