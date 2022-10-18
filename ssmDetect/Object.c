/*
 * File: Object.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "Object.h"
#include "ssmDetect_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : int objects_size[1]
 * Return Type  : void
 */
void Object(int objects_size[1])
{
  int i26;
  emxInitMatrix_Object();
  i26 = objects_size[0];
  objects_size[0] = 0;
  d_emxEnsureCapacity_Object(objects_size, i26);
  emxFreeMatrix_Object();
}

/*
 * File trailer for Object.c
 *
 * [EOF]
 */
