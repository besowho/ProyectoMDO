/*
 * File: extractTheLargestRegion.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "extractTheLargestRegion.h"
#include "ssmDetect_emxutil.h"
#include "replacement_bwconncomp.h"

/* Function Definitions */

/*
 * Copy input image and clear it
 * Arguments    : const boolean_T T_data[]
 *                const int T_size[2]
 *                boolean_T R_data[]
 *                int R_size[2]
 * Return Type  : void
 */
void extractTheLargestRegion(const boolean_T T_data[], const int T_size[2],
  boolean_T R_data[], int R_size[2])
{
  int loop_ub;
  int i11;
  int i;
  int tmp_size_idx_1;
  emxArray_ConnectedComponent *CC;
  int max_idx;
  double max_val;
  int tmp_data[2500];
  R_size[0] = T_size[0];
  R_size[1] = T_size[1];
  loop_ub = T_size[0] * T_size[1];
  for (i11 = 0; i11 < loop_ub; i11++) {
    R_data[i11] = T_data[i11];
  }

  loop_ub = T_size[1];
  for (i11 = 0; i11 < loop_ub; i11++) {
    i = T_size[0];
    for (tmp_size_idx_1 = 0; tmp_size_idx_1 < i; tmp_size_idx_1++) {
      R_data[tmp_size_idx_1 + T_size[0] * i11] = false;
    }
  }

  emxInit_ConnectedComponent(&CC, 2);

  /*  Find connected components */
  replacement_bwconncomp(T_data, T_size, CC);

  /*  Find the largest component */
  /* [ ~, max_idx ] = max([ CC.area ]); */
  max_idx = -2;
  max_val = rtMinusInf;
  for (i = 0; i < CC->size[1]; i++) {
    if (CC->data[i].area > max_val) {
      max_val = CC->data[i].area;
      max_idx = i;
    }
  }

  if (max_idx + 1 == -1) {
  } else {
    /*  "Fill" the largest component into empty output image */
    i = CC->data[max_idx].pixel_idx.size[0];
    tmp_size_idx_1 = CC->data[max_idx].pixel_idx.size[1];
    loop_ub = CC->data[max_idx].pixel_idx.size[0] * CC->data[max_idx].
      pixel_idx.size[1];
    for (i11 = 0; i11 < loop_ub; i11++) {
      tmp_data[i11] = (int)CC->data[max_idx].pixel_idx.data[i11];
    }

    loop_ub = i * tmp_size_idx_1;
    for (i11 = 0; i11 < loop_ub; i11++) {
      R_data[tmp_data[i11] - 1] = true;
    }
  }

  emxFree_ConnectedComponent(&CC);
}

/*
 * File trailer for extractTheLargestRegion.c
 *
 * [EOF]
 */
