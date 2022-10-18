/*
 * File: ssmDetect.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "cov.h"
#include "ssmDetect_emxutil.h"
#include "mean.h"
#include "getEdgeAndObjectsNoScaling.h"
#include "run_SSM.h"
#include "loadPriorModelFromDisk.h"

/* Function Definitions */

/*
 * Se agrega sel_xy y objects como campos a detector_state
 * Size of sel_xy: 2x200 double
 * Size of objects: 20x1 struct
 * Crear estructura detector_state
 * detector_state = DetectorState;
 * detector_state.is_initialized = isInitialized;
 * Arguments    : struct0_T *detector_state
 * Return Type  : void
 */
void ssmDetect(struct0_T *detector_state)
{
  int i31;
  int i;
  boolean_T initialize_detector;
  double em_image_size[2];
  boolean_T expl_temp;
  struct1_T model_prior_mixture[3];
  Colorspace b_expl_temp;
  signed char x[2500];
  int iy;
  int k;
  signed char y[2500];
  int isrc;
  signed char b_x[2500];
  signed char b_y[2500];
  int idest;
  signed char outsz[3];
  static double b[7500];
  int iwork[3];
  int inc[3];
  static const signed char iv9[3] = { 1, 0, 2 };

  int32_T exitg1;
  static double c_y[7500];
  static double dataEM[12500];
  emxArray_real_T *dat;
  emxArray_real_T *b_dat;
  static const short iv10[4] = { 0, 750, 1250, 2500 };

  double a[10];
  static const short vertical_ratio[6] = { 0, 500, 1500, 500, 1000, 2500 };

  double tmp_mu[5];
  double tmp_cov[25];
  double Mu1[5];
  double Cov1[25];
  double multi[10];
  double sum_w;
  double new_mu[5];
  double b_Cov1[25];
  emxArray_real_T *Q_sum_large;
  emxArray_Object *objectsTemp;
  int masked_sea_size[2];
  boolean_T masked_sea_data[2500];
  int sel_xyTemp_size[2];
  static double sel_xyTemp_data[5000];
  double unusedU0[4];

  /* Inicializar sel_xy y objects */
  for (i31 = 0; i31 < 400; i31++) {
    detector_state->sel_xy[i31] = 0.0;
  }

  for (i = 0; i < 20; i++) {
    for (i31 = 0; i31 < 4; i31++) {
      detector_state->objects[i].bounding_box[i31] = 0.0;
    }

    detector_state->objects[i].area = 0.0;

    /* detector_state.objects(i).parts.bounding_box = zeros(1,4); */
    /* detector_state.objects(i).parts.area = 0; */
    /* detector_state.objects(i).parts.features = zeros(6,1); */
    /* detector_state.objects(i).parts.uncertainty_score = zeros(1,2); */
  }

  detector_state->num_points = 0.0;
  detector_state->num_objects = 0.0;

  /* % Initialize detector state, if necessary */
  /*  Initialize detector on first pass */
  initialize_detector = !detector_state->is_initialized;
  if (initialize_detector) {
    /*  Create detector state */
    detector_state->is_initialized = true;

    /*  Load prior */
    loadPriorModelFromDisk(detector_state->colorspace, &b_expl_temp,
      model_prior_mixture, &expl_temp, em_image_size);

    /* assert(isequal(em_image_size, [ 50, 50 ]), 'Change this if EM image size is not 50x50!'); */
    /* assert(isequal(em_image_size, [ 50, 50 ]), 'Change this if EM image size is not 50x50!'); */
    for (i = 0; i < 3; i++) {
      detector_state->prior_mixture[i] = model_prior_mixture[i];
    }

    /*  Set EM image size (stored with prior model) */
    for (i31 = 0; i31 < 2; i31++) {
      detector_state->em_image_size[i31] = em_image_size[i31];
    }

    /*  Initialize spatial data - this in fact describes position of each */
    /*  pixel... we use ndgrid instead of meshgrid because it returns correct */
    /*  shape of the array */
    iy = -1;
    for (i = 0; i < 50; i++) {
      for (k = 0; k < 50; k++) {
        iy++;
        x[iy] = (signed char)(1 + k);
      }
    }

    iy = -1;
    for (k = 0; k < 50; k++) {
      for (isrc = 0; isrc < 50; isrc++) {
        iy++;
        y[iy] = (signed char)(1 + k);
      }
    }

    /* [ x, y ] = ndgrid(1:em_image_size(2), 1:em_image_size(1)); */
    for (i31 = 0; i31 < 50; i31++) {
      for (idest = 0; idest < 50; idest++) {
        b_x[idest + 50 * i31] = x[idest + 50 * i31];
        b_y[idest + 50 * i31] = y[idest + 50 * i31];
      }
    }

    for (i31 = 0; i31 < 2500; i31++) {
      detector_state->spatial_data[i31 << 1] = b_x[i31];
      detector_state->spatial_data[1 + (i31 << 1)] = b_y[i31];
    }

    /* detector_state.spatial_data = [ x(1:50, 1:50)'; y(1:50, 1:50)' ];  */
    /* temp1 = [ x(:)'; y(:)' ]; */
    /* detector_state.spatial_data = temp1; */
  }

  /* En este punto se proporciona la imagen de 50x50 en formato ycrcb */
  /*  %% Prepare data for EM */
  /*  % If first dimension of the image appear to be channels, assume */
  /*  % OpenCV-compatible layout: interleaved BGR in row-major order. Otherwise, */
  /*  % assume we have Matlab-compatible layout */
  /*  if size(Im_in, 1) == 3, */
  /*      % Deinterleave image, transpose and switch BGR to RGB */
  /*      B = squeeze(Im_in(1:3:end,:,:)); */
  /*      G = squeeze(Im_in(2:3:end,:,:)); */
  /*      R = squeeze(Im_in(3:3:end,:,:)); */
  /*       */
  /*      Im = zeros(size(Im_in, 3), size(Im_in, 2), size(Im_in, 1), 'uint8'); */
  /*       */
  /*      Im(:,:,1) = R(:,:,1)'; */
  /*      Im(:,:,2) = G(:,:,1)'; */
  /*      Im(:,:,3) = B(:,:,1)'; */
  /*       */
  /*      image_transposed = true; */
  /*  else */
  /*      Im = Im_in; */
  /*       */
  /*      image_transposed = false; */
  /*  end */
  /*   */
  /*  % Scale the image  */
  /*  %Ax1 = imresize(Im, detector_state.em_image_size, 'bilinear'); */
  /*  Ax1 = Im; */
  /*   */
  /*  % Convert color space */
  /*  switch detector_state.colorspace, */
  /*      case Colorspace.hsv,  */
  /*            Ax = rgb2hsv(Ax1); */
  /*      case Colorspace.rgb, */
  /*          Ax = double(Ax1); */
  /*      case Colorspace.ycrcb,  */
  /*          Ax = double( rgb2ycbcr(Ax1)); */
  /*                    */
  /*      case Colorspace.lab,  */
  /*          %Ax = rgb2lab(Ax1) ; */
  /*      case Colorspace.ycrs,  */
  /*          Ahsv =  rgb2hsv(Ax1) ; */
  /*          Ax = double(rgb2ycbcr(Ax1)); */
  /*          Ax(:,:,3) = Ahsv(:,:,3) ; */
  /*      otherwise */
  /*          error('Unknown colorspace.'); */
  /*  end */
  /*  Construct the color data - transpose Matlab (column-major order,  */
  /*  deinterleaved RGB) image via permute, so that we get C-ordering */
  /*  (row-major) of data, then unroll image planes into vectors */
  outsz[0] = 50;
  outsz[1] = 50;
  outsz[2] = 3;
  for (i31 = 0; i31 < 3; i31++) {
    iwork[i31] = 1;
  }

  for (k = 0; k < 2; k++) {
    iwork[k + 1] = iwork[k] * 50;
  }

  for (i31 = 0; i31 < 3; i31++) {
    inc[i31] = iwork[iv9[i31]];
  }

  for (i31 = 0; i31 < 3; i31++) {
    iwork[i31] = 0;
  }

  idest = 0;
  do {
    isrc = 0;
    for (k = 0; k < 2; k++) {
      isrc += iwork[k + 1] * inc[k + 1];
    }

    for (k = 0; k < 50; k++) {
      b[idest] = detector_state->Im_in[isrc];
      idest++;
      isrc += inc[0];
    }

    k = 1;
    do {
      exitg1 = 0;
      iwork[k]++;
      if (iwork[k] < outsz[k]) {
        exitg1 = 2;
      } else if (k + 1 == 3) {
        exitg1 = 1;
      } else {
        iwork[1] = 0;
        k = 2;
      }
    } while (exitg1 == 0);
  } while (!(exitg1 == 1));

  memcpy(&c_y[0], &b[0], 7500U * sizeof(double));

  /* dataEM = zeros(5, 2500); */
  for (i31 = 0; i31 < 2500; i31++) {
    for (idest = 0; idest < 2; idest++) {
      dataEM[idest + 5 * i31] = detector_state->spatial_data[idest + (i31 << 1)];
    }

    for (idest = 0; idest < 3; idest++) {
      dataEM[(idest + 5 * i31) + 2] = c_y[i31 + 2500 * idest];
    }
  }

  /* Im_size = size(Im); */
  /* Im_size = Im_size([1 2]); */
  /* La imagen original debe ser de 640x480 pixeles */
  /* % initialize the EM if no prior mixture exists */
  emxInit_real_T(&dat, 2);
  if (initialize_detector) {
    emxInit_real_T(&b_dat, 2);
    for (k = 0; k < 3; k++) {
      i31 = iv10[k] + 1;
      if (i31 > iv10[1 + k]) {
        i31 = 0;
        idest = 0;
      } else {
        i31--;
        idest = iv10[1 + k];
      }

      isrc = dat->size[0] * dat->size[1];
      dat->size[0] = 5;
      dat->size[1] = idest - i31;
      emxEnsureCapacity((emxArray__common *)dat, isrc, (int)sizeof(double));
      iy = idest - i31;
      for (idest = 0; idest < iy; idest++) {
        for (isrc = 0; isrc < 5; isrc++) {
          dat->data[isrc + dat->size[0] * idest] = dataEM[isrc + 5 * (i31 +
            idest)];
        }
      }

      mean(dat, detector_state->current_mixture[k].Mu);
      i31 = b_dat->size[0] * b_dat->size[1];
      b_dat->size[0] = dat->size[1];
      b_dat->size[1] = 5;
      emxEnsureCapacity((emxArray__common *)b_dat, i31, (int)sizeof(double));
      for (i31 = 0; i31 < 5; i31++) {
        iy = dat->size[1];
        for (idest = 0; idest < iy; idest++) {
          b_dat->data[idest + b_dat->size[0] * i31] = dat->data[i31 + dat->size
            [0] * idest];
        }
      }

      cov(b_dat, detector_state->current_mixture[k].Cov);
      detector_state->current_mixture[k].w = 0.33333333333333331;
    }

    emxFree_real_T(&b_dat);
  } else {
    initialize_detector = false;
    expl_temp = true;
    if (!(detector_state->colorspace == hsv)) {
      expl_temp = false;
    }

    if (!expl_temp) {
    } else {
      initialize_detector = true;
    }

    if (!initialize_detector) {
      /*  mix existing initial distribution with the current initial pdf */
      emxInit_real_T(&b_dat, 2);
      for (k = 0; k < 3; k++) {
        i31 = vertical_ratio[k] + 1;
        if (i31 > vertical_ratio[3 + k]) {
          i31 = 0;
          idest = 0;
        } else {
          i31--;
          idest = vertical_ratio[3 + k];
        }

        isrc = dat->size[0] * dat->size[1];
        dat->size[0] = 5;
        dat->size[1] = idest - i31;
        emxEnsureCapacity((emxArray__common *)dat, isrc, (int)sizeof(double));
        iy = idest - i31;
        for (idest = 0; idest < iy; idest++) {
          for (isrc = 0; isrc < 5; isrc++) {
            dat->data[isrc + dat->size[0] * idest] = dataEM[isrc + 5 * (i31 +
              idest)];
          }
        }

        mean(dat, tmp_mu);
        i31 = b_dat->size[0] * b_dat->size[1];
        b_dat->size[0] = dat->size[1];
        b_dat->size[1] = 5;
        emxEnsureCapacity((emxArray__common *)b_dat, i31, (int)sizeof(double));
        for (i31 = 0; i31 < 5; i31++) {
          iy = dat->size[1];
          for (idest = 0; idest < iy; idest++) {
            b_dat->data[idest + b_dat->size[0] * i31] = dat->data[i31 +
              dat->size[0] * idest];
          }
        }

        cov(b_dat, tmp_cov);
        for (i = 0; i < 5; i++) {
          Mu1[i] = detector_state->current_mixture[k].Mu[i];
        }

        for (i31 = 0; i31 < 25; i31++) {
          Cov1[i31] = detector_state->current_mixture[k].Cov[i31];
        }

        /* % */
        /*  Originally a part of: Maggot (developed within EU project CogX) */
        /*  Author: Matej Kristan, 2009 (matej.kristan@fri.uni-lj.si; http://vicos.fri.uni-lj.si/matejk/) */
        /*  Last revised: 2009 */
        /* % */
        /*  % new_mu =  sum(bsxfun(@times,Mu, w),2) ; */
        /* new_mu =  sum(bsxfun(@times,[Mu1,Mu2], w),2) ; */
        for (i31 = 0; i31 < 5; i31++) {
          a[i31] = detector_state->current_mixture[k].Mu[i31];
        }

        for (i31 = 0; i31 < 5; i31++) {
          a[5 + i31] = tmp_mu[i31];
        }

        for (idest = 0; idest < 2; idest++) {
          sum_w = 0.6 + -0.19999999999999996 * (double)idest;
          for (i31 = 0; i31 < 5; i31++) {
            multi[i31 + 5 * idest] = a[i31 + 5 * idest] * sum_w;
          }
        }

        iy = -1;
        idest = 4;
        for (isrc = 0; isrc < 5; isrc++) {
          idest++;
          iy++;
          new_mu[iy] = multi[idest - 5] + multi[idest];
        }

        /*  %n = size(new_mu,1) ; */
        /*  %     new_Cov = zeros(n,n) ; */
        /*  %    if n==1 */
        /*  %         new_Cov = sum(w.*(cell2mat(Cov) + Mu.*Mu)) ; */
        /*  %     else */
        /*  %         for j=1:length(w) */
        /*  %              */
        /*  %             new_Cov = new_Cov + w(j)*( Cov{j} + Mu(:,j)*Mu(:,j)') ; */
        /*  %         end */
        /*  %     end */
        /*  %     new_Cov = new_Cov - new_mu*new_mu' ; */
        for (i = 0; i < 5; i++) {
          detector_state->current_mixture[k].Mu[i] = 0.0;
        }

        for (i31 = 0; i31 < 25; i31++) {
          detector_state->current_mixture[k].Cov[i31] = 0.0;
        }

        detector_state->current_mixture[k].w = 0.0;
        for (i31 = 0; i31 < 25; i31++) {
          detector_state->current_mixture[k].Prec[i31] = 0.0;
        }

        for (i = 0; i < 5; i++) {
          detector_state->current_mixture[k].Mu[i] = 0.6 * Mu1[i] + 0.4 *
            tmp_mu[i];
        }

        for (i31 = 0; i31 < 5; i31++) {
          for (idest = 0; idest < 5; idest++) {
            b_Cov1[i31 + 5 * idest] = Cov1[i31 + 5 * idest] + Mu1[i31] *
              Mu1[idest];
          }
        }

        for (i31 = 0; i31 < 5; i31++) {
          for (idest = 0; idest < 5; idest++) {
            Cov1[i31 + 5 * idest] = tmp_cov[i31 + 5 * idest] + tmp_mu[i31] *
              tmp_mu[idest];
          }
        }

        for (i31 = 0; i31 < 5; i31++) {
          for (idest = 0; idest < 5; idest++) {
            detector_state->current_mixture[k].Cov[i31 + 5 * idest] = (0.6 *
              b_Cov1[i31 + 5 * idest] + 0.4 * Cov1[i31 + 5 * idest]) -
              new_mu[i31] * new_mu[idest];
          }
        }

        detector_state->current_mixture[k].w = 1.0;
      }

      emxFree_real_T(&b_dat);
      sum_w = 0.0;
      for (k = 0; k < 3; k++) {
        sum_w += detector_state->current_mixture[k].w;
      }

      for (k = 0; k < 3; k++) {
        detector_state->current_mixture[k].w /= sum_w;
      }
    }
  }

  emxFree_real_T(&dat);
  b_emxInit_real_T(&Q_sum_large, 3);
  b_emxInit_Object(&objectsTemp, 2);

  /* tic ; */
  /* % The SSM: EM iterations */
  run_SSM(detector_state, dataEM, Q_sum_large);

  /* t = toc ; */
  /* fprintf('%3.0f miliseconds required for segmentation.\n', t*1000) ; */
  /* % Retrieve objects and sea edge */
  getEdgeAndObjectsNoScaling(Q_sum_large, objectsTemp, unusedU0, sel_xyTemp_data,
    sel_xyTemp_size, masked_sea_data, masked_sea_size);
  idest = sel_xyTemp_size[1];
  isrc = objectsTemp->size[0];
  emxFree_real_T(&Q_sum_large);
  if (sel_xyTemp_size[1] > 200) {
    idest = 200;
  }

  if (objectsTemp->size[0] > 20) {
    isrc = 20;
  }

  for (i = 0; i < idest; i++) {
    for (i31 = 0; i31 < 2; i31++) {
      detector_state->sel_xy[i31 + (i << 1)] = sel_xyTemp_data[i31 +
        sel_xyTemp_size[0] * i];
    }
  }

  if (isrc > 0) {
    for (i = 0; i < isrc; i++) {
      for (i31 = 0; i31 < 4; i31++) {
        detector_state->objects[i].bounding_box[i31] = objectsTemp->data[i].
          bounding_box[i31];
      }

      detector_state->objects[i].area = objectsTemp->data[i].area;

      /* detector_state.objects(i).parts.bounding_box = objectsTemp(i).parts.bounding_box; */
      /* detector_state.objects(i).parts.area = objectsTemp(i).parts.area; */
      /* detector_state.objects(i).parts.features = objectsTemp(i).parts.features; */
      /* detector_state.objects(i).parts.uncertainty_score = objectsTemp(i).parts.uncertainty_score; */
    }
  }

  emxFree_Object(&objectsTemp);
  detector_state->num_points = idest;
  detector_state->num_objects = isrc;

  /*  If we had to transpose the input image, we need to transpose masked_sea */
  /*  and uncertainty_measures.uncertainty_map */
  /*  if image_transposed, */
  /*      masked_sea = masked_sea';  */
  /*  end */
  /* -------------------------------------------------------------------------- */
  /*  function [ detector_state, Q_sum_large ] = run_SSM(detector_state, data) */
  /*  % not coder-compatible but maybe more readable to a user */
  /*   */
  /*  % read the em parameters */
  /*  p_unknown = getUnknownWeightForTheFeatureModel(detector_state.colorspace, detector_state.em_image_size, detector_state.use_uniform_component); */
  /*   */
  /*  maxEMsteps = detector_state.em_max_steps; % maximum number of em steps */
  /*  mask_size = detector_state.em_image_size; */
  /*   */
  /*  % construct convolution kernels for the em posteriors */
  /*  [H_0, H_1] = getConvolutionKernel(mask_size) ; */
  /*   */
  /*  % number of components in the mixture model */
  /*  mixture_size = length(detector_state.current_mixture) ; */
  /*   */
  /*  % intialize mixtures */
  /*  if isempty(detector_state.PI_i) */
  /*      PI_i = ones(mask_size(2), mask_size(1), mixture_size+1) /(mixture_size+1) ; */
  /*      PI_i(:,:,1:3) = 1/mixture_size - p_unknown/mixture_size ; */
  /*      PI_i(:,:,4) = p_unknown ; */
  /*  else */
  /*      PI_i = detector_state.PI_i ; */
  /*  end */
  /*   */
  /*  % initialize the posterior for checking stopping condition */
  /*  PI_i0 = PI_i ;% dbug */
  /*   */
  /*  cont = maxEMsteps ; % 100 ; */
  /*   */
  /*  Q_sum=[]; */
  /*  p = zeros(mixture_size+1,size(data,2)) ; */
  /*   while cont > 1 */
  /*      % get responsibilities */
  /*      for i = 1 : mixture_size */
  /*          p(i,:) = normpdf(data,detector_state.current_mixture(i).Mu,[], detector_state.current_mixture(i).Cov) ; */
  /*      end */
  /*      p(mixture_size+1,:) = p_unknown ; */
  /*        */
  /*      % for the paper: */
  /*      P_i = PI_i.*reshape(p', mask_size(2),mask_size(1), mixture_size+1) + eps; */
  /*      if ~detector_state.use_uniform_component, */
  /*          P_i(:,:,mixture_size+1) = 0 ; */
  /*      end */
  /*       */
  /*      % perform Expectation on prior and posterior */
  /*      P_i = bsxfun(@times, P_i, 1./sum(P_i,3)) ;    */
  /*      S_i = PI_i.*imfilter(PI_i , H_0, 'replicate')  ; S_i = bsxfun(@times, S_i, 1./sum(S_i,3)) ;   */
  /*      Q_i = P_i.*imfilter(P_i , H_0, 'replicate')  ; Q_i = bsxfun(@times, Q_i, 1./sum(Q_i,3)) ; */
  /*      Q_sum = imfilter(Q_i , H_1, 'replicate') ; */
  /*      S_sum = imfilter(S_i , H_1, 'replicate') ; */
  /*      PI_i = (Q_sum + S_sum)*0.25 ; % */
  /*    */
  /*      % if not using the uniform component, set to zero */
  /*      if ~detector_state.use_uniform_component, */
  /*          PI_i(:,:,mixture_size+1) = 0 ; */
  /*      end */
  /*      */
  /*      p = reshape(Q_sum,mask_size(2)*mask_size(1),mixture_size+1)' ; */
  /*       */
  /*      % measure the change in posterior distribution */
  /*      d_pi = sum((sqrt(PI_i0)-sqrt(PI_i)),3) ; */
  /*      d_pi = sort(d_pi(:)) ;  Loglik_new = mean(d_pi(round(length(d_pi))/2:end)) ; */
  /*      if Loglik_new > 0.01  */
  /*          PI_i0 = PI_i ;% dbug */
  /*      else */
  /*          break ; */
  /*      end */
  /*      lp = sum(p,1) ; */
  /*       */
  /*      % normalize posterior */
  /*      p = bsxfun(@rdivide, p, lp) ; */
  /*      alpha_i = reshape(sum(sum(PI_i,1),2), 1, mixture_size+1 ) ; */
  /*   */
  /*      % Maximization on Guassian parameters */
  /*      alpha_i = alpha_i / sum(alpha_i) ; */
  /*      % estimate means and covs  */
  /*      for k = 1 : mixture_size   */
  /*          w_data = bsxfun(@times, data, p(k,:)) ; */
  /*          x_mu = sum( w_data, 2 ) / sum(p(k,:)) ; */
  /*          x_2_mu = data*w_data' / sum(p(k,:)) ;                 */
  /*          c = x_2_mu - x_mu*x_mu' ;                 */
  /*          % naiive update of mean and covariance */
  /*          detector_state.current_mixture(k).Cov = c ;  */
  /*          detector_state.current_mixture(k).Mu = x_mu ; */
  /*          detector_state.current_mixture(k).w = alpha_i(k) ;  */
  /*   */
  /*          % update means with a static prior */
  /*          if detector_state.use_prior_on_mixture */
  /*              i_c_d = k ; i_c_0 = k ; */
  /*              detector_state.current_mixture(i_c_d).Mu = mergePd( detector_state.current_mixture(i_c_d).Mu, detector_state.current_mixture(i_c_d).Cov , ... */
  /*                  detector_state.prior_mixture(i_c_0).Mu,... */
  /*                  detector_state.prior_mixture(i_c_0).Prec) ;  */
  /*          end */
  /*      end      */
  /*        */
  /*      sum_w=0; */
  /*      for i=1:numel(detector_state.current_mixture), */
  /*          sum_w=sum_w+detector_state.current_mixture(i).w; */
  /*      end; */
  /*    */
  /*      for k=1:mixture_size, */
  /*          detector_state.current_mixture(k).w = detector_state.current_mixture(k).w/ sum_w ; */
  /*      end */
  /*   */
  /*       cont = cont - 1 ; */
  /*   end */
  /*   */
  /*  Q_sum_large = Q_sum ; */
  /*  detector_state.PI_i = Q_sum ;  */
  /*  end */
  /* ------------------------------------------------------------------------- */
  /*  function y = normpdf(x,mu,~,sigma) */
  /*      [U,S,~] = svd(sigma) ; */
  /*      s = diag(S) ; s(s<eps) = 1 ; S = diag(s) ; */
  /*      A = bsxfun(@minus, x, mu)' * (U*diag(1./diag(sqrt(S)))) ; */
  /*       */
  /*      y = exp(-0.5*sum(A .* A, 2)) / (sqrt(2*pi) .* prod(diag(S))) ; */
  /*  end */
  /* ------------------------------------------------------------------------- */
  /*  function Mu = mergePd( Mu_d, C_d, Mu_0, iC0 ) */
  /*   #codegen  */
  /*    */
  /*  d = size(C_d,1) ; */
  /*  approximately robust */
  /*  scl = 1e-10;  */
  /*  tmpB=diag(C_d); */
  /*  tmpC= C_d+eye(d)*mean(tmpB(:))*scl; */
  /*   */
  /*  Mu = (inv(tmpC) + iC0)\(tmpC\Mu_d + iC0*Mu_0) ; */
  /*  end */
  /* -------------------------------------------------------------------------- */
  /*  function [H_0, H_1] = getConvolutionKernel (sizeMask) */
  /*  %#codegen */
  /*   */
  /*  scale_filter = 0.1 ; */
  /*   */
  /*  %to je zaradi tega, ker coder ne podpira variablinih argumentov pri */
  /*  %fspecial */
  /*  assert(isequal(sizeMask,[50,50]),'Slika mora biti 50x50.') */
  /*   */
  /*  hsize = ceil(0.2*( sizeMask(2)*scale_filter -1)) ; */
  /*  % H_0 = replacement_fspecial('gaussian', hsize*2+1, hsize/1.5) ; */
  /*  H_0 = fspecial('gaussian', hsize*2+1, hsize/1.5) ; */
  /*   */
  /*  centr = (size(H_0,1)-1)/2 + 1 ; */
  /*  H_0(centr, centr) = 0 ; H_0 = H_0 / sum(H_0(:)) ; */
  /*  H_1 = H_0 ; */
  /*  H_1(centr, centr) = 1 ; */
  /*   */
  /*  end */
  /* -------------------------------------------------------------------------- */
  /*  function p_unknown = getUnknownWeightForTheFeatureModel(type_colorspace, sizeMask, use_uniform_component)  */
  /*   %#codegen */
  /*    */
  /*  p_unknown=0;  %zato da je output predvidljiv */
  /*    */
  /*  if ~use_uniform_component */
  /*      return ; */
  /*  end */
  /*   */
  /*  switch(type_colorspace) */
  /*      case Colorspace.hsv */
  /*          p_unknown = 1/prod(sizeMask) ; 1e-5 ; 0.001 ; */
  /*      case Colorspace.rgb */
  /*          p_unknown = 1/(prod(sizeMask) *255^3) *0.001; 1e-5 ; 0.001 ; */
  /*      case Colorspace.ycrcb */
  /*          p_unknown = 0.001*1/(prod(sizeMask) *10988544) ; % */
  /*      case Colorspace.lab */
  /*          p_unknown =10^(-2) *  1 / ( prod(sizeMask) *255^3  ) ;% */
  /*      case Colorspace.ycrs */
  /*          p_unknown = 0.01*1/(prod(sizeMask) *49056) ;  */
  /*      otherwise */
  /*          error('Invalid type colorspace.');   */
  /*  end */
  /*  end */
  /* -------------------------------------------------------------------------- */
  /*  function [ objs_out, pts, xy_subset, masked_Sea ] = getEdgeAndObjectsNoScaling (P_edge , Im_size ) */
  /*  %#codegen */
  /*   */
  /*  size_edge = Im_size ; */
  /*  size_obj = size(P_edge(:,:,3)) ; */
  /*  size_obj = size_obj([2,1]) ; */
  /*  scl = size_edge./size_obj ; */
  /*  Tt = diag(scl([2,1])) ; */
  /*    */
  /*  %% *** Sea edge and its uncertainty score *** */
  /*  [~,T] = max(P_edge,[],3) ; T = (T==3) ; */
  /*   */
  /*  T = bwmorph(T,'diag') ; */
  /*  T = extractTheLargestRegion(T) ; */
  /*  T = ~bwmorph(~T,'clean') ; */
  /*  masked_Sea = T' ; */
  /*   */
  /*  dT = [ zeros(size(T,1),1), diff(T')' ] ~=0 ; */
  /*  dT2 = [ zeros(1,size(T,2)); diff(T) ] ~=0 ; */
  /*  dT = dT | dT2 ; */
  /*   */
  /*  % try */
  /*  if (sum(T(:)) ~= numel(T)) && (sum(dT(:)) ~= 0), */
  /*      [ largest_curve, ~ ] = extractTheLargestCurve(dT') ; */
  /*      data = bsxfun(@minus, Tt*largest_curve', diag(Tt/2)) ; */
  /*  else */
  /*      objs_out = Object(0); */
  /*      pts = [ 0 0 0 0 ]; */
  /*      xy_subset = [] ; */
  /*      return; */
  /*  end */
  /*    */
  /*   */
  /*  %% *** Edge of sea *** */
  /*  delta = size(P_edge,1)*0.3 ; */
  /*  [a, ~] = getOptimalLineImage_constrained(data, [], data, delta) ; */
  /*  xy_subset = data ; */
  /*   */
  /*  x0 = 0; */
  /*  y0 =  -(a(1)*x0 + a(3))/a(2); */
  /*  x1 = Im_size(2) ; */
  /*  y1 = -(a(1)*x1 + a(3))/a(2); */
  /*   */
  /*  pts = [ x0, y0, x1, y1 ]; */
  /*   */
  /*  I = ~T' ; */
  /*    */
  /*  %% *** Detected objects *** */
  /*  CC = replacement_bwconncomp(I,8) ; */
  /*   */
  /*  % These are in fact "sub-boxes" which we merge into acutal object */
  /*  % detections */
  /*  objs = ObjectPart(numel(CC)); */
  /*   */
  /*  counter = 0; */
  /*  for k = 1:numel(CC), */
  /*      pixels = CC(k).pixel_idx; */
  /*       */
  /*      obj = ObjectPart(1); */
  /*       */
  /*      %% Bounding box */
  /*      [ y, x ] = ind2sub(size_obj, pixels); */
  /*      xmin = min(x(:)); */
  /*      ymin = min(y(:)); */
  /*      xmax = max(x(:)); */
  /*      ymax = max(y(:)); */
  /*       */
  /*      xmin = xmin-1; */
  /*      ymin = ymin-1; */
  /*      width = xmax-xmin; */
  /*      height = ymax-ymin; */
  /*       */
  /*      % Rescale bounding box */
  /*      xmin = xmin*Tt(1); */
  /*      ymin = ymin*Tt(4); */
  /*      width = width*Tt(1); */
  /*      height = height*Tt(4); */
  /*       */
  /*      obj.bounding_box = [xmin, ymin, width, height]; */
  /*       */
  /*      % Area */
  /*      obj.area = width*height; */
  /*       */
  /*      % Boundary */
  /*      [ymin,loc]=min(y(:)); */
  /*      xmin = x(loc)*Tt(1); */
  /*      ymin = Tt(4)*ymin; */
  /*       */
  /*      [~,loc] = min(abs(xy_subset(1,:)-xmin)) ; */
  /*      boundary = xy_subset(:,loc) ; */
  /*       */
  /*      if boundary(2) > ymin */
  /*          continue ; */
  /*      end */
  /*     */
  /*      %% Add to the list */
  /*      objs(counter+1) = obj; */
  /*      counter = counter+1; */
  /*  end */
  /*   */
  /*  objs(counter+1:end) = [];  */
  /*   */
  /*  objs_out = suppressDetections(objs); */
  /*  end */
}

/*
 * File trailer for ssmDetect.c
 *
 * [EOF]
 */
