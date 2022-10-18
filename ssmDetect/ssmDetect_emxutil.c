/*
 * File: ssmDetect_emxutil.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "ssmDetect_emxutil.h"

/* Function Declarations */
static void b_emxExpand_Object(emxArray_Object *emxArray, int fromIndex, int
  toIndex);
static void c_emxInitStruct_ConnectedCompon(ConnectedComponent *pStruct);
static void emxCopyMatrix_real_T(double dst[4], const double src[4]);
static void emxCopy_ObjectPart(emxArray_ObjectPart **dst, emxArray_ObjectPart *
  const *src);
static void emxExpand_ConnectedComponent(emxArray_ConnectedComponent *emxArray,
  int fromIndex, int toIndex);
static void emxExpand_Object(emxArray_Object *emxArray, int fromIndex, int
  toIndex);
static void emxExpand_Object_0(int fromIndex, int toIndex);
static void emxExpand_Object_1x1(b_Object data[1], int fromIndex, int toIndex);
static void emxExpand_SelectedIndices(emxArray_SelectedIndices *emxArray, int
  fromIndex, int toIndex);
static void emxFreeStruct_SelectedIndices(SelectedIndices *pStruct);
static void emxInitStruct_SelectedIndices(SelectedIndices *pStruct);
static void emxTrim_Object(emxArray_Object *emxArray, int fromIndex, int toIndex);
static void emxTrim_Object_0(int fromIndex, int toIndex);
static void emxTrim_Object_1x1(b_Object data[1], int fromIndex, int toIndex);
static void emxTrim_SelectedIndices(emxArray_SelectedIndices *emxArray, int
  fromIndex, int toIndex);

/* Function Definitions */

/*
 * Arguments    : emxArray_Object *emxArray
 *                int fromIndex
 *                int toIndex
 * Return Type  : void
 */
static void b_emxExpand_Object(emxArray_Object *emxArray, int fromIndex, int
  toIndex)
{
  int i;
  for (i = fromIndex; i < toIndex; i++) {
    emxInitStruct_Object(&emxArray->data[i]);
  }
}

/*
 * Arguments    : ConnectedComponent *pStruct
 * Return Type  : void
 */
static void c_emxInitStruct_ConnectedCompon(ConnectedComponent *pStruct)
{
  pStruct->pixel_idx.size[0] = 0;
  pStruct->pixel_idx.size[1] = 0;
}

/*
 * Arguments    : double dst[4]
 *                const double src[4]
 * Return Type  : void
 */
static void emxCopyMatrix_real_T(double dst[4], const double src[4])
{
  int i;
  for (i = 0; i < 4; i++) {
    dst[i] = src[i];
  }
}

/*
 * Arguments    : emxArray_ObjectPart **dst
 *                emxArray_ObjectPart * const *src
 * Return Type  : void
 */
static void emxCopy_ObjectPart(emxArray_ObjectPart **dst, emxArray_ObjectPart *
  const *src)
{
  int numElDst;
  int numElSrc;
  int i;
  numElDst = 1;
  numElSrc = 1;
  for (i = 0; i < (*dst)->numDimensions; i++) {
    numElDst *= (*dst)->size[i];
    numElSrc *= (*src)->size[i];
  }

  for (i = 0; i < (*dst)->numDimensions; i++) {
    (*dst)->size[i] = (*src)->size[i];
  }

  emxEnsureCapacity((emxArray__common *)*dst, numElDst, (int)sizeof(c_ObjectPart));
  for (i = 0; i < numElSrc; i++) {
    (*dst)->data[i] = (*src)->data[i];
  }
}

/*
 * Arguments    : emxArray_ConnectedComponent *emxArray
 *                int fromIndex
 *                int toIndex
 * Return Type  : void
 */
static void emxExpand_ConnectedComponent(emxArray_ConnectedComponent *emxArray,
  int fromIndex, int toIndex)
{
  int i;
  for (i = fromIndex; i < toIndex; i++) {
    c_emxInitStruct_ConnectedCompon(&emxArray->data[i]);
  }
}

/*
 * Arguments    : emxArray_Object *emxArray
 *                int fromIndex
 *                int toIndex
 * Return Type  : void
 */
static void emxExpand_Object(emxArray_Object *emxArray, int fromIndex, int
  toIndex)
{
  int i;
  for (i = fromIndex; i < toIndex; i++) {
    emxInitStruct_Object(&emxArray->data[i]);
  }
}

/*
 * Arguments    : int fromIndex
 *                int toIndex
 * Return Type  : void
 */
static void emxExpand_Object_0(int fromIndex, int toIndex)
{
  int i;
  for (i = fromIndex; i < toIndex; i++) {
    emxInitStruct_Object(NULL);
  }
}

/*
 * Arguments    : b_Object data[1]
 *                int fromIndex
 *                int toIndex
 * Return Type  : void
 */
static void emxExpand_Object_1x1(b_Object data[1], int fromIndex, int toIndex)
{
  int i;
  for (i = fromIndex; i < toIndex; i++) {
    emxInitStruct_Object(&data[i]);
  }
}

/*
 * Arguments    : emxArray_SelectedIndices *emxArray
 *                int fromIndex
 *                int toIndex
 * Return Type  : void
 */
static void emxExpand_SelectedIndices(emxArray_SelectedIndices *emxArray, int
  fromIndex, int toIndex)
{
  int i;
  for (i = fromIndex; i < toIndex; i++) {
    emxInitStruct_SelectedIndices(&emxArray->data[i]);
  }
}

/*
 * Arguments    : SelectedIndices *pStruct
 * Return Type  : void
 */
static void emxFreeStruct_SelectedIndices(SelectedIndices *pStruct)
{
  emxFree_real_T(&pStruct->idx);
}

/*
 * Arguments    : SelectedIndices *pStruct
 * Return Type  : void
 */
static void emxInitStruct_SelectedIndices(SelectedIndices *pStruct)
{
  emxInit_real_T(&pStruct->idx, 2);
}

/*
 * Arguments    : emxArray_Object *emxArray
 *                int fromIndex
 *                int toIndex
 * Return Type  : void
 */
static void emxTrim_Object(emxArray_Object *emxArray, int fromIndex, int toIndex)
{
  int i;
  for (i = fromIndex; i < toIndex; i++) {
    emxFreeStruct_Object(&emxArray->data[i]);
  }
}

/*
 * Arguments    : int fromIndex
 *                int toIndex
 * Return Type  : void
 */
static void emxTrim_Object_0(int fromIndex, int toIndex)
{
  int i;
  for (i = fromIndex; i < toIndex; i++) {
    emxFreeStruct_Object(NULL);
  }
}

/*
 * Arguments    : b_Object data[1]
 *                int fromIndex
 *                int toIndex
 * Return Type  : void
 */
static void emxTrim_Object_1x1(b_Object data[1], int fromIndex, int toIndex)
{
  int i;
  for (i = fromIndex; i < toIndex; i++) {
    emxFreeStruct_Object(&data[i]);
  }
}

/*
 * Arguments    : emxArray_SelectedIndices *emxArray
 *                int fromIndex
 *                int toIndex
 * Return Type  : void
 */
static void emxTrim_SelectedIndices(emxArray_SelectedIndices *emxArray, int
  fromIndex, int toIndex)
{
  int i;
  for (i = fromIndex; i < toIndex; i++) {
    emxFreeStruct_SelectedIndices(&emxArray->data[i]);
  }
}

/*
 * Arguments    : b_Object data[1]
 *                int size[2]
 *                int oldNumel
 * Return Type  : void
 */
void b_emxEnsureCapacity_Object(b_Object data[1], int size[2], int oldNumel)
{
  int newNumel;
  newNumel = size[0] * size[1];
  if (oldNumel > newNumel) {
    emxTrim_Object_1x1(data, newNumel, oldNumel);
  } else {
    if (oldNumel < newNumel) {
      emxExpand_Object_1x1(data, oldNumel, newNumel);
    }
  }
}

/*
 * Arguments    : emxArray_Object **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void b_emxInit_Object(emxArray_Object **pEmxArray, int numDimensions)
{
  emxArray_Object *emxArray;
  int i;
  *pEmxArray = (emxArray_Object *)malloc(sizeof(emxArray_Object));
  emxArray = *pEmxArray;
  emxArray->data = (b_Object *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : emxArray_int32_T **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void b_emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions)
{
  emxArray_int32_T *emxArray;
  int i;
  *pEmxArray = (emxArray_int32_T *)malloc(sizeof(emxArray_int32_T));
  emxArray = *pEmxArray;
  emxArray->data = (int *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : emxArray_real_T **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void b_emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions)
{
  emxArray_real_T *emxArray;
  int i;
  *pEmxArray = (emxArray_real_T *)malloc(sizeof(emxArray_real_T));
  emxArray = *pEmxArray;
  emxArray->data = (double *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : emxArray_ConnectedComponent *emxArray
 *                int oldNumel
 * Return Type  : void
 */
void c_emxEnsureCapacity_ConnectedCo(emxArray_ConnectedComponent *emxArray, int
  oldNumel)
{
  int elementSize;
  int newNumel;
  int i;
  void *newData;
  elementSize = (int)sizeof(ConnectedComponent);
  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }

  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }

    while (i < newNumel) {
      i <<= 1;
    }

    newData = calloc((unsigned int)i, (unsigned int)elementSize);
    if (emxArray->data != NULL) {
      memcpy(newData, (void *)emxArray->data, (unsigned int)(elementSize *
              oldNumel));
      if (emxArray->canFreeData) {
        free((void *)emxArray->data);
      }
    }

    emxArray->data = (ConnectedComponent *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }

  if (oldNumel > newNumel) {
    emxExpand_ConnectedComponent(emxArray, oldNumel, newNumel);
  }
}

/*
 * Arguments    : emxArray_Object *emxArray
 *                int oldNumel
 * Return Type  : void
 */
void c_emxEnsureCapacity_Object(emxArray_Object *emxArray, int oldNumel)
{
  int elementSize;
  int newNumel;
  int i;
  void *newData;
  elementSize = (int)sizeof(b_Object);
  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }

  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }

    while (i < newNumel) {
      i <<= 1;
    }

    newData = calloc((unsigned int)i, (unsigned int)elementSize);
    if (emxArray->data != NULL) {
      memcpy(newData, (void *)emxArray->data, (unsigned int)(elementSize *
              oldNumel));
      if (emxArray->canFreeData) {
        free((void *)emxArray->data);
      }
    }

    emxArray->data = (b_Object *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }

  if (oldNumel > newNumel) {
    emxTrim_Object(emxArray, newNumel, oldNumel);
  } else {
    if (oldNumel < newNumel) {
      b_emxExpand_Object(emxArray, oldNumel, newNumel);
    }
  }
}

/*
 * Arguments    : emxArray_SelectedIndices *emxArray
 *                int oldNumel
 * Return Type  : void
 */
void c_emxEnsureCapacity_SelectedInd(emxArray_SelectedIndices *emxArray, int
  oldNumel)
{
  int elementSize;
  int newNumel;
  int i;
  void *newData;
  elementSize = (int)sizeof(SelectedIndices);
  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }

  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }

    while (i < newNumel) {
      i <<= 1;
    }

    newData = calloc((unsigned int)i, (unsigned int)elementSize);
    if (emxArray->data != NULL) {
      memcpy(newData, (void *)emxArray->data, (unsigned int)(elementSize *
              oldNumel));
      if (emxArray->canFreeData) {
        free((void *)emxArray->data);
      }
    }

    emxArray->data = (SelectedIndices *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }

  if (oldNumel > newNumel) {
    emxTrim_SelectedIndices(emxArray, newNumel, oldNumel);
  } else {
    if (oldNumel < newNumel) {
      emxExpand_SelectedIndices(emxArray, oldNumel, newNumel);
    }
  }
}

/*
 * Arguments    : emxArray_real_T **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void c_emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions)
{
  emxArray_real_T *emxArray;
  int i;
  *pEmxArray = (emxArray_real_T *)malloc(sizeof(emxArray_real_T));
  emxArray = *pEmxArray;
  emxArray->data = (double *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : int size[1]
 *                int oldNumel
 * Return Type  : void
 */
void d_emxEnsureCapacity_Object(int size[1], int oldNumel)
{
  if (oldNumel > size[0]) {
    emxTrim_Object_0(size[0], oldNumel);
  } else {
    if (oldNumel < size[0]) {
      emxExpand_Object_0(oldNumel, size[0]);
    }
  }
}

/*
 * Arguments    : b_Object *dst
 *                const b_Object *src
 * Return Type  : void
 */
void emxCopyStruct_Object(b_Object *dst, const b_Object *src)
{
  emxCopyMatrix_real_T(dst->bounding_box, src->bounding_box);
  dst->area = src->area;
  emxCopy_ObjectPart(&dst->parts, &src->parts);
}

/*
 * Arguments    : emxArray__common *emxArray
 *                int oldNumel
 *                int elementSize
 * Return Type  : void
 */
void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, int elementSize)
{
  int newNumel;
  int i;
  void *newData;
  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }

  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }

    while (i < newNumel) {
      i <<= 1;
    }

    newData = calloc((unsigned int)i, (unsigned int)elementSize);
    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, (unsigned int)(elementSize * oldNumel));
      if (emxArray->canFreeData) {
        free(emxArray->data);
      }
    }

    emxArray->data = newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

/*
 * Arguments    : emxArray_Object *emxArray
 *                int oldNumel
 * Return Type  : void
 */
void emxEnsureCapacity_Object(emxArray_Object *emxArray, int oldNumel)
{
  int elementSize;
  int newNumel;
  int i;
  void *newData;
  elementSize = (int)sizeof(b_Object);
  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }

  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }

    while (i < newNumel) {
      i <<= 1;
    }

    newData = calloc((unsigned int)i, (unsigned int)elementSize);
    if (emxArray->data != NULL) {
      memcpy(newData, (void *)emxArray->data, (unsigned int)(elementSize *
              oldNumel));
      if (emxArray->canFreeData) {
        free((void *)emxArray->data);
      }
    }

    emxArray->data = (b_Object *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }

  if (oldNumel > newNumel) {
    emxTrim_Object(emxArray, newNumel, oldNumel);
  } else {
    if (oldNumel < newNumel) {
      emxExpand_Object(emxArray, oldNumel, newNumel);
    }
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void emxFreeMatrix_Object(void)
{
}

/*
 * Arguments    : b_Object *pStruct
 * Return Type  : void
 */
void emxFreeStruct_Object(b_Object *pStruct)
{
  emxFree_ObjectPart(&pStruct->parts);
}

/*
 * Arguments    : emxArray_ConnectedComponent **pEmxArray
 * Return Type  : void
 */
void emxFree_ConnectedComponent(emxArray_ConnectedComponent **pEmxArray)
{
  if (*pEmxArray != (emxArray_ConnectedComponent *)NULL) {
    if (((*pEmxArray)->data != (ConnectedComponent *)NULL) && (*pEmxArray)
        ->canFreeData) {
      free((void *)(*pEmxArray)->data);
    }

    free((void *)(*pEmxArray)->size);
    free((void *)*pEmxArray);
    *pEmxArray = (emxArray_ConnectedComponent *)NULL;
  }
}

/*
 * Arguments    : emxArray_Object **pEmxArray
 * Return Type  : void
 */
void emxFree_Object(emxArray_Object **pEmxArray)
{
  int numEl;
  int i;
  if (*pEmxArray != (emxArray_Object *)NULL) {
    if ((*pEmxArray)->data != (b_Object *)NULL) {
      numEl = 1;
      for (i = 0; i < (*pEmxArray)->numDimensions; i++) {
        numEl *= (*pEmxArray)->size[i];
      }

      for (i = 0; i < numEl; i++) {
        emxFreeStruct_Object(&(*pEmxArray)->data[i]);
      }

      if ((*pEmxArray)->canFreeData) {
        free((void *)(*pEmxArray)->data);
      }
    }

    free((void *)(*pEmxArray)->size);
    free((void *)*pEmxArray);
    *pEmxArray = (emxArray_Object *)NULL;
  }
}

/*
 * Arguments    : emxArray_ObjectPart **pEmxArray
 * Return Type  : void
 */
void emxFree_ObjectPart(emxArray_ObjectPart **pEmxArray)
{
  if (*pEmxArray != (emxArray_ObjectPart *)NULL) {
    if (((*pEmxArray)->data != (c_ObjectPart *)NULL) && (*pEmxArray)
        ->canFreeData) {
      free((void *)(*pEmxArray)->data);
    }

    free((void *)(*pEmxArray)->size);
    free((void *)*pEmxArray);
    *pEmxArray = (emxArray_ObjectPart *)NULL;
  }
}

/*
 * Arguments    : emxArray_Object_0 *pEmxArray
 * Return Type  : void
 */
void emxFree_Object_0(emxArray_Object_0 *pEmxArray)
{
  int numEl;
  int i;
  numEl = 1;
  i = 0;
  while (i < 1) {
    numEl *= pEmxArray->size[0];
    i = 1;
  }

  for (i = 0; i < numEl; i++) {
    emxFreeStruct_Object(NULL);
  }
}

/*
 * Arguments    : emxArray_Object_1x1 *pEmxArray
 * Return Type  : void
 */
void emxFree_Object_1x1(emxArray_Object_1x1 *pEmxArray)
{
  int numEl;
  int i;
  numEl = 1;
  for (i = 0; i < 2; i++) {
    numEl *= pEmxArray->size[i];
  }

  for (i = 0; i < numEl; i++) {
    emxFreeStruct_Object(&pEmxArray->data[i]);
  }
}

/*
 * Arguments    : emxArray_SelectedIndices **pEmxArray
 * Return Type  : void
 */
void emxFree_SelectedIndices(emxArray_SelectedIndices **pEmxArray)
{
  int numEl;
  int i;
  if (*pEmxArray != (emxArray_SelectedIndices *)NULL) {
    if ((*pEmxArray)->data != (SelectedIndices *)NULL) {
      numEl = 1;
      for (i = 0; i < (*pEmxArray)->numDimensions; i++) {
        numEl *= (*pEmxArray)->size[i];
      }

      for (i = 0; i < numEl; i++) {
        emxFreeStruct_SelectedIndices(&(*pEmxArray)->data[i]);
      }

      if ((*pEmxArray)->canFreeData) {
        free((void *)(*pEmxArray)->data);
      }
    }

    free((void *)(*pEmxArray)->size);
    free((void *)*pEmxArray);
    *pEmxArray = (emxArray_SelectedIndices *)NULL;
  }
}

/*
 * Arguments    : emxArray_boolean_T **pEmxArray
 * Return Type  : void
 */
void emxFree_boolean_T(emxArray_boolean_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_boolean_T *)NULL) {
    if (((*pEmxArray)->data != (boolean_T *)NULL) && (*pEmxArray)->canFreeData)
    {
      free((void *)(*pEmxArray)->data);
    }

    free((void *)(*pEmxArray)->size);
    free((void *)*pEmxArray);
    *pEmxArray = (emxArray_boolean_T *)NULL;
  }
}

/*
 * Arguments    : emxArray_int32_T **pEmxArray
 * Return Type  : void
 */
void emxFree_int32_T(emxArray_int32_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_int32_T *)NULL) {
    if (((*pEmxArray)->data != (int *)NULL) && (*pEmxArray)->canFreeData) {
      free((void *)(*pEmxArray)->data);
    }

    free((void *)(*pEmxArray)->size);
    free((void *)*pEmxArray);
    *pEmxArray = (emxArray_int32_T *)NULL;
  }
}

/*
 * Arguments    : emxArray_real_T **pEmxArray
 * Return Type  : void
 */
void emxFree_real_T(emxArray_real_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_real_T *)NULL) {
    if (((*pEmxArray)->data != (double *)NULL) && (*pEmxArray)->canFreeData) {
      free((void *)(*pEmxArray)->data);
    }

    free((void *)(*pEmxArray)->size);
    free((void *)*pEmxArray);
    *pEmxArray = (emxArray_real_T *)NULL;
  }
}

/*
 * Arguments    : emxArray_struct_T **pEmxArray
 * Return Type  : void
 */
void emxFree_struct_T(emxArray_struct_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_struct_T *)NULL) {
    if (((*pEmxArray)->data != (struct_T *)NULL) && (*pEmxArray)->canFreeData) {
      free((void *)(*pEmxArray)->data);
    }

    free((void *)(*pEmxArray)->size);
    free((void *)*pEmxArray);
    *pEmxArray = (emxArray_struct_T *)NULL;
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void emxInitMatrix_Object(void)
{
}

/*
 * Arguments    : b_Object *pStruct
 * Return Type  : void
 */
void emxInitStruct_Object(b_Object *pStruct)
{
  emxInit_ObjectPart(&pStruct->parts, 1);
}

/*
 * Arguments    : emxArray_ConnectedComponent **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInit_ConnectedComponent(emxArray_ConnectedComponent **pEmxArray, int
  numDimensions)
{
  emxArray_ConnectedComponent *emxArray;
  int i;
  *pEmxArray = (emxArray_ConnectedComponent *)malloc(sizeof
    (emxArray_ConnectedComponent));
  emxArray = *pEmxArray;
  emxArray->data = (ConnectedComponent *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : emxArray_Object **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInit_Object(emxArray_Object **pEmxArray, int numDimensions)
{
  emxArray_Object *emxArray;
  int i;
  *pEmxArray = (emxArray_Object *)malloc(sizeof(emxArray_Object));
  emxArray = *pEmxArray;
  emxArray->data = (b_Object *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : emxArray_ObjectPart **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInit_ObjectPart(emxArray_ObjectPart **pEmxArray, int numDimensions)
{
  emxArray_ObjectPart *emxArray;
  int i;
  *pEmxArray = (emxArray_ObjectPart *)malloc(sizeof(emxArray_ObjectPart));
  emxArray = *pEmxArray;
  emxArray->data = (c_ObjectPart *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : emxArray_Object_0 *pEmxArray
 * Return Type  : void
 */
void emxInit_Object_0(emxArray_Object_0 *pEmxArray)
{
  int i;
  i = 0;
  while (i < 1) {
    pEmxArray->size[0] = 0;
    i = 1;
  }
}

/*
 * Arguments    : emxArray_Object_1x1 *pEmxArray
 * Return Type  : void
 */
void emxInit_Object_1x1(emxArray_Object_1x1 *pEmxArray)
{
  int i;
  for (i = 0; i < 2; i++) {
    pEmxArray->size[i] = 0;
  }
}

/*
 * Arguments    : emxArray_SelectedIndices **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInit_SelectedIndices(emxArray_SelectedIndices **pEmxArray, int
  numDimensions)
{
  emxArray_SelectedIndices *emxArray;
  int i;
  *pEmxArray = (emxArray_SelectedIndices *)malloc(sizeof
    (emxArray_SelectedIndices));
  emxArray = *pEmxArray;
  emxArray->data = (SelectedIndices *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : emxArray_boolean_T **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInit_boolean_T(emxArray_boolean_T **pEmxArray, int numDimensions)
{
  emxArray_boolean_T *emxArray;
  int i;
  *pEmxArray = (emxArray_boolean_T *)malloc(sizeof(emxArray_boolean_T));
  emxArray = *pEmxArray;
  emxArray->data = (boolean_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : emxArray_int32_T **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions)
{
  emxArray_int32_T *emxArray;
  int i;
  *pEmxArray = (emxArray_int32_T *)malloc(sizeof(emxArray_int32_T));
  emxArray = *pEmxArray;
  emxArray->data = (int *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : emxArray_real_T **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions)
{
  emxArray_real_T *emxArray;
  int i;
  *pEmxArray = (emxArray_real_T *)malloc(sizeof(emxArray_real_T));
  emxArray = *pEmxArray;
  emxArray->data = (double *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : emxArray_struct_T **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInit_struct_T(emxArray_struct_T **pEmxArray, int numDimensions)
{
  emxArray_struct_T *emxArray;
  int i;
  *pEmxArray = (emxArray_struct_T *)malloc(sizeof(emxArray_struct_T));
  emxArray = *pEmxArray;
  emxArray->data = (struct_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * File trailer for ssmDetect_emxutil.c
 *
 * [EOF]
 */
