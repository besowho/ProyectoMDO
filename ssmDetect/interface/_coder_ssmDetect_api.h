/* 
 * File: _coder_ssmDetect_api.h 
 *  
 * MATLAB Coder version            : 2.7 
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22 
 */

#ifndef ___CODER_SSMDETECT_API_H__
#define ___CODER_SSMDETECT_API_H__
/* Include Files */ 
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Type Definitions */ 
#ifndef enum_Colorspace
#define enum_Colorspace
enum Colorspace
{
    hsv = 1,
    lab,
    rgb,
    ycrcb,
    ycrs
};
#endif /*enum_Colorspace*/
#ifndef typedef_Colorspace
#define typedef_Colorspace
typedef enum Colorspace Colorspace;
#endif /*typedef_Colorspace*/
#ifndef typedef_struct1_T
#define typedef_struct1_T
typedef struct
{
    real_T Mu[5];
    real_T Cov[25];
    real_T w;
    real_T Prec[25];
} struct1_T;
#endif /*typedef_struct1_T*/
#ifndef typedef_struct2_T
#define typedef_struct2_T
typedef struct
{
    real_T bounding_box[4];
    real_T area;
} struct2_T;
#endif /*typedef_struct2_T*/
#ifndef typedef_struct0_T
#define typedef_struct0_T
typedef struct
{
    boolean_T use_prior_on_mixture;
    boolean_T use_uniform_component;
    Colorspace colorspace;
    real_T em_min_likelihood_delta;
    real_T em_max_steps;
    boolean_T is_initialized;
    struct1_T prior_mixture[3];
    struct1_T current_mixture[3];
    real_T em_image_size[2];
    real_T spatial_data[5000];
    real_T PI_i[10000];
    real_T sel_xy[400];
    real_T num_points;
    struct2_T objects[20];
    real_T num_objects;
    real_T Im_in[7500];
} struct0_T;
#endif /*typedef_struct0_T*/

/* Function Declarations */ 
extern void ssmDetect_initialize(emlrtContext *aContext);
extern void ssmDetect_terminate(void);
extern void ssmDetect_atexit(void);
extern void ssmDetect_api(const mxArray * const prhs[1], const mxArray *plhs[1]);
extern void ssmDetect_xil_terminate(void);
extern void ssmDetect(struct0_T *detector_state);

#endif
/* 
 * File trailer for _coder_ssmDetect_api.h 
 *  
 * [EOF] 
 */
