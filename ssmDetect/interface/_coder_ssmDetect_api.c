/*
 * File: _coder_ssmDetect_api.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 04-Mar-2021 10:19:22
 */

/* Include Files */
#include "_coder_ssmDetect_api.h"

/* Function Declarations */
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *detector_state,
  const char_T *identifier, struct0_T *y);
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, struct0_T *y);
static boolean_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId);
static Colorspace d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId);
static real_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, struct1_T y[3]);
static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[5]);
static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[25]);
static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[2]);
static void j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[5000]);
static void k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[10000]);
static void l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[400]);
static void m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, struct2_T y[20]);
static void n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[4]);
static void o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[7500]);
static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const struct0_T *u);
static const mxArray *b_emlrt_marshallOut(const struct1_T u[3]);
static boolean_T p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId);
static real_T q_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static void r_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[5]);
static void s_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[25]);
static void t_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[2]);
static void u_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[5000]);
static void v_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[10000]);
static void w_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[400]);
static void x_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[4]);
static void y_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[7500]);

/* Function Definitions */

/*
 * Arguments    : emlrtContext *aContext
 * Return Type  : void
 */
void ssmDetect_initialize(emlrtContext *aContext)
{
  emlrtStack st = { NULL, NULL, NULL };

  emlrtCreateRootTLS(&emlrtRootTLSGlobal, aContext, NULL, 1);
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void ssmDetect_terminate(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void ssmDetect_atexit(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  ssmDetect_xil_terminate();
}

/*
 * Arguments    : const mxArray * const prhs[1]
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void ssmDetect_api(const mxArray * const prhs[1], const mxArray *plhs[1])
{
  struct0_T detector_state;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "detector_state", &detector_state);

  /* Invoke the target function */
  ssmDetect(&detector_state);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(&st, &detector_state);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *detector_state
 *                const char_T *identifier
 *                struct0_T *y
 * Return Type  : void
 */
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *detector_state,
  const char_T *identifier, struct0_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  b_emlrt_marshallIn(sp, emlrtAlias(detector_state), &thisId, y);
  emlrtDestroyArray(&detector_state);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                struct0_T *y
 * Return Type  : void
 */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, struct0_T *y)
{
  emlrtMsgIdentifier thisId;
  static const char * fieldNames[16] = { "use_prior_on_mixture",
    "use_uniform_component", "colorspace", "em_min_likelihood_delta",
    "em_max_steps", "is_initialized", "prior_mixture", "current_mixture",
    "em_image_size", "spatial_data", "PI_i", "sel_xy", "num_points", "objects",
    "num_objects", "Im_in" };

  thisId.fParent = parentId;
  emlrtCheckStructR2012b(sp, parentId, u, 16, fieldNames, 0U, 0);
  thisId.fIdentifier = "use_prior_on_mixture";
  y->use_prior_on_mixture = c_emlrt_marshallIn(sp, emlrtAlias
    (emlrtGetFieldR2013a(sp, u, 0, "use_prior_on_mixture")), &thisId);
  thisId.fIdentifier = "use_uniform_component";
  y->use_uniform_component = c_emlrt_marshallIn(sp, emlrtAlias
    (emlrtGetFieldR2013a(sp, u, 0, "use_uniform_component")), &thisId);
  thisId.fIdentifier = "colorspace";
  y->colorspace = d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0,
    "colorspace")), &thisId);
  thisId.fIdentifier = "em_min_likelihood_delta";
  y->em_min_likelihood_delta = e_emlrt_marshallIn(sp, emlrtAlias
    (emlrtGetFieldR2013a(sp, u, 0, "em_min_likelihood_delta")), &thisId);
  thisId.fIdentifier = "em_max_steps";
  y->em_max_steps = e_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u,
    0, "em_max_steps")), &thisId);
  thisId.fIdentifier = "is_initialized";
  y->is_initialized = c_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp,
    u, 0, "is_initialized")), &thisId);
  thisId.fIdentifier = "prior_mixture";
  f_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0,
    "prior_mixture")), &thisId, y->prior_mixture);
  thisId.fIdentifier = "current_mixture";
  f_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0,
    "current_mixture")), &thisId, y->current_mixture);
  thisId.fIdentifier = "em_image_size";
  i_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0,
    "em_image_size")), &thisId, y->em_image_size);
  thisId.fIdentifier = "spatial_data";
  j_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "spatial_data")),
                     &thisId, y->spatial_data);
  thisId.fIdentifier = "PI_i";
  k_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "PI_i")),
                     &thisId, y->PI_i);
  thisId.fIdentifier = "sel_xy";
  l_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "sel_xy")),
                     &thisId, y->sel_xy);
  thisId.fIdentifier = "num_points";
  y->num_points = e_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0,
    "num_points")), &thisId);
  thisId.fIdentifier = "objects";
  m_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "objects")),
                     &thisId, y->objects);
  thisId.fIdentifier = "num_objects";
  y->num_objects = e_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u,
    0, "num_objects")), &thisId);
  thisId.fIdentifier = "Im_in";
  o_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "Im_in")),
                     &thisId, y->Im_in);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : boolean_T
 */
static boolean_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId)
{
  boolean_T y;
  y = p_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : Colorspace
 */
static Colorspace d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId)
{
  Colorspace y;
  static const int32_T enumValues[5] = { 1, 2, 3, 4, 5 };

  static const char * enumNames[5] = { "hsv", "lab", "rgb", "ycrcb", "ycrs" };

  emlrtCheckEnumR2012b(sp, "Colorspace", 5, enumNames, enumValues);
  emlrtCheckBuiltInR2012b(sp, parentId, u, "Colorspace", false, 0U, 0);
  y = (Colorspace)emlrtGetEnumElementR2009a(u, 0);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T
 */
static real_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = q_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                struct1_T y[3]
 * Return Type  : void
 */
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, struct1_T y[3])
{
  emlrtMsgIdentifier thisId;
  int32_T iv0[1];
  static const char * fieldNames[4] = { "Mu", "Cov", "w", "Prec" };

  int32_T i0;
  thisId.fParent = parentId;
  iv0[0] = 3;
  emlrtCheckStructR2012b(sp, parentId, u, 4, fieldNames, 1U, iv0);
  for (i0 = 0; i0 < 3; i0++) {
    thisId.fIdentifier = "Mu";
    g_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, i0, "Mu")),
                       &thisId, y[i0].Mu);
    thisId.fIdentifier = "Cov";
    h_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, i0, "Cov")),
                       &thisId, y[i0].Cov);
    thisId.fIdentifier = "w";
    y[i0].w = e_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, i0,
      "w")), &thisId);
    thisId.fIdentifier = "Prec";
    h_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, i0, "Prec")),
                       &thisId, y[i0].Prec);
  }

  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real_T y[5]
 * Return Type  : void
 */
static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[5])
{
  r_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real_T y[25]
 * Return Type  : void
 */
static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[25])
{
  s_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real_T y[2]
 * Return Type  : void
 */
static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[2])
{
  t_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real_T y[5000]
 * Return Type  : void
 */
static void j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[5000])
{
  u_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real_T y[10000]
 * Return Type  : void
 */
static void k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[10000])
{
  v_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real_T y[400]
 * Return Type  : void
 */
static void l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[400])
{
  w_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                struct2_T y[20]
 * Return Type  : void
 */
static void m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, struct2_T y[20])
{
  emlrtMsgIdentifier thisId;
  int32_T iv1[1];
  static const char * fieldNames[2] = { "bounding_box", "area" };

  int32_T i1;
  thisId.fParent = parentId;
  iv1[0] = 20;
  emlrtCheckStructR2012b(sp, parentId, u, 2, fieldNames, 1U, iv1);
  for (i1 = 0; i1 < 20; i1++) {
    thisId.fIdentifier = "bounding_box";
    n_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, i1,
      "bounding_box")), &thisId, y[i1].bounding_box);
    thisId.fIdentifier = "area";
    y[i1].area = e_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, i1,
      "area")), &thisId);
  }

  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real_T y[4]
 * Return Type  : void
 */
static void n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[4])
{
  x_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real_T y[7500]
 * Return Type  : void
 */
static void o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[7500])
{
  y_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const struct0_T *u
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const struct0_T *u)
{
  const mxArray *y;
  const mxArray *b_y;
  const mxArray *m0;
  const mxArray *c_y;
  const mxArray *d_y;
  static const int32_T enumValues[5] = { 1, 2, 3, 4, 5 };

  static const char * enumNames[5] = { "hsv", "lab", "rgb", "ycrcb", "ycrs" };

  const mxArray *e_y;
  const mxArray *m1 = NULL;
  const mxArray *f_y;
  const mxArray *g_y;
  const mxArray *h_y;
  const mxArray *i_y;
  static const int32_T iv2[2] = { 1, 2 };

  real_T *pData;
  int32_T i;
  const mxArray *j_y;
  static const int32_T iv3[2] = { 2, 2500 };

  const mxArray *k_y;
  static const int32_T iv4[3] = { 50, 50, 4 };

  const mxArray *l_y;
  static const int32_T iv5[2] = { 2, 200 };

  const mxArray *m_y;
  struct2_T b_u[20];
  const mxArray *n_y;
  int32_T iv6[1];
  int32_T i2;
  const struct2_T *r0;
  real_T c_u[4];
  const mxArray *o_y;
  static const int32_T iv7[2] = { 1, 4 };

  real_T d_u;
  const mxArray *p_y;
  const mxArray *q_y;
  const mxArray *r_y;
  static const int32_T iv8[3] = { 50, 50, 3 };

  y = NULL;
  emlrtAssign(&y, emlrtCreateStructMatrix(1, 1, 0, NULL));
  b_y = NULL;
  m0 = emlrtCreateLogicalScalar(u->use_prior_on_mixture);
  emlrtAssign(&b_y, m0);
  emlrtAddField(y, b_y, "use_prior_on_mixture", 0);
  c_y = NULL;
  m0 = emlrtCreateLogicalScalar(u->use_uniform_component);
  emlrtAssign(&c_y, m0);
  emlrtAddField(y, c_y, "use_uniform_component", 0);
  d_y = NULL;
  emlrtCheckEnumR2012b(sp, "Colorspace", 5, enumNames, enumValues);
  e_y = NULL;
  m0 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)mxGetData(m0) = u->colorspace;
  emlrtAssign(&e_y, m0);
  emlrtAssign(&m1, e_y);
  emlrtAssign(&d_y, emlrtCreateEnumR2012b(sp, "Colorspace", m1));
  emlrtDestroyArray(&m1);
  emlrtAddField(y, d_y, "colorspace", 0);
  f_y = NULL;
  m0 = emlrtCreateDoubleScalar(u->em_min_likelihood_delta);
  emlrtAssign(&f_y, m0);
  emlrtAddField(y, f_y, "em_min_likelihood_delta", 0);
  g_y = NULL;
  m0 = emlrtCreateDoubleScalar(u->em_max_steps);
  emlrtAssign(&g_y, m0);
  emlrtAddField(y, g_y, "em_max_steps", 0);
  h_y = NULL;
  m0 = emlrtCreateLogicalScalar(u->is_initialized);
  emlrtAssign(&h_y, m0);
  emlrtAddField(y, h_y, "is_initialized", 0);
  emlrtAddField(y, b_emlrt_marshallOut(u->prior_mixture), "prior_mixture", 0);
  emlrtAddField(y, b_emlrt_marshallOut(u->current_mixture), "current_mixture", 0);
  i_y = NULL;
  m0 = emlrtCreateNumericArray(2, iv2, mxDOUBLE_CLASS, mxREAL);
  pData = (real_T *)mxGetPr(m0);
  for (i = 0; i < 2; i++) {
    pData[i] = u->em_image_size[i];
  }

  emlrtAssign(&i_y, m0);
  emlrtAddField(y, i_y, "em_image_size", 0);
  j_y = NULL;
  m0 = emlrtCreateNumericArray(2, iv3, mxDOUBLE_CLASS, mxREAL);
  pData = (real_T *)mxGetPr(m0);
  for (i = 0; i < 5000; i++) {
    pData[i] = u->spatial_data[i];
  }

  emlrtAssign(&j_y, m0);
  emlrtAddField(y, j_y, "spatial_data", 0);
  k_y = NULL;
  m0 = emlrtCreateNumericArray(3, iv4, mxDOUBLE_CLASS, mxREAL);
  pData = (real_T *)mxGetPr(m0);
  for (i = 0; i < 10000; i++) {
    pData[i] = u->PI_i[i];
  }

  emlrtAssign(&k_y, m0);
  emlrtAddField(y, k_y, "PI_i", 0);
  l_y = NULL;
  m0 = emlrtCreateNumericArray(2, iv5, mxDOUBLE_CLASS, mxREAL);
  pData = (real_T *)mxGetPr(m0);
  for (i = 0; i < 400; i++) {
    pData[i] = u->sel_xy[i];
  }

  emlrtAssign(&l_y, m0);
  emlrtAddField(y, l_y, "sel_xy", 0);
  m_y = NULL;
  m0 = emlrtCreateDoubleScalar(u->num_points);
  emlrtAssign(&m_y, m0);
  emlrtAddField(y, m_y, "num_points", 0);
  for (i = 0; i < 20; i++) {
    b_u[i] = u->objects[i];
  }

  n_y = NULL;
  iv6[0] = 20;
  emlrtAssign(&n_y, emlrtCreateStructArray(1, iv6, 0, NULL));
  for (i2 = 0; i2 < 20; i2++) {
    r0 = &b_u[i2];
    for (i = 0; i < 4; i++) {
      c_u[i] = r0->bounding_box[i];
    }

    o_y = NULL;
    m0 = emlrtCreateNumericArray(2, iv7, mxDOUBLE_CLASS, mxREAL);
    pData = (real_T *)mxGetPr(m0);
    for (i = 0; i < 4; i++) {
      pData[i] = c_u[i];
    }

    emlrtAssign(&o_y, m0);
    emlrtAddField(n_y, o_y, "bounding_box", i2);
    d_u = r0->area;
    p_y = NULL;
    m0 = emlrtCreateDoubleScalar(d_u);
    emlrtAssign(&p_y, m0);
    emlrtAddField(n_y, p_y, "area", i2);
  }

  emlrtAddField(y, n_y, "objects", 0);
  q_y = NULL;
  m0 = emlrtCreateDoubleScalar(u->num_objects);
  emlrtAssign(&q_y, m0);
  emlrtAddField(y, q_y, "num_objects", 0);
  r_y = NULL;
  m0 = emlrtCreateNumericArray(3, iv8, mxDOUBLE_CLASS, mxREAL);
  pData = (real_T *)mxGetPr(m0);
  for (i = 0; i < 7500; i++) {
    pData[i] = u->Im_in[i];
  }

  emlrtAssign(&r_y, m0);
  emlrtAddField(y, r_y, "Im_in", 0);
  return y;
}

/*
 * Arguments    : const struct1_T u[3]
 * Return Type  : const mxArray *
 */
static const mxArray *b_emlrt_marshallOut(const struct1_T u[3])
{
  const mxArray *y;
  int32_T iv9[1];
  int32_T i3;
  const struct1_T *r1;
  real_T b_u[5];
  int32_T i;
  const mxArray *b_y;
  static const int32_T iv10[1] = { 5 };

  const mxArray *m2;
  real_T *pData;
  real_T c_u[25];
  const mxArray *c_y;
  static const int32_T iv11[2] = { 5, 5 };

  real_T d_u;
  const mxArray *d_y;
  const mxArray *e_y;
  static const int32_T iv12[2] = { 5, 5 };

  y = NULL;
  iv9[0] = 3;
  emlrtAssign(&y, emlrtCreateStructArray(1, iv9, 0, NULL));
  for (i3 = 0; i3 < 3; i3++) {
    r1 = &u[i3];
    for (i = 0; i < 5; i++) {
      b_u[i] = r1->Mu[i];
    }

    b_y = NULL;
    m2 = emlrtCreateNumericArray(1, iv10, mxDOUBLE_CLASS, mxREAL);
    pData = (real_T *)mxGetPr(m2);
    for (i = 0; i < 5; i++) {
      pData[i] = b_u[i];
    }

    emlrtAssign(&b_y, m2);
    emlrtAddField(y, b_y, "Mu", i3);
    for (i = 0; i < 25; i++) {
      c_u[i] = r1->Cov[i];
    }

    c_y = NULL;
    m2 = emlrtCreateNumericArray(2, iv11, mxDOUBLE_CLASS, mxREAL);
    pData = (real_T *)mxGetPr(m2);
    memcpy(&pData[0], &c_u[0], 25U * sizeof(real_T));
    emlrtAssign(&c_y, m2);
    emlrtAddField(y, c_y, "Cov", i3);
    d_u = r1->w;
    d_y = NULL;
    m2 = emlrtCreateDoubleScalar(d_u);
    emlrtAssign(&d_y, m2);
    emlrtAddField(y, d_y, "w", i3);
    for (i = 0; i < 25; i++) {
      c_u[i] = r1->Prec[i];
    }

    e_y = NULL;
    m2 = emlrtCreateNumericArray(2, iv12, mxDOUBLE_CLASS, mxREAL);
    pData = (real_T *)mxGetPr(m2);
    memcpy(&pData[0], &c_u[0], 25U * sizeof(real_T));
    emlrtAssign(&e_y, m2);
    emlrtAddField(y, e_y, "Prec", i3);
  }

  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : boolean_T
 */
static boolean_T p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId)
{
  boolean_T ret;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "logical", false, 0U, 0);
  ret = *mxGetLogicals(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T
 */
static real_T q_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  real_T ret;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, 0);
  ret = *(real_T *)mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real_T ret[5]
 * Return Type  : void
 */
static void r_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[5])
{
  int32_T iv13[1];
  int32_T i4;
  iv13[0] = 5;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 1U, iv13);
  for (i4 = 0; i4 < 5; i4++) {
    ret[i4] = (*(real_T (*)[5])mxGetData(src))[i4];
  }

  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real_T ret[25]
 * Return Type  : void
 */
static void s_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[25])
{
  int32_T iv14[2];
  int32_T i;
  int32_T i5;
  for (i = 0; i < 2; i++) {
    iv14[i] = 5;
  }

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, iv14);
  for (i = 0; i < 5; i++) {
    for (i5 = 0; i5 < 5; i5++) {
      ret[i5 + 5 * i] = (*(real_T (*)[25])mxGetData(src))[i5 + 5 * i];
    }
  }

  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real_T ret[2]
 * Return Type  : void
 */
static void t_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[2])
{
  int32_T iv15[2];
  int32_T i6;
  for (i6 = 0; i6 < 2; i6++) {
    iv15[i6] = 1 + i6;
  }

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, iv15);
  for (i6 = 0; i6 < 2; i6++) {
    ret[i6] = (*(real_T (*)[2])mxGetData(src))[i6];
  }

  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real_T ret[5000]
 * Return Type  : void
 */
static void u_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[5000])
{
  int32_T iv16[2];
  int32_T i7;
  int32_T i8;
  for (i7 = 0; i7 < 2; i7++) {
    iv16[i7] = 2 + 2498 * i7;
  }

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, iv16);
  for (i7 = 0; i7 < 2500; i7++) {
    for (i8 = 0; i8 < 2; i8++) {
      ret[i8 + (i7 << 1)] = (*(real_T (*)[5000])mxGetData(src))[i8 + (i7 << 1)];
    }
  }

  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real_T ret[10000]
 * Return Type  : void
 */
static void v_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[10000])
{
  int32_T iv17[3];
  int32_T i;
  static const int8_T iv18[3] = { 50, 50, 4 };

  int32_T i9;
  int32_T i10;
  for (i = 0; i < 3; i++) {
    iv17[i] = iv18[i];
  }

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 3U, iv17);
  for (i = 0; i < 4; i++) {
    for (i9 = 0; i9 < 50; i9++) {
      for (i10 = 0; i10 < 50; i10++) {
        ret[(i10 + 50 * i9) + 2500 * i] = (*(real_T (*)[10000])mxGetData(src))
          [(i10 + 50 * i9) + 2500 * i];
      }
    }
  }

  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real_T ret[400]
 * Return Type  : void
 */
static void w_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[400])
{
  int32_T iv19[2];
  int32_T i11;
  int32_T i12;
  for (i11 = 0; i11 < 2; i11++) {
    iv19[i11] = 2 + 198 * i11;
  }

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, iv19);
  for (i11 = 0; i11 < 200; i11++) {
    for (i12 = 0; i12 < 2; i12++) {
      ret[i12 + (i11 << 1)] = (*(real_T (*)[400])mxGetData(src))[i12 + (i11 << 1)];
    }
  }

  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real_T ret[4]
 * Return Type  : void
 */
static void x_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[4])
{
  int32_T iv20[2];
  int32_T i13;
  for (i13 = 0; i13 < 2; i13++) {
    iv20[i13] = 1 + 3 * i13;
  }

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, iv20);
  for (i13 = 0; i13 < 4; i13++) {
    ret[i13] = (*(real_T (*)[4])mxGetData(src))[i13];
  }

  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real_T ret[7500]
 * Return Type  : void
 */
static void y_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[7500])
{
  int32_T iv21[3];
  int32_T i;
  static const int8_T iv22[3] = { 50, 50, 3 };

  int32_T i14;
  int32_T i15;
  for (i = 0; i < 3; i++) {
    iv21[i] = iv22[i];
  }

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 3U, iv21);
  for (i = 0; i < 3; i++) {
    for (i14 = 0; i14 < 50; i14++) {
      for (i15 = 0; i15 < 50; i15++) {
        ret[(i15 + 50 * i14) + 2500 * i] = (*(real_T (*)[7500])mxGetData(src))
          [(i15 + 50 * i14) + 2500 * i];
      }
    }
  }

  emlrtDestroyArray(&src);
}

/*
 * File trailer for _coder_ssmDetect_api.c
 *
 * [EOF]
 */
