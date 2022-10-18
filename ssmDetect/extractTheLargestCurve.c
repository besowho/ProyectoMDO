/*
 * File: extractTheLargestCurve.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "extractTheLargestCurve.h"
#include "ssmDetect_emxutil.h"
#include "getEdgeAndObjectsNoScaling.h"
#include "replacement_bwconncomp.h"
#include "ssmDetect_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : const boolean_T T_data[]
 *                const int T_size[2]
 *                double points_data[]
 *                int points_size[2]
 *                double pixel_idx_data[]
 *                int pixel_idx_size[2]
 * Return Type  : void
 */
void extractTheLargestCurve(const boolean_T T_data[], const int T_size[2],
  double points_data[], int points_size[2], double pixel_idx_data[], int
  pixel_idx_size[2])
{
  emxArray_ConnectedComponent *CC;
  int max_idx;
  double max_val;
  int i;
  int i21;
  signed char siz[2];
  int idx_size_idx_0;
  int idx_size_idx_1;
  int idx_data[2500];
  int vk_data[2500];
  emxInit_ConnectedComponent(&CC, 2);
  pixel_idx_size[0] = 0;
  pixel_idx_size[1] = 0;
  points_size[0] = 0;
  points_size[1] = 0;

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
    /*  Pixel indices of the largest curve (largest component's perimeter) */
    pixel_idx_size[0] = CC->data[max_idx].pixel_idx.size[0];
    pixel_idx_size[1] = CC->data[max_idx].pixel_idx.size[1];
    i = CC->data[max_idx].pixel_idx.size[0] * CC->data[max_idx].pixel_idx.size[1];
    for (i21 = 0; i21 < i; i21++) {
      pixel_idx_data[i21] = CC->data[max_idx].pixel_idx.data[i21];
    }

    /*  Actual points */
    for (i21 = 0; i21 < 2; i21++) {
      siz[i21] = (signed char)T_size[i21];
    }

    idx_size_idx_0 = CC->data[max_idx].pixel_idx.size[0];
    idx_size_idx_1 = CC->data[max_idx].pixel_idx.size[1];
    i = CC->data[max_idx].pixel_idx.size[0] * CC->data[max_idx].pixel_idx.size[1];
    for (i21 = 0; i21 < i; i21++) {
      idx_data[i21] = (int)CC->data[max_idx].pixel_idx.data[i21];
    }

    i = idx_size_idx_0 * idx_size_idx_1;
    for (i21 = 0; i21 < i; i21++) {
      idx_data[i21]--;
    }

    i = idx_size_idx_0 * idx_size_idx_1;
    for (i21 = 0; i21 < i; i21++) {
      vk_data[i21] = div_s32(idx_data[i21], siz[0]);
    }

    i = idx_size_idx_0 * idx_size_idx_1;
    for (i21 = 0; i21 < i; i21++) {
      idx_data[i21] -= vk_data[i21] * siz[0];
    }

    points_size[0] = idx_size_idx_0;
    points_size[1] = idx_size_idx_1 + idx_size_idx_1;
    for (i21 = 0; i21 < idx_size_idx_1; i21++) {
      for (i = 0; i < idx_size_idx_0; i++) {
        points_data[i + idx_size_idx_0 * i21] = (double)(vk_data[i +
          idx_size_idx_0 * i21] + 1) - 1.0;
      }
    }

    for (i21 = 0; i21 < idx_size_idx_1; i21++) {
      for (i = 0; i < idx_size_idx_0; i++) {
        points_data[i + idx_size_idx_0 * (i21 + idx_size_idx_1)] = idx_data[i +
          idx_size_idx_0 * i21] + 1;
      }
    }
  }

  emxFree_ConnectedComponent(&CC);
}

/*
 * File trailer for extractTheLargestCurve.c
 *
 * [EOF]
 */
