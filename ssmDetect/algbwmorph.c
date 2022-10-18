/*
 * File: algbwmorph.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "algbwmorph.h"

/* Function Definitions */

/*
 * Arguments    : const boolean_T bw_data[]
 *                const int bw_size[2]
 *                boolean_T bwout_data[]
 *                int bwout_size[2]
 * Return Type  : void
 */
void algbwmorph(const boolean_T bw_data[], const int bw_size[2], boolean_T
                bwout_data[], int bwout_size[2])
{
  signed char iv4[2];
  int rowInd;
  signed char inDims[2];
  static const boolean_T lut[512] = { false, false, false, false, false, false,
    false, false, false, false, true, false, false, false, true, false, true,
    true, true, true, true, true, true, true, true, true, true, true, true, true,
    true, true, false, false, true, true, false, false, false, false, false,
    false, true, true, false, false, true, false, true, true, true, true, true,
    true, true, true, true, true, true, true, true, true, true, true, false,
    false, false, false, false, false, false, false, false, false, true, false,
    false, false, true, false, true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true, false, false, true, true,
    false, false, false, false, false, false, true, true, false, false, true,
    false, true, true, true, true, true, true, true, true, true, true, true,
    true, true, true, true, true, false, false, false, false, false, false,
    false, false, true, true, true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, false, false, false, false, false,
    false, false, false, false, false, true, false, false, false, true, false,
    true, true, true, true, true, true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true, true, false, false, false,
    false, false, false, false, false, false, false, true, false, false, false,
    true, false, true, true, true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, false, false, true, true, false, false,
    false, false, false, false, true, true, false, false, true, false, true,
    true, true, true, true, true, true, true, true, true, true, true, true, true,
    true, true, false, false, false, false, false, false, false, false, false,
    false, true, false, false, false, true, false, true, true, true, true, true,
    true, true, true, true, true, true, true, true, true, true, true, false,
    false, true, true, false, false, false, false, false, false, true, true,
    false, false, true, false, true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true, false, false, false, false,
    false, false, false, false, true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true, true, true, true, true, true,
    true, true, true, false, false, true, true, false, false, false, false, true,
    true, true, true, true, true, true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true, true, true, false, false,
    false, false, false, false, false, false, false, false, true, false, false,
    false, true, false, true, true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, false, false, true, true, false,
    false, false, false, false, false, true, true, false, false, true, false,
    true, true, true, true, true, true, true, true, true, true, true, true, true,
    true, true, true };

  int colInd;
  for (rowInd = 0; rowInd < 2; rowInd++) {
    iv4[rowInd] = (signed char)bw_size[rowInd];
  }

  bwout_size[0] = iv4[0];
  bwout_size[1] = iv4[1];
  if ((bw_size[0] == 0) || (bw_size[1] == 0)) {
  } else {
    for (rowInd = 0; rowInd < 2; rowInd++) {
      inDims[rowInd] = (signed char)bw_size[rowInd];
    }

    if ((inDims[0] >= 2) && (inDims[1] >= 2)) {
      /*  Process a 3x3 neighborhood centered around the pixel being processed.    */
      /*  process the first column first row element */
      bwout_data[0] = lut[(((bw_data[0] << 4) + (bw_data[1] << 5)) +
                           (bw_data[bw_size[0]] << 7)) + (bw_data[1 + bw_size[0]]
        << 8)];

      /*  process the first column interior elements */
      for (rowInd = 0; rowInd <= inDims[0] - 3; rowInd++) {
        bwout_data[rowInd + 1] = lut[(((((bw_data[rowInd] << 3) +
          (bw_data[rowInd + 1] << 4)) + (bw_data[rowInd + 2] << 5)) +
          (bw_data[rowInd + bw_size[0]] << 6)) + (bw_data[(rowInd + bw_size[0])
          + 1] << 7)) + (bw_data[(rowInd + bw_size[0]) + 2] << 8)];
      }

      /*  process the first column last row element */
      bwout_data[inDims[0] - 1] = lut[(((bw_data[inDims[0] - 2] << 3) +
        (bw_data[inDims[0] - 1] << 4)) + (bw_data[(inDims[0] + bw_size[0]) - 2] <<
        6)) + (bw_data[(inDims[0] + bw_size[0]) - 1] << 7)];

      /*  process second column to last but one column------------------------- */
      for (colInd = 1; colInd - 1 <= inDims[1] - 3; colInd++) {
        /*  process first row element */
        bwout_data[bwout_size[0] * colInd] = lut[(((((bw_data[bw_size[0] *
          (colInd - 1)] << 1) + (bw_data[1 + bw_size[0] * (colInd - 1)] << 2)) +
          (bw_data[bw_size[0] * colInd] << 4)) + (bw_data[1 + bw_size[0] *
          colInd] << 5)) + (bw_data[bw_size[0] * (colInd + 1)] << 7)) +
          (bw_data[1 + bw_size[0] * (colInd + 1)] << 8)];

        /*  process second to last but one row for this column */
        for (rowInd = 0; rowInd <= inDims[0] - 3; rowInd++) {
          bwout_data[(rowInd + bwout_size[0] * colInd) + 1] = lut
            [(((((((bw_data[rowInd + bw_size[0] * (colInd - 1)] + (bw_data
                     [(rowInd + bw_size[0] * (colInd - 1)) + 1] << 1)) +
                   (bw_data[(rowInd + bw_size[0] * (colInd - 1)) + 2] << 2)) +
                  (bw_data[rowInd + bw_size[0] * colInd] << 3)) + (bw_data
                  [(rowInd + bw_size[0] * colInd) + 1] << 4)) + (bw_data[(rowInd
                  + bw_size[0] * colInd) + 2] << 5)) + (bw_data[rowInd +
                bw_size[0] * (colInd + 1)] << 6)) + (bw_data[(rowInd + bw_size[0]
                * (colInd + 1)) + 1] << 7)) + (bw_data[(rowInd + bw_size[0] *
            (colInd + 1)) + 2] << 8)];
        }

        /*  process the last row element */
        bwout_data[(inDims[0] + bwout_size[0] * colInd) - 1] = lut[((((bw_data
          [(inDims[0] + bw_size[0] * (colInd - 1)) - 2] + (bw_data[(inDims[0] +
          bw_size[0] * (colInd - 1)) - 1] << 1)) + (bw_data[(inDims[0] +
          bw_size[0] * colInd) - 2] << 3)) + (bw_data[(inDims[0] + bw_size[0] *
          colInd) - 1] << 4)) + (bw_data[(inDims[0] + bw_size[0] * (colInd + 1))
          - 2] << 6)) + (bw_data[(inDims[0] + bw_size[0] * (colInd + 1)) - 1] <<
                         7)];
      }

      /*  end process second column to last but one column--------------------- */
      /*  process last column first row element */
      colInd = inDims[1] - 1;
      bwout_data[iv4[0] * (inDims[1] - 1)] = lut[(((bw_data[bw_size[0] *
        (inDims[1] - 2)] << 1) + (bw_data[1 + bw_size[0] * (inDims[1] - 2)] << 2))
        + (bw_data[bw_size[0] * (inDims[1] - 1)] << 4)) + (bw_data[1 + bw_size[0]
        * (inDims[1] - 1)] << 5)];

      /*  process last column second to last but one element */
      for (rowInd = 0; rowInd <= inDims[0] - 3; rowInd++) {
        bwout_data[(rowInd + bwout_size[0] * colInd) + 1] = lut
          [((((bw_data[rowInd + bw_size[0] * (colInd - 1)] + (bw_data[(rowInd +
                 bw_size[0] * (colInd - 1)) + 1] << 1)) + (bw_data[(rowInd +
                bw_size[0] * (colInd - 1)) + 2] << 2)) + (bw_data[rowInd +
              bw_size[0] * colInd] << 3)) + (bw_data[(rowInd + bw_size[0] *
              colInd) + 1] << 4)) + (bw_data[(rowInd + bw_size[0] * colInd) + 2]
          << 5)];
      }

      /*  process the last column last row element */
      bwout_data[(inDims[0] + iv4[0] * (inDims[1] - 1)) - 1] = lut[((bw_data
        [(inDims[0] + bw_size[0] * (inDims[1] - 2)) - 2] + (bw_data[(inDims[0] +
        bw_size[0] * (inDims[1] - 2)) - 1] << 1)) + (bw_data[(inDims[0] +
        bw_size[0] * (inDims[1] - 1)) - 2] << 3)) + (bw_data[(inDims[0] +
        bw_size[0] * (inDims[1] - 1)) - 1] << 4)];
    } else {
      /*  input is either 1x1, 1xN or Nx1 */
      if (inDims[0] == inDims[1]) {
        /*  input size is 1x1 */
        bwout_data[0] = lut[bw_data[0] << 4];
      }

      if (inDims[0] > 1) {
        /*  input size is Nx1 */
        bwout_data[0] = lut[(bw_data[0] << 4) + (bw_data[1] << 5)];
        for (rowInd = 0; rowInd <= inDims[0] - 3; rowInd++) {
          bwout_data[rowInd + 1] = lut[((bw_data[rowInd] << 3) + (bw_data[rowInd
            + 1] << 4)) + (bw_data[rowInd + 2] << 5)];
        }

        bwout_data[inDims[0] - 1] = lut[(bw_data[inDims[0] - 2] << 3) +
          (bw_data[inDims[0] - 1] << 4)];
      }

      if (inDims[1] > 1) {
        /*  input size is 1xN */
        bwout_data[0] = lut[(bw_data[0] << 4) + (bw_data[bw_size[0]] << 7)];
        for (colInd = 0; colInd <= inDims[1] - 3; colInd++) {
          bwout_data[bwout_size[0] * (colInd + 1)] = lut[((bw_data[bw_size[0] *
            colInd] << 1) + (bw_data[bw_size[0] * (colInd + 1)] << 4)) +
            (bw_data[bw_size[0] * (colInd + 2)] << 7)];
        }

        bwout_data[iv4[0] * (inDims[1] - 1)] = lut[(bw_data[bw_size[0] *
          (inDims[1] - 2)] << 1) + (bw_data[bw_size[0] * (inDims[1] - 1)] << 4)];
      }
    }
  }
}

/*
 * Arguments    : const boolean_T bw_data[]
 *                const int bw_size[2]
 *                boolean_T bwout_data[]
 *                int bwout_size[2]
 * Return Type  : void
 */
void b_algbwmorph(const boolean_T bw_data[], const int bw_size[2], boolean_T
                  bwout_data[], int bwout_size[2])
{
  signed char iv5[2];
  int rowInd;
  signed char inDims[2];
  static const boolean_T lut[512] = { false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    true, true, true, true, true, true, true, true, true, true, true, true, true,
    true, true, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, true, true, true, true,
    true, true, true, true, true, true, true, true, true, true, true, true,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true, true, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, true, true, true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, true,
    true, true, true, true, true, true, true, true, true, true, true, true, true,
    true, true, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, true, true, true, true,
    true, true, true, true, true, true, true, true, true, true, true, true,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true, true, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, true, true, true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, true,
    true, true, true, true, true, true, true, true, true, true, true, true, true,
    true, true, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, true, true, true, true,
    true, true, true, true, true, true, true, true, true, true, true, true,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true, true, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, true, true, true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, true,
    true, true, true, true, true, true, true, true, true, true, true, true, true,
    true, true, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, true, true, true, true,
    true, true, true, true, true, true, true, true, true, true, true, true,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true, true, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, true, true, true, true, true, true, true, true, true, true,
    true, true, true, true, true, true };

  int colInd;
  for (rowInd = 0; rowInd < 2; rowInd++) {
    iv5[rowInd] = (signed char)bw_size[rowInd];
  }

  bwout_size[0] = iv5[0];
  bwout_size[1] = iv5[1];
  if ((bw_size[0] == 0) || (bw_size[1] == 0)) {
  } else {
    for (rowInd = 0; rowInd < 2; rowInd++) {
      inDims[rowInd] = (signed char)bw_size[rowInd];
    }

    if ((inDims[0] >= 2) && (inDims[1] >= 2)) {
      /*  Process a 3x3 neighborhood centered around the pixel being processed.    */
      /*  process the first column first row element */
      bwout_data[0] = lut[(((bw_data[0] << 4) + (bw_data[1] << 5)) +
                           (bw_data[bw_size[0]] << 7)) + (bw_data[1 + bw_size[0]]
        << 8)];

      /*  process the first column interior elements */
      for (rowInd = 0; rowInd <= inDims[0] - 3; rowInd++) {
        bwout_data[rowInd + 1] = lut[(((((bw_data[rowInd] << 3) +
          (bw_data[rowInd + 1] << 4)) + (bw_data[rowInd + 2] << 5)) +
          (bw_data[rowInd + bw_size[0]] << 6)) + (bw_data[(rowInd + bw_size[0])
          + 1] << 7)) + (bw_data[(rowInd + bw_size[0]) + 2] << 8)];
      }

      /*  process the first column last row element */
      bwout_data[inDims[0] - 1] = lut[(((bw_data[inDims[0] - 2] << 3) +
        (bw_data[inDims[0] - 1] << 4)) + (bw_data[(inDims[0] + bw_size[0]) - 2] <<
        6)) + (bw_data[(inDims[0] + bw_size[0]) - 1] << 7)];

      /*  process second column to last but one column------------------------- */
      for (colInd = 1; colInd - 1 <= inDims[1] - 3; colInd++) {
        /*  process first row element */
        bwout_data[bwout_size[0] * colInd] = lut[(((((bw_data[bw_size[0] *
          (colInd - 1)] << 1) + (bw_data[1 + bw_size[0] * (colInd - 1)] << 2)) +
          (bw_data[bw_size[0] * colInd] << 4)) + (bw_data[1 + bw_size[0] *
          colInd] << 5)) + (bw_data[bw_size[0] * (colInd + 1)] << 7)) +
          (bw_data[1 + bw_size[0] * (colInd + 1)] << 8)];

        /*  process second to last but one row for this column */
        for (rowInd = 0; rowInd <= inDims[0] - 3; rowInd++) {
          bwout_data[(rowInd + bwout_size[0] * colInd) + 1] = lut
            [(((((((bw_data[rowInd + bw_size[0] * (colInd - 1)] + (bw_data
                     [(rowInd + bw_size[0] * (colInd - 1)) + 1] << 1)) +
                   (bw_data[(rowInd + bw_size[0] * (colInd - 1)) + 2] << 2)) +
                  (bw_data[rowInd + bw_size[0] * colInd] << 3)) + (bw_data
                  [(rowInd + bw_size[0] * colInd) + 1] << 4)) + (bw_data[(rowInd
                  + bw_size[0] * colInd) + 2] << 5)) + (bw_data[rowInd +
                bw_size[0] * (colInd + 1)] << 6)) + (bw_data[(rowInd + bw_size[0]
                * (colInd + 1)) + 1] << 7)) + (bw_data[(rowInd + bw_size[0] *
            (colInd + 1)) + 2] << 8)];
        }

        /*  process the last row element */
        bwout_data[(inDims[0] + bwout_size[0] * colInd) - 1] = lut[((((bw_data
          [(inDims[0] + bw_size[0] * (colInd - 1)) - 2] + (bw_data[(inDims[0] +
          bw_size[0] * (colInd - 1)) - 1] << 1)) + (bw_data[(inDims[0] +
          bw_size[0] * colInd) - 2] << 3)) + (bw_data[(inDims[0] + bw_size[0] *
          colInd) - 1] << 4)) + (bw_data[(inDims[0] + bw_size[0] * (colInd + 1))
          - 2] << 6)) + (bw_data[(inDims[0] + bw_size[0] * (colInd + 1)) - 1] <<
                         7)];
      }

      /*  end process second column to last but one column--------------------- */
      /*  process last column first row element */
      colInd = inDims[1] - 1;
      bwout_data[iv5[0] * (inDims[1] - 1)] = lut[(((bw_data[bw_size[0] *
        (inDims[1] - 2)] << 1) + (bw_data[1 + bw_size[0] * (inDims[1] - 2)] << 2))
        + (bw_data[bw_size[0] * (inDims[1] - 1)] << 4)) + (bw_data[1 + bw_size[0]
        * (inDims[1] - 1)] << 5)];

      /*  process last column second to last but one element */
      for (rowInd = 0; rowInd <= inDims[0] - 3; rowInd++) {
        bwout_data[(rowInd + bwout_size[0] * colInd) + 1] = lut
          [((((bw_data[rowInd + bw_size[0] * (colInd - 1)] + (bw_data[(rowInd +
                 bw_size[0] * (colInd - 1)) + 1] << 1)) + (bw_data[(rowInd +
                bw_size[0] * (colInd - 1)) + 2] << 2)) + (bw_data[rowInd +
              bw_size[0] * colInd] << 3)) + (bw_data[(rowInd + bw_size[0] *
              colInd) + 1] << 4)) + (bw_data[(rowInd + bw_size[0] * colInd) + 2]
          << 5)];
      }

      /*  process the last column last row element */
      bwout_data[(inDims[0] + iv5[0] * (inDims[1] - 1)) - 1] = lut[((bw_data
        [(inDims[0] + bw_size[0] * (inDims[1] - 2)) - 2] + (bw_data[(inDims[0] +
        bw_size[0] * (inDims[1] - 2)) - 1] << 1)) + (bw_data[(inDims[0] +
        bw_size[0] * (inDims[1] - 1)) - 2] << 3)) + (bw_data[(inDims[0] +
        bw_size[0] * (inDims[1] - 1)) - 1] << 4)];
    } else {
      /*  input is either 1x1, 1xN or Nx1 */
      if (inDims[0] == inDims[1]) {
        /*  input size is 1x1 */
        bwout_data[0] = lut[bw_data[0] << 4];
      }

      if (inDims[0] > 1) {
        /*  input size is Nx1 */
        bwout_data[0] = lut[(bw_data[0] << 4) + (bw_data[1] << 5)];
        for (rowInd = 0; rowInd <= inDims[0] - 3; rowInd++) {
          bwout_data[rowInd + 1] = lut[((bw_data[rowInd] << 3) + (bw_data[rowInd
            + 1] << 4)) + (bw_data[rowInd + 2] << 5)];
        }

        bwout_data[inDims[0] - 1] = lut[(bw_data[inDims[0] - 2] << 3) +
          (bw_data[inDims[0] - 1] << 4)];
      }

      if (inDims[1] > 1) {
        /*  input size is 1xN */
        bwout_data[0] = lut[(bw_data[0] << 4) + (bw_data[bw_size[0]] << 7)];
        for (colInd = 0; colInd <= inDims[1] - 3; colInd++) {
          bwout_data[bwout_size[0] * (colInd + 1)] = lut[((bw_data[bw_size[0] *
            colInd] << 1) + (bw_data[bw_size[0] * (colInd + 1)] << 4)) +
            (bw_data[bw_size[0] * (colInd + 2)] << 7)];
        }

        bwout_data[iv5[0] * (inDims[1] - 1)] = lut[(bw_data[bw_size[0] *
          (inDims[1] - 2)] << 1) + (bw_data[bw_size[0] * (inDims[1] - 1)] << 4)];
      }
    }
  }
}

/*
 * File trailer for algbwmorph.c
 *
 * [EOF]
 */
