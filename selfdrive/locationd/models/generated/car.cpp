#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.11.1                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_8827834186464641590) {
   out_8827834186464641590[0] = delta_x[0] + nom_x[0];
   out_8827834186464641590[1] = delta_x[1] + nom_x[1];
   out_8827834186464641590[2] = delta_x[2] + nom_x[2];
   out_8827834186464641590[3] = delta_x[3] + nom_x[3];
   out_8827834186464641590[4] = delta_x[4] + nom_x[4];
   out_8827834186464641590[5] = delta_x[5] + nom_x[5];
   out_8827834186464641590[6] = delta_x[6] + nom_x[6];
   out_8827834186464641590[7] = delta_x[7] + nom_x[7];
   out_8827834186464641590[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4357544145669623999) {
   out_4357544145669623999[0] = -nom_x[0] + true_x[0];
   out_4357544145669623999[1] = -nom_x[1] + true_x[1];
   out_4357544145669623999[2] = -nom_x[2] + true_x[2];
   out_4357544145669623999[3] = -nom_x[3] + true_x[3];
   out_4357544145669623999[4] = -nom_x[4] + true_x[4];
   out_4357544145669623999[5] = -nom_x[5] + true_x[5];
   out_4357544145669623999[6] = -nom_x[6] + true_x[6];
   out_4357544145669623999[7] = -nom_x[7] + true_x[7];
   out_4357544145669623999[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_5054864097630402037) {
   out_5054864097630402037[0] = 1.0;
   out_5054864097630402037[1] = 0;
   out_5054864097630402037[2] = 0;
   out_5054864097630402037[3] = 0;
   out_5054864097630402037[4] = 0;
   out_5054864097630402037[5] = 0;
   out_5054864097630402037[6] = 0;
   out_5054864097630402037[7] = 0;
   out_5054864097630402037[8] = 0;
   out_5054864097630402037[9] = 0;
   out_5054864097630402037[10] = 1.0;
   out_5054864097630402037[11] = 0;
   out_5054864097630402037[12] = 0;
   out_5054864097630402037[13] = 0;
   out_5054864097630402037[14] = 0;
   out_5054864097630402037[15] = 0;
   out_5054864097630402037[16] = 0;
   out_5054864097630402037[17] = 0;
   out_5054864097630402037[18] = 0;
   out_5054864097630402037[19] = 0;
   out_5054864097630402037[20] = 1.0;
   out_5054864097630402037[21] = 0;
   out_5054864097630402037[22] = 0;
   out_5054864097630402037[23] = 0;
   out_5054864097630402037[24] = 0;
   out_5054864097630402037[25] = 0;
   out_5054864097630402037[26] = 0;
   out_5054864097630402037[27] = 0;
   out_5054864097630402037[28] = 0;
   out_5054864097630402037[29] = 0;
   out_5054864097630402037[30] = 1.0;
   out_5054864097630402037[31] = 0;
   out_5054864097630402037[32] = 0;
   out_5054864097630402037[33] = 0;
   out_5054864097630402037[34] = 0;
   out_5054864097630402037[35] = 0;
   out_5054864097630402037[36] = 0;
   out_5054864097630402037[37] = 0;
   out_5054864097630402037[38] = 0;
   out_5054864097630402037[39] = 0;
   out_5054864097630402037[40] = 1.0;
   out_5054864097630402037[41] = 0;
   out_5054864097630402037[42] = 0;
   out_5054864097630402037[43] = 0;
   out_5054864097630402037[44] = 0;
   out_5054864097630402037[45] = 0;
   out_5054864097630402037[46] = 0;
   out_5054864097630402037[47] = 0;
   out_5054864097630402037[48] = 0;
   out_5054864097630402037[49] = 0;
   out_5054864097630402037[50] = 1.0;
   out_5054864097630402037[51] = 0;
   out_5054864097630402037[52] = 0;
   out_5054864097630402037[53] = 0;
   out_5054864097630402037[54] = 0;
   out_5054864097630402037[55] = 0;
   out_5054864097630402037[56] = 0;
   out_5054864097630402037[57] = 0;
   out_5054864097630402037[58] = 0;
   out_5054864097630402037[59] = 0;
   out_5054864097630402037[60] = 1.0;
   out_5054864097630402037[61] = 0;
   out_5054864097630402037[62] = 0;
   out_5054864097630402037[63] = 0;
   out_5054864097630402037[64] = 0;
   out_5054864097630402037[65] = 0;
   out_5054864097630402037[66] = 0;
   out_5054864097630402037[67] = 0;
   out_5054864097630402037[68] = 0;
   out_5054864097630402037[69] = 0;
   out_5054864097630402037[70] = 1.0;
   out_5054864097630402037[71] = 0;
   out_5054864097630402037[72] = 0;
   out_5054864097630402037[73] = 0;
   out_5054864097630402037[74] = 0;
   out_5054864097630402037[75] = 0;
   out_5054864097630402037[76] = 0;
   out_5054864097630402037[77] = 0;
   out_5054864097630402037[78] = 0;
   out_5054864097630402037[79] = 0;
   out_5054864097630402037[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_3794276025868419788) {
   out_3794276025868419788[0] = state[0];
   out_3794276025868419788[1] = state[1];
   out_3794276025868419788[2] = state[2];
   out_3794276025868419788[3] = state[3];
   out_3794276025868419788[4] = state[4];
   out_3794276025868419788[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_3794276025868419788[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_3794276025868419788[7] = state[7];
   out_3794276025868419788[8] = state[8];
}
void F_fun(double *state, double dt, double *out_3600320196893165164) {
   out_3600320196893165164[0] = 1;
   out_3600320196893165164[1] = 0;
   out_3600320196893165164[2] = 0;
   out_3600320196893165164[3] = 0;
   out_3600320196893165164[4] = 0;
   out_3600320196893165164[5] = 0;
   out_3600320196893165164[6] = 0;
   out_3600320196893165164[7] = 0;
   out_3600320196893165164[8] = 0;
   out_3600320196893165164[9] = 0;
   out_3600320196893165164[10] = 1;
   out_3600320196893165164[11] = 0;
   out_3600320196893165164[12] = 0;
   out_3600320196893165164[13] = 0;
   out_3600320196893165164[14] = 0;
   out_3600320196893165164[15] = 0;
   out_3600320196893165164[16] = 0;
   out_3600320196893165164[17] = 0;
   out_3600320196893165164[18] = 0;
   out_3600320196893165164[19] = 0;
   out_3600320196893165164[20] = 1;
   out_3600320196893165164[21] = 0;
   out_3600320196893165164[22] = 0;
   out_3600320196893165164[23] = 0;
   out_3600320196893165164[24] = 0;
   out_3600320196893165164[25] = 0;
   out_3600320196893165164[26] = 0;
   out_3600320196893165164[27] = 0;
   out_3600320196893165164[28] = 0;
   out_3600320196893165164[29] = 0;
   out_3600320196893165164[30] = 1;
   out_3600320196893165164[31] = 0;
   out_3600320196893165164[32] = 0;
   out_3600320196893165164[33] = 0;
   out_3600320196893165164[34] = 0;
   out_3600320196893165164[35] = 0;
   out_3600320196893165164[36] = 0;
   out_3600320196893165164[37] = 0;
   out_3600320196893165164[38] = 0;
   out_3600320196893165164[39] = 0;
   out_3600320196893165164[40] = 1;
   out_3600320196893165164[41] = 0;
   out_3600320196893165164[42] = 0;
   out_3600320196893165164[43] = 0;
   out_3600320196893165164[44] = 0;
   out_3600320196893165164[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_3600320196893165164[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_3600320196893165164[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3600320196893165164[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3600320196893165164[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_3600320196893165164[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_3600320196893165164[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_3600320196893165164[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_3600320196893165164[53] = -9.8000000000000007*dt;
   out_3600320196893165164[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_3600320196893165164[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_3600320196893165164[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3600320196893165164[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3600320196893165164[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_3600320196893165164[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_3600320196893165164[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_3600320196893165164[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3600320196893165164[62] = 0;
   out_3600320196893165164[63] = 0;
   out_3600320196893165164[64] = 0;
   out_3600320196893165164[65] = 0;
   out_3600320196893165164[66] = 0;
   out_3600320196893165164[67] = 0;
   out_3600320196893165164[68] = 0;
   out_3600320196893165164[69] = 0;
   out_3600320196893165164[70] = 1;
   out_3600320196893165164[71] = 0;
   out_3600320196893165164[72] = 0;
   out_3600320196893165164[73] = 0;
   out_3600320196893165164[74] = 0;
   out_3600320196893165164[75] = 0;
   out_3600320196893165164[76] = 0;
   out_3600320196893165164[77] = 0;
   out_3600320196893165164[78] = 0;
   out_3600320196893165164[79] = 0;
   out_3600320196893165164[80] = 1;
}
void h_25(double *state, double *unused, double *out_133870440206676857) {
   out_133870440206676857[0] = state[6];
}
void H_25(double *state, double *unused, double *out_1939961542814685148) {
   out_1939961542814685148[0] = 0;
   out_1939961542814685148[1] = 0;
   out_1939961542814685148[2] = 0;
   out_1939961542814685148[3] = 0;
   out_1939961542814685148[4] = 0;
   out_1939961542814685148[5] = 0;
   out_1939961542814685148[6] = 1;
   out_1939961542814685148[7] = 0;
   out_1939961542814685148[8] = 0;
}
void h_24(double *state, double *unused, double *out_2241976900638027477) {
   out_2241976900638027477[0] = state[4];
   out_2241976900638027477[1] = state[5];
}
void H_24(double *state, double *unused, double *out_232688056190814418) {
   out_232688056190814418[0] = 0;
   out_232688056190814418[1] = 0;
   out_232688056190814418[2] = 0;
   out_232688056190814418[3] = 0;
   out_232688056190814418[4] = 1;
   out_232688056190814418[5] = 0;
   out_232688056190814418[6] = 0;
   out_232688056190814418[7] = 0;
   out_232688056190814418[8] = 0;
   out_232688056190814418[9] = 0;
   out_232688056190814418[10] = 0;
   out_232688056190814418[11] = 0;
   out_232688056190814418[12] = 0;
   out_232688056190814418[13] = 0;
   out_232688056190814418[14] = 1;
   out_232688056190814418[15] = 0;
   out_232688056190814418[16] = 0;
   out_232688056190814418[17] = 0;
}
void h_30(double *state, double *unused, double *out_8630531121470416849) {
   out_8630531121470416849[0] = state[4];
}
void H_30(double *state, double *unused, double *out_4458294501321933775) {
   out_4458294501321933775[0] = 0;
   out_4458294501321933775[1] = 0;
   out_4458294501321933775[2] = 0;
   out_4458294501321933775[3] = 0;
   out_4458294501321933775[4] = 1;
   out_4458294501321933775[5] = 0;
   out_4458294501321933775[6] = 0;
   out_4458294501321933775[7] = 0;
   out_4458294501321933775[8] = 0;
}
void h_26(double *state, double *unused, double *out_5214257831821346833) {
   out_5214257831821346833[0] = state[7];
}
void H_26(double *state, double *unused, double *out_1801541776059371076) {
   out_1801541776059371076[0] = 0;
   out_1801541776059371076[1] = 0;
   out_1801541776059371076[2] = 0;
   out_1801541776059371076[3] = 0;
   out_1801541776059371076[4] = 0;
   out_1801541776059371076[5] = 0;
   out_1801541776059371076[6] = 0;
   out_1801541776059371076[7] = 1;
   out_1801541776059371076[8] = 0;
}
void h_27(double *state, double *unused, double *out_5011019622908970680) {
   out_5011019622908970680[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6681888572505876992) {
   out_6681888572505876992[0] = 0;
   out_6681888572505876992[1] = 0;
   out_6681888572505876992[2] = 0;
   out_6681888572505876992[3] = 1;
   out_6681888572505876992[4] = 0;
   out_6681888572505876992[5] = 0;
   out_6681888572505876992[6] = 0;
   out_6681888572505876992[7] = 0;
   out_6681888572505876992[8] = 0;
}
void h_29(double *state, double *unused, double *out_3417171434825285621) {
   out_3417171434825285621[0] = state[1];
}
void H_29(double *state, double *unused, double *out_4968525845636325959) {
   out_4968525845636325959[0] = 0;
   out_4968525845636325959[1] = 1;
   out_4968525845636325959[2] = 0;
   out_4968525845636325959[3] = 0;
   out_4968525845636325959[4] = 0;
   out_4968525845636325959[5] = 0;
   out_4968525845636325959[6] = 0;
   out_4968525845636325959[7] = 0;
   out_4968525845636325959[8] = 0;
}
void h_28(double *state, double *unused, double *out_4114166344552671977) {
   out_4114166344552671977[0] = state[0];
}
void H_28(double *state, double *unused, double *out_113873171433204615) {
   out_113873171433204615[0] = 1;
   out_113873171433204615[1] = 0;
   out_113873171433204615[2] = 0;
   out_113873171433204615[3] = 0;
   out_113873171433204615[4] = 0;
   out_113873171433204615[5] = 0;
   out_113873171433204615[6] = 0;
   out_113873171433204615[7] = 0;
   out_113873171433204615[8] = 0;
}
void h_31(double *state, double *unused, double *out_6578481571228170128) {
   out_6578481571228170128[0] = state[8];
}
void H_31(double *state, double *unused, double *out_2427749878292722552) {
   out_2427749878292722552[0] = 0;
   out_2427749878292722552[1] = 0;
   out_2427749878292722552[2] = 0;
   out_2427749878292722552[3] = 0;
   out_2427749878292722552[4] = 0;
   out_2427749878292722552[5] = 0;
   out_2427749878292722552[6] = 0;
   out_2427749878292722552[7] = 0;
   out_2427749878292722552[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_8827834186464641590) {
  err_fun(nom_x, delta_x, out_8827834186464641590);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4357544145669623999) {
  inv_err_fun(nom_x, true_x, out_4357544145669623999);
}
void car_H_mod_fun(double *state, double *out_5054864097630402037) {
  H_mod_fun(state, out_5054864097630402037);
}
void car_f_fun(double *state, double dt, double *out_3794276025868419788) {
  f_fun(state,  dt, out_3794276025868419788);
}
void car_F_fun(double *state, double dt, double *out_3600320196893165164) {
  F_fun(state,  dt, out_3600320196893165164);
}
void car_h_25(double *state, double *unused, double *out_133870440206676857) {
  h_25(state, unused, out_133870440206676857);
}
void car_H_25(double *state, double *unused, double *out_1939961542814685148) {
  H_25(state, unused, out_1939961542814685148);
}
void car_h_24(double *state, double *unused, double *out_2241976900638027477) {
  h_24(state, unused, out_2241976900638027477);
}
void car_H_24(double *state, double *unused, double *out_232688056190814418) {
  H_24(state, unused, out_232688056190814418);
}
void car_h_30(double *state, double *unused, double *out_8630531121470416849) {
  h_30(state, unused, out_8630531121470416849);
}
void car_H_30(double *state, double *unused, double *out_4458294501321933775) {
  H_30(state, unused, out_4458294501321933775);
}
void car_h_26(double *state, double *unused, double *out_5214257831821346833) {
  h_26(state, unused, out_5214257831821346833);
}
void car_H_26(double *state, double *unused, double *out_1801541776059371076) {
  H_26(state, unused, out_1801541776059371076);
}
void car_h_27(double *state, double *unused, double *out_5011019622908970680) {
  h_27(state, unused, out_5011019622908970680);
}
void car_H_27(double *state, double *unused, double *out_6681888572505876992) {
  H_27(state, unused, out_6681888572505876992);
}
void car_h_29(double *state, double *unused, double *out_3417171434825285621) {
  h_29(state, unused, out_3417171434825285621);
}
void car_H_29(double *state, double *unused, double *out_4968525845636325959) {
  H_29(state, unused, out_4968525845636325959);
}
void car_h_28(double *state, double *unused, double *out_4114166344552671977) {
  h_28(state, unused, out_4114166344552671977);
}
void car_H_28(double *state, double *unused, double *out_113873171433204615) {
  H_28(state, unused, out_113873171433204615);
}
void car_h_31(double *state, double *unused, double *out_6578481571228170128) {
  h_31(state, unused, out_6578481571228170128);
}
void car_H_31(double *state, double *unused, double *out_2427749878292722552) {
  H_31(state, unused, out_2427749878292722552);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_init(car);
