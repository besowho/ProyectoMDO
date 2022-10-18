/*
 * File: ssmDetect_emxutil.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

#ifndef __SSMDETECT_EMXUTIL_H__
#define __SSMDETECT_EMXUTIL_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "ssmDetect_types.h"

/* Function Declarations */
extern void b_emxEnsureCapacity_Object(b_Object data[1], int size[2], int
  oldNumel);
extern void b_emxInit_Object(emxArray_Object **pEmxArray, int numDimensions);
extern void b_emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions);
extern void b_emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);
extern void c_emxEnsureCapacity_ConnectedCo(emxArray_ConnectedComponent
  *emxArray, int oldNumel);
extern void c_emxEnsureCapacity_Object(emxArray_Object *emxArray, int oldNumel);
extern void c_emxEnsureCapacity_SelectedInd(emxArray_SelectedIndices *emxArray,
  int oldNumel);
extern void c_emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);
extern void d_emxEnsureCapacity_Object(int size[1], int oldNumel);
extern void emxCopyStruct_Object(b_Object *dst, const b_Object *src);
extern void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, int
  elementSize);
extern void emxEnsureCapacity_Object(emxArray_Object *emxArray, int oldNumel);
extern void emxFreeMatrix_Object(void);
extern void emxFreeStruct_Object(b_Object *pStruct);
extern void emxFree_ConnectedComponent(emxArray_ConnectedComponent **pEmxArray);
extern void emxFree_Object(emxArray_Object **pEmxArray);
extern void emxFree_ObjectPart(emxArray_ObjectPart **pEmxArray);
extern void emxFree_Object_0(emxArray_Object_0 *pEmxArray);
extern void emxFree_Object_1x1(emxArray_Object_1x1 *pEmxArray);
extern void emxFree_SelectedIndices(emxArray_SelectedIndices **pEmxArray);
extern void emxFree_boolean_T(emxArray_boolean_T **pEmxArray);
extern void emxFree_int32_T(emxArray_int32_T **pEmxArray);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxFree_struct_T(emxArray_struct_T **pEmxArray);
extern void emxInitMatrix_Object(void);
extern void emxInitStruct_Object(b_Object *pStruct);
extern void emxInit_ConnectedComponent(emxArray_ConnectedComponent **pEmxArray,
  int numDimensions);
extern void emxInit_Object(emxArray_Object **pEmxArray, int numDimensions);
extern void emxInit_ObjectPart(emxArray_ObjectPart **pEmxArray, int
  numDimensions);
extern void emxInit_Object_0(emxArray_Object_0 *pEmxArray);
extern void emxInit_Object_1x1(emxArray_Object_1x1 *pEmxArray);
extern void emxInit_SelectedIndices(emxArray_SelectedIndices **pEmxArray, int
  numDimensions);
extern void emxInit_boolean_T(emxArray_boolean_T **pEmxArray, int numDimensions);
extern void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);
extern void emxInit_struct_T(emxArray_struct_T **pEmxArray, int numDimensions);

#endif
/*
 * File trailer for ssmDetect_emxutil.h
 *
 * [EOF]
 */
