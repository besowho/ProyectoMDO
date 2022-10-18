/*
 * File: run_SSM.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "run_SSM.h"
#include "normpdf.h"
#include "mergePd.h"
#include "sum.h"
#include "bsxfun.h"
#include "ssmDetect_emxutil.h"
#include "mean.h"
#include "eml_sort.h"
#include "sqrt.h"
#include "imfilter.h"
#include "getUnknownWeightForTheFeatureModel.h"

/* Function Definitions */

/*
 * not coder-compatible but maybe more readable to a user
 * Arguments    : struct0_T *detector_state
 *                const double data[12500]
 *                emxArray_real_T *Q_sum_large
 * Return Type  : void
 */
void run_SSM(struct0_T *detector_state, const double data[12500],
             emxArray_real_T *Q_sum_large)
{
  double p_unknown;
  static double S_sum[10000];
  static double PI_i0[10000];
  int i32;
  double cont;
  static double p[10000];
  emxArray_real_T *x;
  boolean_T exitg1;
  int i;
  double d_pi[2500];
  static double b_x[10000];
  static double P_i[10000];
  int k;
  double p_B[2500];
  static double b_P_i[10000];
  static double Q_i[10000];
  double dv13[2500];
  static double dv14[10000];
  static double dv15[10000];
  static double b_p_B[10000];
  double dv16[2500];
  double dv17[2500];
  double dv18[200];
  double c_x[4];
  double alpha_i[4];
  double sum_w;
  static double w_data[12500];
  double x_mu[5];
  double b_data[25];
  double d0;
  int i33;
  double b_x_mu[25];
  double b_detector_state[5];
  struct1_T c_detector_state;
  struct1_T d_detector_state;

  /*  read the em parameters */
  p_unknown = c_getUnknownWeightForTheFeature(detector_state->colorspace,
    detector_state->em_image_size, detector_state->use_uniform_component);

  /*  maximum number of em steps */
  /* mask_size = detector_state.em_image_size; */
  /*  construct convolution kernels for the em posteriors */
  /* [H_0, H_1] = getConvolutionKernel(mask_size); */
  /*  number of components in the mixture model */
  /*  intialize mixtures */
  for (i32 = 0; i32 < 10000; i32++) {
    S_sum[i32] = detector_state->PI_i[i32];

    /*  initialize the posterior for checking stopping condition */
    PI_i0[i32] = detector_state->PI_i[i32];
  }

  /*  dbug */
  cont = detector_state->em_max_steps;

  /*  100 ; */
  i32 = Q_sum_large->size[0] * Q_sum_large->size[1] * Q_sum_large->size[2];
  Q_sum_large->size[0] = 0;
  Q_sum_large->size[1] = 0;
  Q_sum_large->size[2] = 1;
  emxEnsureCapacity((emxArray__common *)Q_sum_large, i32, (int)sizeof(double));

  /* Q_sum_temp = cat(3,zeros(50,50),zeros(50,50),zeros(50,50),zeros(50,50)); */
  /* Q_sum = Q_sum_temp; */
  memset(&p[0], 0, 10000U * sizeof(double));
  b_emxInit_real_T(&x, 3);
  exitg1 = false;
  while ((!exitg1) && (cont > 1.0)) {
    /*  get responsibilities */
    for (i = 0; i < 3; i++) {
      normpdf(data, detector_state->current_mixture[i].Mu,
              detector_state->current_mixture[i].Cov, d_pi);
      for (i32 = 0; i32 < 2500; i32++) {
        p[i + (i32 << 2)] = d_pi[i32];
      }
    }

    for (i32 = 0; i32 < 2500; i32++) {
      p[3 + (i32 << 2)] = p_unknown;
    }

    /*  for the paper: */
    for (i32 = 0; i32 < 4; i32++) {
      for (i = 0; i < 2500; i++) {
        b_x[i + 2500 * i32] = p[i32 + (i << 2)];
      }
    }

    for (k = 0; k < 10000; k++) {
      P_i[k] = S_sum[k] * b_x[k] + 2.2204460492503131E-16;
    }

    if (!detector_state->use_uniform_component) {
      for (i32 = 0; i32 < 50; i32++) {
        memset(&P_i[7500 + 50 * i32], 0, 50U * sizeof(double));
      }
    }

    /*  perform Expectation on prior and posterior */
    b_sum(P_i, d_pi);
    for (i32 = 0; i32 < 2500; i32++) {
      p_B[i32] = 1.0 / d_pi[i32];
    }

    memcpy(&b_P_i[0], &P_i[0], 10000U * sizeof(double));
    b_bsxfun(b_P_i, p_B, P_i);
    imfilter(S_sum, x);
    for (k = 0; k < 10000; k++) {
      Q_i[k] = x->data[k];
    }

    for (i32 = 0; i32 < 10000; i32++) {
      S_sum[i32] *= Q_i[i32];
    }

    b_sum(S_sum, d_pi);
    for (i32 = 0; i32 < 2500; i32++) {
      p_B[i32] = 1.0 / d_pi[i32];
    }

    imfilter(P_i, x);
    for (k = 0; k < 10000; k++) {
      Q_i[k] = x->data[k];
    }

    for (i32 = 0; i32 < 10000; i32++) {
      P_i[i32] *= Q_i[i32];
    }

    b_sum(P_i, d_pi);
    for (i32 = 0; i32 < 2500; i32++) {
      dv13[i32] = 1.0 / d_pi[i32];
    }

    b_bsxfun(P_i, dv13, dv14);
    b_imfilter(dv14, x);
    for (k = 0; k < 10000; k++) {
      Q_i[k] = x->data[k];
    }

    i32 = Q_sum_large->size[0] * Q_sum_large->size[1] * Q_sum_large->size[2];
    Q_sum_large->size[0] = 50;
    Q_sum_large->size[1] = 50;
    Q_sum_large->size[2] = 4;
    emxEnsureCapacity((emxArray__common *)Q_sum_large, i32, (int)sizeof(double));
    for (i32 = 0; i32 < 10000; i32++) {
      Q_sum_large->data[i32] = Q_i[i32];
    }

    b_bsxfun(S_sum, p_B, dv15);
    b_imfilter(dv15, x);
    for (k = 0; k < 10000; k++) {
      S_sum[k] = x->data[k];
    }

    for (i32 = 0; i32 < 10000; i32++) {
      S_sum[i32] = (Q_i[i32] + S_sum[i32]) * 0.25;
    }

    /*  */
    /*  if not using the uniform component, set to zero */
    if (!detector_state->use_uniform_component) {
      for (i32 = 0; i32 < 50; i32++) {
        memset(&S_sum[7500 + 50 * i32], 0, 50U * sizeof(double));
      }
    }

    memcpy(&b_x[0], &Q_i[0], 10000U * sizeof(double));
    for (i32 = 0; i32 < 2500; i32++) {
      for (i = 0; i < 4; i++) {
        p[i + (i32 << 2)] = b_x[i32 + 2500 * i];
      }
    }

    /*  measure the change in posterior distribution */
    c_sqrt(PI_i0);
    memcpy(&Q_i[0], &S_sum[0], 10000U * sizeof(double));
    c_sqrt(Q_i);
    for (i32 = 0; i32 < 10000; i32++) {
      b_p_B[i32] = PI_i0[i32] - Q_i[i32];
    }

    b_sum(b_p_B, dv16);
    eml_sort(dv16, d_pi);
    if (b_mean(*(double (*)[1251])&d_pi[1249]) > 0.01) {
      memcpy(&PI_i0[0], &S_sum[0], 10000U * sizeof(double));

      /*  dbug */
      /*  normalize posterior */
      c_sum(p, dv17);
      c_bsxfun(p, dv17, b_p_B);
      d_sum(S_sum, dv18);
      e_sum(dv18, c_x);
      for (k = 0; k < 4; k++) {
        alpha_i[k] = c_x[k];
      }

      /*  Maximization on Guassian parameters */
      sum_w = f_sum(alpha_i);
      for (i32 = 0; i32 < 4; i32++) {
        alpha_i[i32] /= sum_w;
      }

      /*  estimate means and covs  */
      for (k = 0; k < 3; k++) {
        for (i32 = 0; i32 < 2500; i32++) {
          d_pi[i32] = b_p_B[k + (i32 << 2)];
          p_B[i32] = b_p_B[k + (i32 << 2)];
        }

        d_bsxfun(data, d_pi, w_data);
        g_sum(w_data, x_mu);
        sum_w = h_sum(p_B);
        for (i32 = 0; i32 < 5; i32++) {
          x_mu[i32] /= sum_w;
        }

        for (i32 = 0; i32 < 2500; i32++) {
          d_pi[i32] = b_p_B[k + (i32 << 2)];
        }

        sum_w = h_sum(d_pi);

        /*  naiive update of mean and covariance */
        for (i32 = 0; i32 < 5; i32++) {
          for (i = 0; i < 5; i++) {
            d0 = 0.0;
            for (i33 = 0; i33 < 2500; i33++) {
              d0 += data[i32 + 5 * i33] * w_data[i + 5 * i33];
            }

            b_data[i32 + 5 * i] = d0 / sum_w;
          }
        }

        for (i32 = 0; i32 < 5; i32++) {
          for (i = 0; i < 5; i++) {
            b_x_mu[i32 + 5 * i] = x_mu[i32] * x_mu[i];
          }
        }

        for (i32 = 0; i32 < 5; i32++) {
          for (i = 0; i < 5; i++) {
            detector_state->current_mixture[k].Cov[i + 5 * i32] = b_data[i + 5 *
              i32] - b_x_mu[i + 5 * i32];
          }
        }

        for (i = 0; i < 5; i++) {
          detector_state->current_mixture[k].Mu[i] = x_mu[i];
        }

        detector_state->current_mixture[k].w = alpha_i[k];

        /*  update means with a static prior */
        if (detector_state->use_prior_on_mixture) {
          for (i = 0; i < 5; i++) {
            x_mu[i] = detector_state->current_mixture[k].Mu[i];
          }

          for (i = 0; i < 5; i++) {
            b_detector_state[i] = detector_state->prior_mixture[k].Mu[i];
          }

          c_detector_state = detector_state->current_mixture[k];
          d_detector_state = detector_state->prior_mixture[k];
          mergePd(x_mu, c_detector_state.Cov, b_detector_state,
                  d_detector_state.Prec, detector_state->current_mixture[k].Mu);
        }
      }

      sum_w = 0.0;
      for (i = 0; i < 3; i++) {
        sum_w += detector_state->current_mixture[i].w;
      }

      for (k = 0; k < 3; k++) {
        detector_state->current_mixture[k].w /= sum_w;
      }

      cont--;
    } else {
      exitg1 = true;
    }
  }

  emxFree_real_T(&x);
  for (k = 0; k < 10000; k++) {
    detector_state->PI_i[k] = Q_sum_large->data[k];
  }
}

/*
 * File trailer for run_SSM.c
 *
 * [EOF]
 */
