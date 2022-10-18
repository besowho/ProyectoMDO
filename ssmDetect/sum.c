/*
 * File: sum.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ssmDetect.h"
#include "sum.h"

/* Function Definitions */

/*
 * Arguments    : const double x[10000]
 *                double y[2500]
 * Return Type  : void
 */
void b_sum(const double x[10000], double y[2500])
{
  int iy;
  int ixstart;
  int j;
  int ix;
  double s;
  int k;
  iy = -1;
  ixstart = -1;
  for (j = 0; j < 2500; j++) {
    ixstart++;
    ix = ixstart;
    s = x[ixstart];
    for (k = 0; k < 3; k++) {
      ix += 2500;
      s += x[ix];
    }

    iy++;
    y[iy] = s;
  }
}

/*
 * Arguments    : const double x[10000]
 *                double y[2500]
 * Return Type  : void
 */
void c_sum(const double x[10000], double y[2500])
{
  int ix;
  int iy;
  int i;
  int ixstart;
  double s;
  ix = -1;
  iy = -1;
  for (i = 0; i < 2500; i++) {
    ixstart = ix + 1;
    ix++;
    s = x[ixstart];
    for (ixstart = 0; ixstart < 3; ixstart++) {
      ix++;
      s += x[ix];
    }

    iy++;
    y[iy] = s;
  }
}

/*
 * Arguments    : const double x[10000]
 *                double y[200]
 * Return Type  : void
 */
void d_sum(const double x[10000], double y[200])
{
  int ix;
  int iy;
  int i;
  int ixstart;
  double s;
  ix = -1;
  iy = -1;
  for (i = 0; i < 200; i++) {
    ixstart = ix + 1;
    ix++;
    s = x[ixstart];
    for (ixstart = 0; ixstart < 49; ixstart++) {
      ix++;
      s += x[ix];
    }

    iy++;
    y[iy] = s;
  }
}

/*
 * Arguments    : const double x[200]
 *                double y[4]
 * Return Type  : void
 */
void e_sum(const double x[200], double y[4])
{
  int ix;
  int iy;
  int i;
  int ixstart;
  double s;
  ix = -1;
  iy = -1;
  for (i = 0; i < 4; i++) {
    ixstart = ix + 1;
    ix++;
    s = x[ixstart];
    for (ixstart = 0; ixstart < 49; ixstart++) {
      ix++;
      s += x[ix];
    }

    iy++;
    y[iy] = s;
  }
}

/*
 * Arguments    : const double x[4]
 * Return Type  : double
 */
double f_sum(const double x[4])
{
  double y;
  int k;
  y = x[0];
  for (k = 0; k < 3; k++) {
    y += x[k + 1];
  }

  return y;
}

/*
 * Arguments    : const double x[12500]
 *                double y[5]
 * Return Type  : void
 */
void g_sum(const double x[12500], double y[5])
{
  int iy;
  int ixstart;
  int j;
  int ix;
  double s;
  int k;
  iy = -1;
  ixstart = -1;
  for (j = 0; j < 5; j++) {
    ixstart++;
    ix = ixstart;
    s = x[ixstart];
    for (k = 0; k < 2499; k++) {
      ix += 5;
      s += x[ix];
    }

    iy++;
    y[iy] = s;
  }
}

/*
 * Arguments    : const double x[2500]
 * Return Type  : double
 */
double h_sum(const double x[2500])
{
  double y;
  int k;
  y = x[0];
  for (k = 0; k < 2499; k++) {
    y += x[k + 1];
  }

  return y;
}

/*
 * Arguments    : const boolean_T x_data[]
 *                const int x_size[1]
 * Return Type  : double
 */
double i_sum(const boolean_T x_data[], const int x_size[1])
{
  double y;
  int k;
  if (x_size[0] == 0) {
    y = 0.0;
  } else {
    y = x_data[0];
    for (k = 2; k <= x_size[0]; k++) {
      y += (double)x_data[k - 1];
    }
  }

  return y;
}

/*
 * Arguments    : const double x_data[]
 *                const int x_size[2]
 * Return Type  : double
 */
double j_sum(const double x_data[], const int x_size[2])
{
  double y;
  int k;
  if (x_size[1] == 0) {
    y = 0.0;
  } else {
    y = x_data[0];
    for (k = 2; k <= x_size[1]; k++) {
      y += x_data[k - 1];
    }
  }

  return y;
}

/*
 * Arguments    : const double x[12500]
 *                double y[2500]
 * Return Type  : void
 */
void sum(const double x[12500], double y[2500])
{
  int iy;
  int ixstart;
  int j;
  int ix;
  double s;
  int k;
  iy = -1;
  ixstart = -1;
  for (j = 0; j < 2500; j++) {
    ixstart++;
    ix = ixstart;
    s = x[ixstart];
    for (k = 0; k < 4; k++) {
      ix += 2500;
      s += x[ix];
    }

    iy++;
    y[iy] = s;
  }
}

/*
 * File trailer for sum.c
 *
 * [EOF]
 */
