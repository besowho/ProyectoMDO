/*
 * File: convn.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "convn.h"
#include "ssmDetect_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *A
 *                const double B[9]
 *                emxArray_real_T *C
 * Return Type  : void
 */
void convn(const emxArray_real_T *A, const double B[9], emxArray_real_T *C)
{
  signed char iv2[3];
  int firstRowA;
  int aidx;
  int k;
  int sA;
  int sC;
  signed char iv3[3];
  int i;
  int c;
  int b_c;
  int c_c;
  int d_c;
  int ma;
  int na;
  int j;
  int lastColA;
  int b_j;
  int iC;
  int iA;
  int iB;
  int b_i;
  int c_i;
  int a_length;
  int r;
  for (firstRowA = 0; firstRowA < 3; firstRowA++) {
    iv2[firstRowA] = (signed char)A->size[firstRowA];
  }

  firstRowA = C->size[0] * C->size[1] * C->size[2];
  C->size[0] = iv2[0];
  emxEnsureCapacity((emxArray__common *)C, firstRowA, (int)sizeof(double));
  firstRowA = C->size[0] * C->size[1] * C->size[2];
  C->size[1] = iv2[1];
  emxEnsureCapacity((emxArray__common *)C, firstRowA, (int)sizeof(double));
  firstRowA = C->size[0] * C->size[1] * C->size[2];
  C->size[2] = iv2[2];
  emxEnsureCapacity((emxArray__common *)C, firstRowA, (int)sizeof(double));
  aidx = iv2[0] * iv2[1] * iv2[2];
  for (firstRowA = 0; firstRowA < aidx; firstRowA++) {
    C->data[firstRowA] = 0.0;
  }

  k = 3;
  while ((k > 2) && (A->size[2] == 1)) {
    k = 2;
  }

  if (3 > k) {
    sA = A->size[0] * A->size[1] * A->size[2];
  } else {
    sA = 1;
    for (k = 0; k < 2; k++) {
      sA *= A->size[k];
    }
  }

  k = 3;
  while ((k > 2) && (iv2[2] == 1)) {
    k = 2;
  }

  if (3 > k) {
    sC = iv2[0] * iv2[1] * iv2[2];
  } else {
    sC = 1;
    for (k = 0; k < 2; k++) {
      iv3[0] = iv2[0];
      iv3[1] = iv2[1];
      iv3[2] = iv2[2];
      sC *= iv3[k];
    }
  }

  for (i = 0; i < A->size[2]; i++) {
    c = i * sA;
    if (i <= iv2[2] - 1) {
      b_c = sC * i;
      c_c = C->size[1];
      d_c = C->size[0];
      ma = A->size[0];
      na = A->size[1];
      for (j = 0; j < 3; j++) {
        if ((j + na) - 1 < c_c) {
          lastColA = na - 1;
        } else {
          lastColA = c_c - j;
        }

        if (j < 1) {
          k = 1;
        } else {
          k = 0;
        }

        while (k <= lastColA) {
          if (j + k > 1) {
            b_j = (j + k) - 1;
          } else {
            b_j = 0;
          }

          iC = b_c + b_j * d_c;
          iA = c + k * ma;
          iB = j * 3;
          for (b_i = 0; b_i < 3; b_i++) {
            if (b_i < 1) {
              firstRowA = 2;
            } else {
              firstRowA = 1;
            }

            if (b_i + ma <= d_c) {
              c_i = ma;
            } else {
              c_i = (d_c - b_i) + 1;
            }

            a_length = c_i - firstRowA;
            aidx = (iA + firstRowA) - 1;
            firstRowA = iC;
            for (r = 1; r <= a_length + 1; r++) {
              C->data[firstRowA] += B[iB] * A->data[aidx];
              aidx++;
              firstRowA++;
            }

            iB++;
            if (b_i >= 1) {
              iC++;
            }
          }

          k++;
        }
      }
    }
  }
}

/*
 * File trailer for convn.c
 *
 * [EOF]
 */
