/*
 * File: diff.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "diff.h"

/* Function Definitions */

/*
 * Arguments    : const boolean_T x_data[]
 *                const int x_size[2]
 *                double y_data[]
 *                int y_size[2]
 * Return Type  : void
 */
void diff(const boolean_T x_data[], const int x_size[2], double y_data[], int
          y_size[2])
{
  int dimSize;
  signed char ySize[2];
  int tmp2;
  int b_x_size;
  int ixStart;
  int iyStart;
  int r;
  int ixLead;
  int iyLead;
  int work_data_idx_0;
  int m;
  dimSize = x_size[0];
  if (x_size[0] == 0) {
    for (tmp2 = 0; tmp2 < 2; tmp2++) {
      ySize[tmp2] = (signed char)x_size[tmp2];
    }

    y_size[0] = 0;
    y_size[1] = ySize[1];
  } else {
    if (x_size[0] - 1 <= 1) {
      b_x_size = x_size[0] - 1;
    } else {
      b_x_size = 1;
    }

    if (b_x_size < 1) {
      for (tmp2 = 0; tmp2 < 2; tmp2++) {
        ySize[tmp2] = (signed char)x_size[tmp2];
      }

      y_size[0] = 0;
      y_size[1] = ySize[1];
    } else {
      for (tmp2 = 0; tmp2 < 2; tmp2++) {
        ySize[tmp2] = (signed char)x_size[tmp2];
      }

      y_size[0] = x_size[0] - 1;
      y_size[1] = ySize[1];
      if (!((x_size[0] - 1 == 0) || (ySize[1] == 0))) {
        ixStart = 0;
        iyStart = 0;
        for (r = 1; r <= x_size[1]; r++) {
          ixLead = ixStart + 1;
          iyLead = iyStart;
          work_data_idx_0 = x_data[ixStart];
          for (m = 2; m <= dimSize; m++) {
            tmp2 = work_data_idx_0;
            work_data_idx_0 = x_data[ixLead];
            tmp2 = x_data[ixLead] - tmp2;
            ixLead++;
            y_data[iyLead] = tmp2;
            iyLead++;
          }

          ixStart += dimSize;
          iyStart = (iyStart + dimSize) - 1;
        }
      }
    }
  }
}

/*
 * File trailer for diff.c
 *
 * [EOF]
 */
