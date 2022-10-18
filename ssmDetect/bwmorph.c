/*
 * File: bwmorph.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "bwmorph.h"
#include "algbwmorph.h"

/* Function Definitions */

/*
 * Arguments    : boolean_T bwin_data[]
 *                int bwin_size[2]
 * Return Type  : void
 */
void b_bwmorph(boolean_T bwin_data[], int bwin_size[2])
{
  boolean_T b_bwin_data[2500];
  int b_bwin_size[2];
  int loop_ub;
  int i36;
  if ((bwin_size[0] == 0) || (bwin_size[1] == 0)) {
  } else {
    b_bwin_size[0] = bwin_size[0];
    b_bwin_size[1] = bwin_size[1];
    loop_ub = bwin_size[0] * bwin_size[1];
    for (i36 = 0; i36 < loop_ub; i36++) {
      b_bwin_data[i36] = bwin_data[i36];
    }

    b_algbwmorph(b_bwin_data, b_bwin_size, bwin_data, bwin_size);
  }
}

/*
 * Arguments    : boolean_T bwin_data[]
 *                int bwin_size[2]
 * Return Type  : void
 */
void bwmorph(boolean_T bwin_data[], int bwin_size[2])
{
  boolean_T b_bwin_data[2500];
  int b_bwin_size[2];
  int loop_ub;
  int i35;
  if ((bwin_size[0] == 0) || (bwin_size[1] == 0)) {
  } else {
    b_bwin_size[0] = bwin_size[0];
    b_bwin_size[1] = bwin_size[1];
    loop_ub = bwin_size[0] * bwin_size[1];
    for (i35 = 0; i35 < loop_ub; i35++) {
      b_bwin_data[i35] = bwin_data[i35];
    }

    algbwmorph(b_bwin_data, b_bwin_size, bwin_data, bwin_size);
  }
}

/*
 * File trailer for bwmorph.c
 *
 * [EOF]
 */
