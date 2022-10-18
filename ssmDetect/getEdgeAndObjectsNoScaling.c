/*
 * File: getEdgeAndObjectsNoScaling.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "getEdgeAndObjectsNoScaling.h"
#include "abs.h"
#include "ObjectPart.h"
#include "ssmDetect_emxutil.h"
#include "suppressDetections.h"
#include "Object.h"
#include "replacement_bwconncomp.h"
#include "getOptimalLineImage_constrained.h"
#include "bsxfun.h"
#include "diag.h"
#include "extractTheLargestCurve.h"
#include "sum.h"
#include "diff.h"
#include "bwmorph.h"
#include "extractTheLargestRegion.h"
#include "rdivide.h"
#include "ssmDetect_rtwutil.h"

/* Function Declarations */
static void eml_xgemm(int n, const double A[4], const double B_data[], double
                      C_data[]);

/* Function Definitions */

/*
 * Arguments    : int n
 *                const double A[4]
 *                const double B_data[]
 *                double C_data[]
 * Return Type  : void
 */
static void eml_xgemm(int n, const double A[4], const double B_data[], double
                      C_data[])
{
  int c;
  int cr;
  int ic;
  int br;
  int ar;
  int ib;
  int ia;
  if (n == 0) {
  } else {
    c = (n - 1) << 1;
    for (cr = 0; cr <= c; cr += 2) {
      for (ic = cr + 1; ic <= cr + 2; ic++) {
        C_data[ic - 1] = 0.0;
      }
    }

    br = 0;
    for (cr = 0; cr <= c; cr += 2) {
      ar = -1;
      for (ib = br; ib + 1 <= br + 2; ib++) {
        if (B_data[ib] != 0.0) {
          ia = ar;
          for (ic = cr; ic + 1 <= cr + 2; ic++) {
            ia++;
            C_data[ic] += B_data[ib] * A[ia];
          }
        }

        ar += 2;
      }

      br += 2;
    }
  }
}

/*
 * Arguments    : const emxArray_real_T *P_edge
 *                emxArray_Object *objs_out
 *                double pts[4]
 *                double xy_subset_data[]
 *                int xy_subset_size[2]
 *                boolean_T masked_Sea_data[]
 *                int masked_Sea_size[2]
 * Return Type  : void
 */
void getEdgeAndObjectsNoScaling(const emxArray_real_T *P_edge, emxArray_Object
  *objs_out, double pts[4], double xy_subset_data[], int xy_subset_size[2],
  boolean_T masked_Sea_data[], int masked_Sea_size[2])
{
  int n;
  int vstride;
  int P_edge_size[2];
  double size_obj[2];
  double obj_uncertainty_score[2];
  double dv10[2];
  double Tt[4];
  signed char outsz[3];
  int ixstart;
  int iindx_data[2500];
  int k;
  int ix;
  int iy;
  int j;
  int k0;
  double xmin;
  int itmp;
  int nxin;
  int mtmp;
  boolean_T exitg3;
  int T_size[2];
  boolean_T T_data[2500];
  boolean_T b_T_data[2500];
  int b_T_size[2];
  int c_T_size[2];
  static double tmp_data[2450];
  static double b_tmp_data[2450];
  static double c_tmp_data[2500];
  static double d_tmp_data[2500];
  boolean_T dT_data[2500];
  int T[1];
  emxArray_ConnectedComponent *CC;
  emxArray_ObjectPart *objs;
  emxArray_Object_0 r0;
  emxArray_real_T *idx;
  emxArray_boolean_T *b;
  emxArray_real_T *bbs;
  emxArray_SelectedIndices *selected;
  emxArray_Object *r1;
  emxArray_real_T *b_bbs;
  emxArray_Object_1x1 b_objs_out;
  b_Object r2;
  emxArray_ObjectPart *b_objs;
  emxArray_ObjectPart *c_objs;
  emxArray_ObjectPart *d_objs;
  emxArray_ObjectPart *e_objs;
  boolean_T guard1 = false;
  int dT[1];
  int dT_size[2];
  static double largest_curve_data[5000];
  int b_size[2];
  static double b_data[5000];
  int y_size[2];
  static double y_data[5000];
  double b_Tt[4];
  double dv11[2];
  double a[3];
  int d_T_size[2];
  double counter;
  double obj_features[6];
  int idx_data[2500];
  int vk_data[2500];
  int x_data[2500];
  int b_mtmp;
  double width;
  double height;
  int b_xy_subset_size[2];
  static double varargin_1_data[2500];
  boolean_T exitg2;
  c_ObjectPart expl_temp;
  int32_T exitg1;
  n = P_edge->size[0];
  vstride = P_edge->size[1];
  P_edge_size[0] = n;
  P_edge_size[1] = vstride;
  for (n = 0; n < 2; n++) {
    size_obj[n] = P_edge_size[1 - n];
  }

  for (n = 0; n < 2; n++) {
    obj_uncertainty_score[n] = 480.0 + 160.0 * (double)n;
  }

  rdivide(obj_uncertainty_score, size_obj, dv10);
  for (n = 0; n < 2; n++) {
    obj_uncertainty_score[n] = dv10[1 - n];
  }

  c_diag(obj_uncertainty_score, Tt);

  /* % *** Sea edge and its uncertainty score *** */
  for (n = 0; n < 3; n++) {
    outsz[n] = (signed char)P_edge->size[n];
  }

  ixstart = outsz[0] * outsz[1];
  for (n = 0; n < ixstart; n++) {
    iindx_data[n] = 1;
  }

  n = P_edge->size[2];
  k = 3;
  while ((k > 2) && (P_edge->size[2] == 1)) {
    k = 2;
  }

  if (3 > k) {
    vstride = P_edge->size[0] * P_edge->size[1] * P_edge->size[2];
  } else {
    vstride = 1;
    for (k = 0; k < 2; k++) {
      vstride *= P_edge->size[k];
    }
  }

  ix = 0;
  iy = -1;
  for (j = 1; j <= vstride; j++) {
    ix++;
    ixstart = ix;
    k0 = ix + (n - 1) * vstride;
    xmin = P_edge->data[ix - 1];
    itmp = 1;
    if (n > 1) {
      nxin = 1;
      if (rtIsNaN(P_edge->data[ix - 1])) {
        mtmp = ix + vstride;
        exitg3 = false;
        while ((!exitg3) && (((vstride > 0) && (mtmp <= k0)) || ((vstride < 0) &&
                 (mtmp >= k0)))) {
          nxin++;
          ixstart = mtmp;
          if (!rtIsNaN(P_edge->data[mtmp - 1])) {
            xmin = P_edge->data[mtmp - 1];
            itmp = nxin;
            exitg3 = true;
          } else {
            mtmp += vstride;
          }
        }
      }

      if (ixstart < k0) {
        mtmp = ixstart + vstride;
        while (((vstride > 0) && (mtmp <= k0)) || ((vstride < 0) && (mtmp >= k0)))
        {
          nxin++;
          if (P_edge->data[mtmp - 1] > xmin) {
            xmin = P_edge->data[mtmp - 1];
            itmp = nxin;
          }

          mtmp += vstride;
        }
      }
    }

    iy++;
    iindx_data[iy] = itmp;
  }

  T_size[0] = outsz[0];
  T_size[1] = outsz[1];
  ixstart = outsz[0] * outsz[1];
  for (n = 0; n < ixstart; n++) {
    T_data[n] = (iindx_data[n] == 3);
  }

  bwmorph(T_data, T_size);
  b_T_size[0] = T_size[0];
  b_T_size[1] = T_size[1];
  ixstart = T_size[0] * T_size[1];
  for (n = 0; n < ixstart; n++) {
    b_T_data[n] = T_data[n];
  }

  extractTheLargestRegion(b_T_data, b_T_size, T_data, T_size);
  ixstart = T_size[0] * T_size[1];
  for (n = 0; n < ixstart; n++) {
    T_data[n] = !T_data[n];
  }

  b_bwmorph(T_data, T_size);
  ixstart = T_size[0] * T_size[1];
  for (n = 0; n < ixstart; n++) {
    T_data[n] = !T_data[n];
  }

  masked_Sea_size[0] = T_size[1];
  masked_Sea_size[1] = T_size[0];
  ixstart = T_size[0];
  for (n = 0; n < ixstart; n++) {
    mtmp = T_size[1];
    for (vstride = 0; vstride < mtmp; vstride++) {
      masked_Sea_data[vstride + masked_Sea_size[0] * n] = T_data[n + T_size[0] *
        vstride];
    }
  }

  c_T_size[0] = T_size[1];
  c_T_size[1] = T_size[0];
  ixstart = T_size[0];
  for (n = 0; n < ixstart; n++) {
    mtmp = T_size[1];
    for (vstride = 0; vstride < mtmp; vstride++) {
      b_T_data[vstride + c_T_size[0] * n] = T_data[n + T_size[0] * vstride];
    }
  }

  diff(b_T_data, c_T_size, tmp_data, b_T_size);
  diff(T_data, T_size, b_tmp_data, P_edge_size);
  iy = T_size[0];
  ixstart = T_size[0];
  for (n = 0; n < ixstart; n++) {
    c_tmp_data[n] = 0.0;
  }

  ixstart = b_T_size[0];
  for (n = 0; n < ixstart; n++) {
    mtmp = b_T_size[1];
    for (vstride = 0; vstride < mtmp; vstride++) {
      c_tmp_data[vstride + iy * (n + 1)] = tmp_data[n + b_T_size[0] * vstride];
    }
  }

  k0 = 1 + P_edge_size[0];
  ixstart = T_size[1];
  for (n = 0; n < ixstart; n++) {
    d_tmp_data[k0 * n] = 0.0;
  }

  ixstart = P_edge_size[1];
  for (n = 0; n < ixstart; n++) {
    mtmp = P_edge_size[0];
    for (vstride = 0; vstride < mtmp; vstride++) {
      d_tmp_data[(vstride + k0 * n) + 1] = b_tmp_data[vstride + P_edge_size[0] *
        n];
    }
  }

  nxin = T_size[0];
  ixstart = 1 + b_T_size[0];
  for (n = 0; n < ixstart; n++) {
    for (vstride = 0; vstride < iy; vstride++) {
      dT_data[vstride + nxin * n] = ((c_tmp_data[vstride + iy * n] != 0.0) ||
        (d_tmp_data[vstride + k0 * n] != 0.0));
    }
  }

  /*  try */
  T[0] = T_size[0] * T_size[1];
  emxInit_ConnectedComponent(&CC, 2);
  emxInit_ObjectPart(&objs, 1);
  emxInit_Object_0(&r0);
  emxInit_real_T(&idx, 2);
  emxInit_boolean_T(&b, 2);
  emxInit_real_T(&bbs, 2);
  emxInit_SelectedIndices(&selected, 1);
  emxInit_Object(&r1, 1);
  emxInit_real_T(&b_bbs, 2);
  emxInit_Object_1x1(&b_objs_out);
  emxInitStruct_Object(&r2);
  emxInit_ObjectPart(&b_objs, 1);
  emxInit_ObjectPart(&c_objs, 1);
  emxInit_ObjectPart(&d_objs, 1);
  emxInit_ObjectPart(&e_objs, 1);
  guard1 = false;
  if (i_sum(T_data, T) != T_size[0] * T_size[1]) {
    dT[0] = T_size[0] * (1 + b_T_size[0]);
    if (i_sum(dT_data, dT) != 0.0) {
      dT_size[0] = 1 + b_T_size[0];
      dT_size[1] = T_size[0];
      ixstart = T_size[0];
      for (n = 0; n < ixstart; n++) {
        mtmp = 1 + b_T_size[0];
        for (vstride = 0; vstride < mtmp; vstride++) {
          b_T_data[vstride + dT_size[0] * n] = dT_data[n + nxin * vstride];
        }
      }

      extractTheLargestCurve(b_T_data, dT_size, largest_curve_data, P_edge_size,
        c_tmp_data, b_T_size);
      b_size[0] = P_edge_size[1];
      ixstart = P_edge_size[0];
      for (n = 0; n < ixstart; n++) {
        mtmp = P_edge_size[1];
        for (vstride = 0; vstride < mtmp; vstride++) {
          b_data[vstride + b_size[0] * n] = largest_curve_data[n + P_edge_size[0]
            * vstride];
        }
      }

      if (P_edge_size[1] == 1) {
        y_size[0] = 2;
        y_size[1] = P_edge_size[0];
        for (n = 0; n < 2; n++) {
          ixstart = P_edge_size[0];
          for (vstride = 0; vstride < ixstart; vstride++) {
            y_data[n + (vstride << 1)] = 0.0;
            for (iy = 0; iy < 2; iy++) {
              y_data[n + (vstride << 1)] += Tt[n + (iy << 1)] * b_data[iy +
                b_size[0] * vstride];
            }
          }
        }
      } else {
        y_size[0] = 2;
        y_size[1] = P_edge_size[0];
        ixstart = P_edge_size[0] << 1;
        for (n = 0; n < ixstart; n++) {
          y_data[n] = 0.0;
        }

        eml_xgemm(P_edge_size[0], Tt, b_data, y_data);
      }

      for (n = 0; n < 4; n++) {
        b_Tt[n] = Tt[n] / 2.0;
      }

      d_diag(b_Tt, dv11);
      e_bsxfun(y_data, y_size, dv11, xy_subset_data, xy_subset_size);

      /* % *** Edge of sea *** */
      getOptimalLineImage_constrained(xy_subset_data, xy_subset_size,
        xy_subset_data, xy_subset_size, (double)P_edge->size[0] * 0.3, a, b_data,
        b_size);
      pts[0] = 0.0;
      pts[1] = -(a[0] * 0.0 + a[2]) / a[1];
      pts[2] = 640.0;
      pts[3] = -(a[0] * 640.0 + a[2]) / a[1];

      /* % *** Detected objects *** */
      d_T_size[0] = T_size[1];
      d_T_size[1] = T_size[0];
      ixstart = T_size[0];
      for (n = 0; n < ixstart; n++) {
        mtmp = T_size[1];
        for (vstride = 0; vstride < mtmp; vstride++) {
          b_T_data[vstride + d_T_size[0] * n] = !T_data[n + T_size[0] * vstride];
        }
      }

      replacement_bwconncomp(b_T_data, d_T_size, CC);

      /*  These are in fact "sub-boxes" which we merge into acutal object */
      /*  detections */
      ObjectPart(CC->size[1], objs);
      counter = 0.0;
      for (k = 0; k < CC->size[1]; k++) {
        b_ObjectPart(b_Tt, &xmin, obj_features, obj_uncertainty_score);

        /*     %% Bounding box */
        nxin = CC->data[k].pixel_idx.size[0];
        j = CC->data[k].pixel_idx.size[1];
        ixstart = CC->data[k].pixel_idx.size[0] * CC->data[k].pixel_idx.size[1];
        for (n = 0; n < ixstart; n++) {
          idx_data[n] = (int)CC->data[k].pixel_idx.data[n];
        }

        ixstart = nxin * j;
        for (n = 0; n < ixstart; n++) {
          idx_data[n]--;
        }

        ixstart = nxin * j;
        for (n = 0; n < ixstart; n++) {
          vk_data[n] = div_s32(idx_data[n], (int)size_obj[0]);
        }

        ixstart = nxin * j;
        for (n = 0; n < ixstart; n++) {
          idx_data[n] -= vk_data[n] * (int)size_obj[0];
        }

        ixstart = nxin * j;
        for (n = 0; n < ixstart; n++) {
          c_tmp_data[n] = idx_data[n] + 1;
        }

        ixstart = nxin * j;
        for (n = 0; n < ixstart; n++) {
          x_data[n] = vk_data[n] + 1;
        }

        iy = nxin * j;
        b_mtmp = x_data[0];
        if ((nxin * j > 1) && (1 < nxin * j)) {
          for (ix = 1; ix + 1 <= iy; ix++) {
            if (x_data[ix] < b_mtmp) {
              b_mtmp = x_data[ix];
            }
          }
        }

        k0 = nxin * j;
        mtmp = (int)c_tmp_data[0];
        if ((nxin * j > 1) && (1 < nxin * j)) {
          for (ix = 1; ix + 1 <= k0; ix++) {
            if ((int)c_tmp_data[ix] < mtmp) {
              mtmp = (int)c_tmp_data[ix];
            }
          }
        }

        iy = nxin * j;
        vstride = x_data[0];
        if ((nxin * j > 1) && (1 < nxin * j)) {
          for (ix = 1; ix + 1 <= iy; ix++) {
            if (x_data[ix] > vstride) {
              vstride = x_data[ix];
            }
          }
        }

        k0 = nxin * j;
        iy = (int)c_tmp_data[0];
        if ((nxin * j > 1) && (1 < nxin * j)) {
          for (ix = 1; ix + 1 <= k0; ix++) {
            if ((int)c_tmp_data[ix] > iy) {
              iy = (int)c_tmp_data[ix];
            }
          }
        }

        /*  Rescale bounding box */
        width = ((double)vstride - ((double)b_mtmp - 1.0)) * Tt[0];
        height = ((double)iy - ((double)mtmp - 1.0)) * Tt[3];
        b_Tt[0] = ((double)b_mtmp - 1.0) * Tt[0];
        b_Tt[1] = ((double)mtmp - 1.0) * Tt[3];
        b_Tt[2] = width;
        b_Tt[3] = height;

        /*  Area */
        /*  Boundary */
        k0 = nxin * j;
        b_mtmp = (int)c_tmp_data[0];
        itmp = 0;
        if ((nxin * j > 1) && (1 < nxin * j)) {
          for (ix = 2; ix <= k0; ix++) {
            if ((int)c_tmp_data[ix - 1] < b_mtmp) {
              b_mtmp = (int)c_tmp_data[ix - 1];
              itmp = ix - 1;
            }
          }
        }

        xmin = (double)x_data[itmp] * Tt[0];
        ixstart = xy_subset_size[1];
        b_xy_subset_size[0] = 1;
        b_xy_subset_size[1] = ixstart;
        for (n = 0; n < ixstart; n++) {
          d_tmp_data[n] = xy_subset_data[xy_subset_size[0] * n] - xmin;
        }

        b_abs(d_tmp_data, b_xy_subset_size, varargin_1_data, P_edge_size);
        ixstart = 1;
        n = P_edge_size[1];
        xmin = varargin_1_data[0];
        itmp = 0;
        if (P_edge_size[1] > 1) {
          if (rtIsNaN(varargin_1_data[0])) {
            ix = 2;
            exitg2 = false;
            while ((!exitg2) && (ix <= n)) {
              ixstart = ix;
              if (!rtIsNaN(varargin_1_data[ix - 1])) {
                xmin = varargin_1_data[ix - 1];
                itmp = ix - 1;
                exitg2 = true;
              } else {
                ix++;
              }
            }
          }

          if (ixstart < P_edge_size[1]) {
            while (ixstart + 1 <= n) {
              if (varargin_1_data[ixstart] < xmin) {
                xmin = varargin_1_data[ixstart];
                itmp = ixstart;
              }

              ixstart++;
            }
          }
        }

        if (xy_subset_data[1 + xy_subset_size[0] * itmp] > Tt[3] * (double)
            b_mtmp) {
        } else {
          /*     %% Add to the list */
          for (n = 0; n < 4; n++) {
            expl_temp.bounding_box[n] = b_Tt[n];
          }

          expl_temp.area = width * height;
          for (iy = 0; iy < 6; iy++) {
            expl_temp.features[iy] = obj_features[iy];
          }

          for (n = 0; n < 2; n++) {
            expl_temp.uncertainty_score[n] = obj_uncertainty_score[n];
          }

          objs->data[(int)(counter + 1.0) - 1] = expl_temp;
          counter++;
        }
      }

      n = objs->size[0];
      vstride = idx->size[0] * idx->size[1];
      idx->size[0] = 1;
      idx->size[1] = (int)((double)n - (counter + 1.0)) + 1;
      emxEnsureCapacity((emxArray__common *)idx, vstride, (int)sizeof(double));
      ixstart = (int)((double)n - (counter + 1.0));
      for (n = 0; n <= ixstart; n++) {
        idx->data[idx->size[0] * n] = (counter + 1.0) + (double)n;
      }

      nxin = objs->size[0] - 1;
      if (idx->size[1] == 1) {
        for (k = (int)idx->data[0]; k <= nxin; k++) {
          objs->data[k - 1] = objs->data[k];
        }

        if (objs->size[0] != 1) {
          if (1 > nxin) {
            ixstart = 0;
          } else {
            ixstart = nxin;
          }

          n = e_objs->size[0];
          e_objs->size[0] = ixstart;
          emxEnsureCapacity((emxArray__common *)e_objs, n, (int)sizeof
                            (c_ObjectPart));
          for (n = 0; n < ixstart; n++) {
            e_objs->data[n] = objs->data[n];
          }

          n = objs->size[0];
          objs->size[0] = e_objs->size[0];
          emxEnsureCapacity((emxArray__common *)objs, n, (int)sizeof
                            (c_ObjectPart));
          ixstart = e_objs->size[0];
          for (n = 0; n < ixstart; n++) {
            objs->data[n] = e_objs->data[n];
          }
        } else {
          if (1 > nxin) {
            ixstart = -1;
          } else {
            ixstart = 0;
          }

          n = d_objs->size[0];
          d_objs->size[0] = ixstart + 1;
          emxEnsureCapacity((emxArray__common *)d_objs, n, (int)sizeof
                            (c_ObjectPart));
          n = 0;
          while (n <= ixstart) {
            d_objs->data[0] = objs->data[0];
            n = 1;
          }

          n = objs->size[0];
          objs->size[0] = d_objs->size[0];
          emxEnsureCapacity((emxArray__common *)objs, n, (int)sizeof
                            (c_ObjectPart));
          ixstart = d_objs->size[0];
          for (n = 0; n < ixstart; n++) {
            objs->data[n] = d_objs->data[n];
          }
        }
      } else {
        n = b->size[0] * b->size[1];
        b->size[0] = 1;
        emxEnsureCapacity((emxArray__common *)b, n, (int)sizeof(boolean_T));
        iy = objs->size[0];
        n = b->size[0] * b->size[1];
        b->size[1] = iy;
        emxEnsureCapacity((emxArray__common *)b, n, (int)sizeof(boolean_T));
        ixstart = objs->size[0];
        for (n = 0; n < ixstart; n++) {
          b->data[n] = false;
        }

        for (k = 1; k <= idx->size[1]; k++) {
          b->data[(int)idx->data[k - 1] - 1] = true;
        }

        n = 0;
        for (k = 1; k <= b->size[1]; k++) {
          n += b->data[k - 1];
        }

        iy = objs->size[0] - n;
        k0 = -1;
        for (k = 1; k <= nxin + 1; k++) {
          if ((k > b->size[1]) || (!b->data[k - 1])) {
            k0++;
            objs->data[k0] = objs->data[k - 1];
          }
        }

        if (objs->size[0] != 1) {
          if (1 > iy) {
            ixstart = 0;
          } else {
            ixstart = iy;
          }

          n = c_objs->size[0];
          c_objs->size[0] = ixstart;
          emxEnsureCapacity((emxArray__common *)c_objs, n, (int)sizeof
                            (c_ObjectPart));
          for (n = 0; n < ixstart; n++) {
            c_objs->data[n] = objs->data[n];
          }

          n = objs->size[0];
          objs->size[0] = c_objs->size[0];
          emxEnsureCapacity((emxArray__common *)objs, n, (int)sizeof
                            (c_ObjectPart));
          ixstart = c_objs->size[0];
          for (n = 0; n < ixstart; n++) {
            objs->data[n] = c_objs->data[n];
          }
        } else {
          if (1 > iy) {
            ixstart = -1;
          } else {
            ixstart = 0;
          }

          n = b_objs->size[0];
          b_objs->size[0] = ixstart + 1;
          emxEnsureCapacity((emxArray__common *)b_objs, n, (int)sizeof
                            (c_ObjectPart));
          n = 0;
          while (n <= ixstart) {
            b_objs->data[0] = objs->data[0];
            n = 1;
          }

          n = objs->size[0];
          objs->size[0] = b_objs->size[0];
          emxEnsureCapacity((emxArray__common *)objs, n, (int)sizeof
                            (c_ObjectPart));
          ixstart = b_objs->size[0];
          for (n = 0; n < ixstart; n++) {
            objs->data[n] = b_objs->data[n];
          }
        }
      }

      Object(r0.size);
      n = objs_out->size[0] * objs_out->size[1];
      objs_out->size[0] = 0;
      objs_out->size[1] = 1;
      emxEnsureCapacity_Object(objs_out, n);
      switch (objs->size[0]) {
       case 0:
        break;

       case 1:
        /* -------------------------------------------------------------------------- */
        for (n = 0; n < 4; n++) {
          r2.bounding_box[n] = 0.0;
        }

        r2.area = 0.0;
        n = r2.parts->size[0];
        r2.parts->size[0] = 0;
        emxEnsureCapacity((emxArray__common *)r2.parts, n, (int)sizeof
                          (c_ObjectPart));
        n = b_objs_out.size[0] * b_objs_out.size[1];
        b_objs_out.size[0] = 1;
        b_objs_out.size[1] = 1;
        b_emxEnsureCapacity_Object(b_objs_out.data, b_objs_out.size, n);
        emxCopyStruct_Object(&b_objs_out.data[0], &r2);
        for (n = 0; n < 4; n++) {
          b_objs_out.data[0].bounding_box[n] = objs->data[0].bounding_box[n];
        }

        b_objs_out.data[0].area = objs->data[0].bounding_box[2] * objs->data[0].
          bounding_box[3];
        n = b_objs_out.data[0].parts->size[0];
        b_objs_out.data[0].parts->size[0] = 1;
        emxEnsureCapacity((emxArray__common *)b_objs_out.data[0].parts, n, (int)
                          sizeof(c_ObjectPart));
        b_objs_out.data[0].parts->data[0] = objs->data[0];
        n = objs_out->size[0] * objs_out->size[1];
        objs_out->size[0] = 1;
        objs_out->size[1] = 1;
        emxEnsureCapacity_Object(objs_out, n);
        emxCopyStruct_Object(&objs_out->data[0], &b_objs_out.data[0]);
        break;

       default:
        iy = objs->size[0];
        n = bbs->size[0] * bbs->size[1];
        bbs->size[0] = iy;
        bbs->size[1] = 4;
        emxEnsureCapacity((emxArray__common *)bbs, n, (int)sizeof(double));
        ixstart = objs->size[0] << 2;
        for (n = 0; n < ixstart; n++) {
          bbs->data[n] = 0.0;
        }

        for (iy = 0; iy < objs->size[0]; iy++) {
          for (n = 0; n < 4; n++) {
            bbs->data[iy + bbs->size[0] * n] = objs->data[iy].bounding_box[n];
          }
        }

        mergeByProximity(bbs, b_bbs, selected);

        /* -------------------------------------------------------------------------- */
        iy = selected->size[0];
        n = r1->size[0];
        r1->size[0] = iy;
        c_emxEnsureCapacity_Object(r1, n);
        j = 0;
        do {
          exitg1 = 0;
          iy = selected->size[0];
          if (j < iy) {
            for (n = 0; n < 4; n++) {
              r1->data[j].bounding_box[n] = 0.0;
            }

            r1->data[j].area = 0.0;
            n = r1->data[j].parts->size[0];
            r1->data[j].parts->size[0] = 0;
            emxEnsureCapacity((emxArray__common *)r1->data[j].parts, n, (int)
                              sizeof(c_ObjectPart));
            j++;
          } else {
            exitg1 = 1;
          }
        } while (exitg1 == 0);

        for (iy = 0; iy < selected->size[0]; iy++) {
          for (n = 0; n < 4; n++) {
            r1->data[iy].bounding_box[n] = b_bbs->data[iy + b_bbs->size[0] * n];
          }

          r1->data[iy].area = b_bbs->data[iy + (b_bbs->size[0] << 1)] *
            b_bbs->data[iy + b_bbs->size[0] * 3];
          n = r1->data[iy].parts->size[0];
          r1->data[iy].parts->size[0] = selected->data[iy].idx->size[0] *
            selected->data[iy].idx->size[1];
          emxEnsureCapacity((emxArray__common *)r1->data[iy].parts, n, (int)
                            sizeof(c_ObjectPart));
          ixstart = selected->data[iy].idx->size[0] * selected->data[iy]
            .idx->size[1];
          for (n = 0; n < ixstart; n++) {
            r1->data[iy].parts->data[n] = objs->data[(int)selected->data[iy].
              idx->data[n] - 1];
          }
        }

        iy = r1->size[0];
        n = objs_out->size[0] * objs_out->size[1];
        objs_out->size[0] = iy;
        objs_out->size[1] = 1;
        emxEnsureCapacity_Object(objs_out, n);
        ixstart = r1->size[0];
        for (n = 0; n < ixstart; n++) {
          emxCopyStruct_Object(&objs_out->data[n], &r1->data[n]);
        }
        break;
      }
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1) {
    Object(r0.size);
    n = objs_out->size[0] * objs_out->size[1];
    objs_out->size[0] = 0;
    objs_out->size[1] = 1;
    emxEnsureCapacity_Object(objs_out, n);
    for (n = 0; n < 4; n++) {
      pts[n] = 0.0;
    }

    xy_subset_size[0] = 2;
    xy_subset_size[1] = 2500;
    for (n = 0; n < 5000; n++) {
      xy_subset_data[n] = 0.0;
    }

    /* xy_subset = [] ; */
  }

  emxFree_ObjectPart(&e_objs);
  emxFree_ObjectPart(&d_objs);
  emxFree_ObjectPart(&c_objs);
  emxFree_ObjectPart(&b_objs);
  emxFreeStruct_Object(&r2);
  emxFree_Object_1x1(&b_objs_out);
  emxFree_real_T(&b_bbs);
  emxFree_Object(&r1);
  emxFree_SelectedIndices(&selected);
  emxFree_real_T(&bbs);
  emxFree_boolean_T(&b);
  emxFree_real_T(&idx);
  emxFree_Object_0(&r0);
  emxFree_ObjectPart(&objs);
  emxFree_ConnectedComponent(&CC);
}

/*
 * File trailer for getEdgeAndObjectsNoScaling.c
 *
 * [EOF]
 */
