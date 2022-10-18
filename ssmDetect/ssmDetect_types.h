/* 
 * File: ssmDetect_types.h 
 *  
 * MATLAB Coder version            : 2.7 
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22 
 */

#ifndef __SSMDETECT_TYPES_H__
#define __SSMDETECT_TYPES_H__

/* Include Files */ 
#include "rtwtypes.h"

/* Type Definitions */ 
#ifndef struct_emxArray_real_T_2500x1
#define struct_emxArray_real_T_2500x1
struct emxArray_real_T_2500x1
{
    double data[2500];
    int size[2];
};
#endif /*struct_emxArray_real_T_2500x1*/
#ifndef typedef_emxArray_real_T_2500x1
#define typedef_emxArray_real_T_2500x1
typedef struct emxArray_real_T_2500x1 emxArray_real_T_2500x1;
#endif /*typedef_emxArray_real_T_2500x1*/
#ifndef struct_sPa5J2A6sBBdIo9I7KkSpTG
#define struct_sPa5J2A6sBBdIo9I7KkSpTG
struct sPa5J2A6sBBdIo9I7KkSpTG
{
    double label;
    emxArray_real_T_2500x1 pixel_idx;
    double area;
};
#endif /*struct_sPa5J2A6sBBdIo9I7KkSpTG*/
#ifndef typedef_ConnectedComponent
#define typedef_ConnectedComponent
typedef struct sPa5J2A6sBBdIo9I7KkSpTG ConnectedComponent;
#endif /*typedef_ConnectedComponent*/
#ifndef struct_emxArray_ConnectedComponent
#define struct_emxArray_ConnectedComponent
struct emxArray_ConnectedComponent
{
    ConnectedComponent *data;
    int *size;
    int allocatedSize;
    int numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_ConnectedComponent*/
#ifndef typedef_emxArray_ConnectedComponent
#define typedef_emxArray_ConnectedComponent
typedef struct emxArray_ConnectedComponent emxArray_ConnectedComponent;
#endif /*typedef_emxArray_ConnectedComponent*/
#ifndef typedef_c_ObjectPart
#define typedef_c_ObjectPart
typedef struct
{
    double bounding_box[4];
    double area;
    double features[6];
    double uncertainty_score[2];
} c_ObjectPart;
#endif /*typedef_c_ObjectPart*/
#ifndef struct_emxArray_ObjectPart
#define struct_emxArray_ObjectPart
struct emxArray_ObjectPart
{
    c_ObjectPart *data;
    int *size;
    int allocatedSize;
    int numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_ObjectPart*/
#ifndef typedef_emxArray_ObjectPart
#define typedef_emxArray_ObjectPart
typedef struct emxArray_ObjectPart emxArray_ObjectPart;
#endif /*typedef_emxArray_ObjectPart*/
#ifndef typedef_b_Object
#define typedef_b_Object
typedef struct
{
    double bounding_box[4];
    double area;
    emxArray_ObjectPart *parts;
} b_Object;
#endif /*typedef_b_Object*/
#ifndef struct_emxArray_Object
#define struct_emxArray_Object
struct emxArray_Object
{
    b_Object *data;
    int *size;
    int allocatedSize;
    int numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_Object*/
#ifndef typedef_emxArray_Object
#define typedef_emxArray_Object
typedef struct emxArray_Object emxArray_Object;
#endif /*typedef_emxArray_Object*/
#ifndef struct_emxArray_Object_0
#define struct_emxArray_Object_0
struct emxArray_Object_0
{
    int size[1];
};
#endif /*struct_emxArray_Object_0*/
#ifndef typedef_emxArray_Object_0
#define typedef_emxArray_Object_0
typedef struct emxArray_Object_0 emxArray_Object_0;
#endif /*typedef_emxArray_Object_0*/
#ifndef struct_emxArray_Object_1x1
#define struct_emxArray_Object_1x1
struct emxArray_Object_1x1
{
    b_Object data[1];
    int size[2];
};
#endif /*struct_emxArray_Object_1x1*/
#ifndef typedef_emxArray_Object_1x1
#define typedef_emxArray_Object_1x1
typedef struct emxArray_Object_1x1 emxArray_Object_1x1;
#endif /*typedef_emxArray_Object_1x1*/
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T
{
    double *data;
    int *size;
    int allocatedSize;
    int numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_real_T*/
#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T
typedef struct emxArray_real_T emxArray_real_T;
#endif /*typedef_emxArray_real_T*/
#ifndef struct_sYNRo5bXC4BSiMhVlVMcVkC
#define struct_sYNRo5bXC4BSiMhVlVMcVkC
struct sYNRo5bXC4BSiMhVlVMcVkC
{
    emxArray_real_T *idx;
};
#endif /*struct_sYNRo5bXC4BSiMhVlVMcVkC*/
#ifndef typedef_SelectedIndices
#define typedef_SelectedIndices
typedef struct sYNRo5bXC4BSiMhVlVMcVkC SelectedIndices;
#endif /*typedef_SelectedIndices*/
#ifndef struct_emxArray_SelectedIndices
#define struct_emxArray_SelectedIndices
struct emxArray_SelectedIndices
{
    SelectedIndices *data;
    int *size;
    int allocatedSize;
    int numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_SelectedIndices*/
#ifndef typedef_emxArray_SelectedIndices
#define typedef_emxArray_SelectedIndices
typedef struct emxArray_SelectedIndices emxArray_SelectedIndices;
#endif /*typedef_emxArray_SelectedIndices*/
#ifndef struct_emxArray__common
#define struct_emxArray__common
struct emxArray__common
{
    void *data;
    int *size;
    int allocatedSize;
    int numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray__common*/
#ifndef typedef_emxArray__common
#define typedef_emxArray__common
typedef struct emxArray__common emxArray__common;
#endif /*typedef_emxArray__common*/
#ifndef struct_emxArray_boolean_T
#define struct_emxArray_boolean_T
struct emxArray_boolean_T
{
    boolean_T *data;
    int *size;
    int allocatedSize;
    int numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_boolean_T*/
#ifndef typedef_emxArray_boolean_T
#define typedef_emxArray_boolean_T
typedef struct emxArray_boolean_T emxArray_boolean_T;
#endif /*typedef_emxArray_boolean_T*/
#ifndef struct_emxArray_boolean_T_1x2500
#define struct_emxArray_boolean_T_1x2500
struct emxArray_boolean_T_1x2500
{
    boolean_T data[2500];
    int size[2];
};
#endif /*struct_emxArray_boolean_T_1x2500*/
#ifndef typedef_emxArray_boolean_T_1x2500
#define typedef_emxArray_boolean_T_1x2500
typedef struct emxArray_boolean_T_1x2500 emxArray_boolean_T_1x2500;
#endif /*typedef_emxArray_boolean_T_1x2500*/
#ifndef struct_emxArray_boolean_T_50x50
#define struct_emxArray_boolean_T_50x50
struct emxArray_boolean_T_50x50
{
    boolean_T data[2500];
    int size[2];
};
#endif /*struct_emxArray_boolean_T_50x50*/
#ifndef typedef_emxArray_boolean_T_50x50
#define typedef_emxArray_boolean_T_50x50
typedef struct emxArray_boolean_T_50x50 emxArray_boolean_T_50x50;
#endif /*typedef_emxArray_boolean_T_50x50*/
#ifndef struct_emxArray_int32_T
#define struct_emxArray_int32_T
struct emxArray_int32_T
{
    int *data;
    int *size;
    int allocatedSize;
    int numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_int32_T*/
#ifndef typedef_emxArray_int32_T
#define typedef_emxArray_int32_T
typedef struct emxArray_int32_T emxArray_int32_T;
#endif /*typedef_emxArray_int32_T*/
#ifndef struct_emxArray_int32_T_1x52
#define struct_emxArray_int32_T_1x52
struct emxArray_int32_T_1x52
{
    int data[52];
    int size[2];
};
#endif /*struct_emxArray_int32_T_1x52*/
#ifndef typedef_emxArray_int32_T_1x52
#define typedef_emxArray_int32_T_1x52
typedef struct emxArray_int32_T_1x52 emxArray_int32_T_1x52;
#endif /*typedef_emxArray_int32_T_1x52*/
#ifndef struct_emxArray_int32_T_2500
#define struct_emxArray_int32_T_2500
struct emxArray_int32_T_2500
{
    int data[2500];
    int size[1];
};
#endif /*struct_emxArray_int32_T_2500*/
#ifndef typedef_emxArray_int32_T_2500
#define typedef_emxArray_int32_T_2500
typedef struct emxArray_int32_T_2500 emxArray_int32_T_2500;
#endif /*typedef_emxArray_int32_T_2500*/
#ifndef struct_emxArray_int32_T_5
#define struct_emxArray_int32_T_5
struct emxArray_int32_T_5
{
    int data[5];
    int size[1];
};
#endif /*struct_emxArray_int32_T_5*/
#ifndef typedef_emxArray_int32_T_5
#define typedef_emxArray_int32_T_5
typedef struct emxArray_int32_T_5 emxArray_int32_T_5;
#endif /*typedef_emxArray_int32_T_5*/
#ifndef struct_emxArray_real_T_1x2500
#define struct_emxArray_real_T_1x2500
struct emxArray_real_T_1x2500
{
    double data[2500];
    int size[2];
};
#endif /*struct_emxArray_real_T_1x2500*/
#ifndef typedef_emxArray_real_T_1x2500
#define typedef_emxArray_real_T_1x2500
typedef struct emxArray_real_T_1x2500 emxArray_real_T_1x2500;
#endif /*typedef_emxArray_real_T_1x2500*/
#ifndef struct_emxArray_real_T_2500
#define struct_emxArray_real_T_2500
struct emxArray_real_T_2500
{
    double data[2500];
    int size[1];
};
#endif /*struct_emxArray_real_T_2500*/
#ifndef typedef_emxArray_real_T_2500
#define typedef_emxArray_real_T_2500
typedef struct emxArray_real_T_2500 emxArray_real_T_2500;
#endif /*typedef_emxArray_real_T_2500*/
#ifndef struct_emxArray_real_T_2500x2
#define struct_emxArray_real_T_2500x2
struct emxArray_real_T_2500x2
{
    double data[5000];
    int size[2];
};
#endif /*struct_emxArray_real_T_2500x2*/
#ifndef typedef_emxArray_real_T_2500x2
#define typedef_emxArray_real_T_2500x2
typedef struct emxArray_real_T_2500x2 emxArray_real_T_2500x2;
#endif /*typedef_emxArray_real_T_2500x2*/
#ifndef struct_emxArray_real_T_2x2500
#define struct_emxArray_real_T_2x2500
struct emxArray_real_T_2x2500
{
    double data[5000];
    int size[2];
};
#endif /*struct_emxArray_real_T_2x2500*/
#ifndef typedef_emxArray_real_T_2x2500
#define typedef_emxArray_real_T_2x2500
typedef struct emxArray_real_T_2x2500 emxArray_real_T_2x2500;
#endif /*typedef_emxArray_real_T_2x2500*/
#ifndef struct_emxArray_real_T_49x50
#define struct_emxArray_real_T_49x50
struct emxArray_real_T_49x50
{
    double data[2450];
    int size[2];
};
#endif /*struct_emxArray_real_T_49x50*/
#ifndef typedef_emxArray_real_T_49x50
#define typedef_emxArray_real_T_49x50
typedef struct emxArray_real_T_49x50 emxArray_real_T_49x50;
#endif /*typedef_emxArray_real_T_49x50*/
#ifndef struct_emxArray_real_T_50x50
#define struct_emxArray_real_T_50x50
struct emxArray_real_T_50x50
{
    double data[2500];
    int size[2];
};
#endif /*struct_emxArray_real_T_50x50*/
#ifndef typedef_emxArray_real_T_50x50
#define typedef_emxArray_real_T_50x50
typedef struct emxArray_real_T_50x50 emxArray_real_T_50x50;
#endif /*typedef_emxArray_real_T_50x50*/
#ifndef typedef_struct_T
#define typedef_struct_T
typedef struct
{
    double label;
    double area;
} struct_T;
#endif /*typedef_struct_T*/
#ifndef struct_emxArray_struct_T
#define struct_emxArray_struct_T
struct emxArray_struct_T
{
    struct_T *data;
    int *size;
    int allocatedSize;
    int numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_struct_T*/
#ifndef typedef_emxArray_struct_T
#define typedef_emxArray_struct_T
typedef struct emxArray_struct_T emxArray_struct_T;
#endif /*typedef_emxArray_struct_T*/
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
    double Mu[5];
    double Cov[25];
    double w;
    double Prec[25];
} struct1_T;
#endif /*typedef_struct1_T*/
#ifndef typedef_struct2_T
#define typedef_struct2_T
typedef struct
{
    double bounding_box[4];
    double area;
} struct2_T;
#endif /*typedef_struct2_T*/
#ifndef typedef_struct0_T
#define typedef_struct0_T
typedef struct
{
    boolean_T use_prior_on_mixture;
    boolean_T use_uniform_component;
    Colorspace colorspace;
    double em_min_likelihood_delta;
    double em_max_steps;
    boolean_T is_initialized;
    struct1_T prior_mixture[3];
    struct1_T current_mixture[3];
    double em_image_size[2];
    double spatial_data[5000];
    double PI_i[10000];
    double sel_xy[400];
    double num_points;
    struct2_T objects[20];
    double num_objects;
    double Im_in[7500];
} struct0_T;
#endif /*typedef_struct0_T*/

#endif
/* 
 * File trailer for ssmDetect_types.h 
 *  
 * [EOF] 
 */
