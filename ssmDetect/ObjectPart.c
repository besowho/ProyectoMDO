/*
 * File: ObjectPart.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */
/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "ObjectPart.h"
#include "ssmDetect_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : double num
 *                emxArray_ObjectPart *parts
 * Return Type  : void
 */
void ObjectPart(double num, emxArray_ObjectPart *parts)
{
  int i25;
  int j;
  i25 = parts->size[0];
  parts->size[0] = (int)num;
  emxEnsureCapacity((emxArray__common *)parts, i25, (int)sizeof(c_ObjectPart));
  for (j = 0; j < (int)num; j++) {
    for (i25 = 0; i25 < 4; i25++) {
      parts->data[j].bounding_box[i25] = 0.0;
    }

    parts->data[j].area = 0.0;
    for (i25 = 0; i25 < 6; i25++) {
      parts->data[j].features[i25] = 0.0;
    }

    for (i25 = 0; i25 < 2; i25++) {
      parts->data[j].uncertainty_score[i25] = 0.0;
    }
  }
}

/*
 * Arguments    : double parts_bounding_box[4]
 *                double *parts_area
 *                double parts_features[6]
 *                double parts_uncertainty_score[2]
 * Return Type  : void
 */
void b_ObjectPart(double parts_bounding_box[4], double *parts_area, double
                  parts_features[6], double parts_uncertainty_score[2])
{
  int i;
  for (i = 0; i < 4; i++) {
    parts_bounding_box[i] = 0.0;
  }

  *parts_area = 0.0;
  for (i = 0; i < 6; i++) {
    parts_features[i] = 0.0;
  }

  for (i = 0; i < 2; i++) {
    parts_uncertainty_score[i] = 0.0;
  }
}

/*
 * File trailer for ObjectPart.c
 *
 * [EOF]
 */
