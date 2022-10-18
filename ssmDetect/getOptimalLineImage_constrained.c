/*
 * File: getOptimalLineImage_constrained.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "getOptimalLineImage_constrained.h"
#include "sqrt.h"
#include "ssmDetect_emxutil.h"
#include "suppressDetections.h"
#include "mean.h"
#include "abs.h"
#include "svd.h"
#include "combine_vector_elements.h"
#include "sum.h"
#include "exp.h"
#include "power.h"
#include "cov.h"

/* Function Definitions */

/*
 * Arguments    : const double xy_data[]
 *                const int xy_size[2]
 *                const double ptsinit_data[]
 *                const int ptsinit_size[2]
 *                double delta
 *                double a[3]
 *                double sel_xy_data[]
 *                int sel_xy_size[2]
 * Return Type  : void
 */
void getOptimalLineImage_constrained(const double xy_data[], const int xy_size[2],
  const double ptsinit_data[], const int ptsinit_size[2], double delta, double
  a[3], double sel_xy_data[], int sel_xy_size[2])
{
  int i;
  static double b_ptsinit_data[5000];
  int b_ptsinit_size[2];
  int i22;
  int br;
  int ar;
  double C[4];
  double unusedU2[4];
  double unusedU1[4];
  double U[4];
  double mnxy[2];
  double b_a[2];
  double B;
  double a0[3];
  int j;
  emxArray_int32_T *r5;
  boolean_T exitg1;
  double w_data[2500];
  int a_size[2];
  double rr_data[2500];
  int zerovls_size[2];
  boolean_T zerovls_data[2500];
  int w_size[2];
  emxArray_boolean_T b_zerovls_data;
  int tmp_data[2500];
  short iv6[2];
  int xyw_size[2];
  static double xyw_data[5000];
  int k;
  int wd_size_idx_1;
  static double wd_data[5000];
  static double b_data[5000];
  int ic;
  int ia;
  double c_a[2];
  double b_a0[3];
  double dv12[3];
  boolean_T c_zerovls_data[2500];
  int b_zerovls_size[2];
  emxArray_boolean_T d_zerovls_data;
  for (i = 0; i < 3; i++) {
    a[i] = 0.0;
  }

  b_ptsinit_size[0] = ptsinit_size[1];
  b_ptsinit_size[1] = 2;
  for (i22 = 0; i22 < 2; i22++) {
    br = ptsinit_size[1];
    for (ar = 0; ar < br; ar++) {
      b_ptsinit_data[ar + b_ptsinit_size[0] * i22] = ptsinit_data[i22 +
        ptsinit_size[0] * ar];
    }
  }

  b_cov(b_ptsinit_data, b_ptsinit_size, C);
  b_svd(C, U, unusedU1, unusedU2);
  for (i22 = 0; i22 < 2; i22++) {
    a[i22] = U[2 + i22];
  }

  c_mean(ptsinit_data, ptsinit_size, mnxy);
  b_a[0] = a[0];
  b_a[1] = a[1];
  B = 0.0;
  for (i22 = 0; i22 < 2; i22++) {
    B += -b_a[i22] * mnxy[i22];
  }

  a[2] = B;
  for (i = 0; i < 3; i++) {
    a0[i] = a[i];
  }

  /* [delta, delta/4 ] ; */
  j = 0;
  emxInit_int32_T(&r5, 2);
  exitg1 = false;
  while ((!exitg1) && (j < 5)) {
    br = xy_size[1];
    a_size[0] = 1;
    a_size[1] = xy_size[1];
    for (i22 = 0; i22 < br; i22++) {
      w_data[i22] = (a[0] * xy_data[xy_size[0] * i22] + a[1] * xy_data[1 +
                     xy_size[0] * i22]) + a[2];
    }

    b_abs(w_data, a_size, rr_data, b_ptsinit_size);
    b_ptsinit_size[0] = 1;
    br = b_ptsinit_size[1];
    for (i22 = 0; i22 < br; i22++) {
      rr_data[i22] /= delta;
    }

    zerovls_size[0] = 1;
    zerovls_size[1] = b_ptsinit_size[1];
    br = b_ptsinit_size[1];
    for (i22 = 0; i22 < br; i22++) {
      zerovls_data[i22] = (rr_data[i22] > 2.0);
    }

    power(rr_data, b_ptsinit_size, w_data, w_size);
    w_size[0] = 1;
    br = w_size[1];
    for (i22 = 0; i22 < br; i22++) {
      w_data[i22] *= -0.5;
    }

    c_exp(w_data, w_size);
    b_zerovls_data.data = (boolean_T *)&zerovls_data;
    b_zerovls_data.size = (int *)&zerovls_size;
    b_zerovls_data.allocatedSize = 2500;
    b_zerovls_data.numDimensions = 2;
    b_zerovls_data.canFreeData = false;
    c_eml_li_find(&b_zerovls_data, r5);
    i = r5->size[1];
    br = r5->size[0] * r5->size[1];
    for (i22 = 0; i22 < br; i22++) {
      tmp_data[i22] = r5->data[i22];
    }

    for (i22 = 0; i22 < i; i22++) {
      w_data[tmp_data[i22] - 1] = 0.0;
    }

    B = j_sum(w_data, w_size);
    br = w_size[1];
    for (i22 = 0; i22 < br; i22++) {
      w_data[i22] /= B;
    }

    /* mnxy = sum(bsxfun(@times, xy, w),2) ;   */
    for (i22 = 0; i22 < 2; i22++) {
      iv6[i22] = (short)xy_size[i22];
    }

    xyw_size[0] = 2;
    xyw_size[1] = iv6[1];
    br = iv6[1] << 1;
    for (i22 = 0; i22 < br; i22++) {
      xyw_data[i22] = 0.0;
    }

    for (k = 0; k < 2; k++) {
      br = xy_size[1] - 1;
      for (i22 = 0; i22 <= br; i22++) {
        xyw_data[k + (i22 << 1)] = xy_data[k + xy_size[0] * i22] * w_data[i22];
      }
    }

    combine_vector_elements(xyw_data, xyw_size, mnxy);

    /* wd = bsxfun(@times, bsxfun(@minus,xy,mnxy), sqrt(w)) ; */
    for (i22 = 0; i22 < 2; i22++) {
      iv6[i22] = (short)xy_size[i22];
    }

    xyw_size[0] = 2;
    xyw_size[1] = iv6[1];
    br = iv6[1] << 1;
    for (i22 = 0; i22 < br; i22++) {
      xyw_data[i22] = 0.0;
    }

    for (k = 0; k < xy_size[1]; k++) {
      for (i22 = 0; i22 < 2; i22++) {
        xyw_data[i22 + (k << 1)] = xy_data[i22 + xy_size[0] * k] - mnxy[i22];
      }
    }

    for (i22 = 0; i22 < 2; i22++) {
      iv6[i22] = (short)xyw_size[i22];
    }

    wd_size_idx_1 = iv6[1];
    br = iv6[1] << 1;
    for (i22 = 0; i22 < br; i22++) {
      wd_data[i22] = 0.0;
    }

    for (k = 0; k < 2; k++) {
      b_ptsinit_size[0] = 1;
      b_ptsinit_size[1] = w_size[1];
      br = w_size[1];
      for (i22 = 0; i22 < br; i22++) {
        rr_data[i22] = w_data[i22];
      }

      d_sqrt(rr_data, b_ptsinit_size);
      br = xyw_size[1] - 1;
      for (i22 = 0; i22 <= br; i22++) {
        wd_data[k + (i22 << 1)] = xyw_data[k + (i22 << 1)] *
          rr_data[b_ptsinit_size[0] * i22];
      }
    }

    i = iv6[1];
    for (i22 = 0; i22 < 2; i22++) {
      for (ar = 0; ar < wd_size_idx_1; ar++) {
        b_data[ar + i * i22] = wd_data[i22 + (ar << 1)];
      }
    }

    if (iv6[1] == 1) {
      for (i22 = 0; i22 < 2; i22++) {
        for (ar = 0; ar < 2; ar++) {
          C[i22 + (ar << 1)] = 0.0;
          for (br = 0; br < wd_size_idx_1; br++) {
            C[i22 + (ar << 1)] += wd_data[i22 + (br << 1)] * b_data[br + i * ar];
          }
        }
      }
    } else {
      k = iv6[1];
      for (i22 = 0; i22 < 4; i22++) {
        C[i22] = 0.0;
      }

      for (i = 0; i < 4; i += 2) {
        for (ic = i; ic + 1 <= i + 2; ic++) {
          C[ic] = 0.0;
        }
      }

      br = 0;
      for (i = 0; i < 4; i += 2) {
        ar = 0;
        i22 = br + k;
        for (wd_size_idx_1 = br; wd_size_idx_1 + 1 <= i22; wd_size_idx_1++) {
          if (b_data[wd_size_idx_1] != 0.0) {
            ia = ar;
            for (ic = i; ic + 1 <= i + 2; ic++) {
              ia++;
              C[ic] += b_data[wd_size_idx_1] * wd_data[ia - 1];
            }
          }

          ar += 2;
        }

        br += k;
      }
    }

    b_svd(C, U, unusedU1, unusedU2);
    for (i22 = 0; i22 < 2; i22++) {
      a[i22] = U[2 + i22];
    }

    c_a[0] = a[0];
    c_a[1] = a[1];
    B = 0.0;
    for (i22 = 0; i22 < 2; i22++) {
      B += -c_a[i22] * mnxy[i22];
    }

    a[2] = B;
    for (i = 0; i < 3; i++) {
      b_a0[i] = a0[i] - a[i];
    }

    c_abs(b_a0, dv12);
    if (d_mean(dv12) < 1.0E-10) {
      exitg1 = true;
    } else {
      for (i = 0; i < 3; i++) {
        a0[i] = a[i];
      }

      j++;
    }
  }

  b_zerovls_size[0] = 1;
  b_zerovls_size[1] = zerovls_size[1];
  br = zerovls_size[0] * zerovls_size[1];
  for (i22 = 0; i22 < br; i22++) {
    c_zerovls_data[i22] = (zerovls_data[i22] == 0);
  }

  d_zerovls_data.data = (boolean_T *)&c_zerovls_data;
  d_zerovls_data.size = (int *)&b_zerovls_size;
  d_zerovls_data.allocatedSize = 2500;
  d_zerovls_data.numDimensions = 2;
  d_zerovls_data.canFreeData = false;
  c_eml_li_find(&d_zerovls_data, r5);
  sel_xy_size[0] = 2;
  sel_xy_size[1] = r5->size[1];
  br = r5->size[1];
  for (i22 = 0; i22 < br; i22++) {
    for (ar = 0; ar < 2; ar++) {
      sel_xy_data[ar + (i22 << 1)] = xy_data[ar + xy_size[0] * (r5->data
        [r5->size[0] * i22] - 1)];
    }
  }

  emxFree_int32_T(&r5);
}

/*
 * File trailer for getOptimalLineImage_constrained.c
 *
 * [EOF]
 */
