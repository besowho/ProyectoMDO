/*
 * File: getUnknownWeightForTheFeatureModel.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "getUnknownWeightForTheFeatureModel.h"

/* Function Definitions */

/*
 * Arguments    : Colorspace type_colorspace
 *                const double sizeMask[2]
 *                boolean_T use_uniform_component
 * Return Type  : double
 */
double c_getUnknownWeightForTheFeature(Colorspace type_colorspace, const double
  sizeMask[2], boolean_T use_uniform_component)
{
  double p_unknown;
  p_unknown = 0.0;

  /* zato da je output predvidljiv */
  if (!use_uniform_component) {
  } else {
    switch (type_colorspace) {
     case hsv:
      p_unknown = 1.0 / (sizeMask[0] * sizeMask[1]);
      break;

     case rgb:
      p_unknown = 1.0 / (sizeMask[0] * sizeMask[1] * 1.6581375E+7) * 0.001;
      break;

     case ycrcb:
      p_unknown = 0.001 / (sizeMask[0] * sizeMask[1] * 1.0988544E+7);
      break;

     case lab:
      /*  */
      p_unknown = 0.01 / (sizeMask[0] * sizeMask[1] * 1.6581375E+7);
      break;

     case ycrs:
      /*  */
      p_unknown = 0.01 / (sizeMask[0] * sizeMask[1] * 49056.0);
      break;
    }
  }

  return p_unknown;
}

/*
 * File trailer for getUnknownWeightForTheFeatureModel.c
 *
 * [EOF]
 */
