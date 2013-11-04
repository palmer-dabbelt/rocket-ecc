#include "modMultiply.h"

void modMultiply_t::init ( bool rand_init ) {
  if (rand_init) modMultiply__op1Mod.randomize();
  if (rand_init) modMultiply__flag1.randomize();
  if (rand_init) modMultiply__op2Mod.randomize();
  if (rand_init) modMultiply__modulo.randomize();
  if (rand_init) modMultiply__flag2.randomize();
  if (rand_init) modMultiply__state.randomize();
  if (rand_init) modMultiply__product.randomize();
}
void modMultiply_t::clock_lo ( dat_t<1> reset ) {
  val_t T0__w0;
  T0__w0 = modMultiply__state.values[0] == 0x3L;
  { modMultiply__io_control_resp_val.values[0] = T0__w0; }
  val_t T1__w0;
  T1__w0 = modMultiply__state.values[0] == 0x0L;
  val_t T2__w0;
  { T2__w0 = T1__w0&&modMultiply__io_control_req_val.values[0]; }
  val_t T3__w0, T3__w1, T3__w2, T3__w3;
  { val_t __mask = -T2__w0; T3__w0 = modMultiply__op1Mod.values[0] ^ ((modMultiply__op1Mod.values[0] ^ modMultiply__io_control_req_op1.values[0]) & __mask); T3__w1 = modMultiply__op1Mod.values[1] ^ ((modMultiply__op1Mod.values[1] ^ modMultiply__io_control_req_op1.values[1]) & __mask); T3__w2 = modMultiply__op1Mod.values[2] ^ ((modMultiply__op1Mod.values[2] ^ modMultiply__io_control_req_op1.values[2]) & __mask); T3__w3 = modMultiply__op1Mod.values[3] ^ ((modMultiply__op1Mod.values[3] ^ modMultiply__io_control_req_op1.values[3]) & __mask); }
  val_t T4__w0, T4__w1, T4__w2, T4__w3;
  { T4__w0 = modMultiply__op1Mod.values[0]-modMultiply__modulo.values[0]; val_t __c = modMultiply__op1Mod.values[0]-modMultiply__modulo.values[0] > modMultiply__op1Mod.values[0]; T4__w1 = modMultiply__op1Mod.values[1]-modMultiply__modulo.values[1]-__c; __c = modMultiply__op1Mod.values[1]-modMultiply__modulo.values[1] > modMultiply__op1Mod.values[1] || modMultiply__op1Mod.values[1]-modMultiply__modulo.values[1] < T4__w1; T4__w2 = modMultiply__op1Mod.values[2]-modMultiply__modulo.values[2]-__c; __c = modMultiply__op1Mod.values[2]-modMultiply__modulo.values[2] > modMultiply__op1Mod.values[2] || modMultiply__op1Mod.values[2]-modMultiply__modulo.values[2] < T4__w2; T4__w3 = modMultiply__op1Mod.values[3]-modMultiply__modulo.values[3]-__c; }
  val_t T5__w0;
  T5__w0 = (((modMultiply__op1Mod.values[0]>=modMultiply__modulo.values[0]) & modMultiply__op1Mod.values[1] == modMultiply__modulo.values[1] || modMultiply__op1Mod.values[1]>modMultiply__modulo.values[1]) & modMultiply__op1Mod.values[2] == modMultiply__modulo.values[2] || modMultiply__op1Mod.values[2]>modMultiply__modulo.values[2]) & modMultiply__op1Mod.values[3] == modMultiply__modulo.values[3] || modMultiply__op1Mod.values[3]>modMultiply__modulo.values[3];
  val_t T6__w0;
  T6__w0 = modMultiply__state.values[0] == 0x1L;
  val_t T7__w0;
  { T7__w0 = T6__w0&&T5__w0; }
  val_t T8__w0, T8__w1, T8__w2, T8__w3;
  { val_t __mask = -T7__w0; T8__w0 = T3__w0 ^ ((T3__w0 ^ T4__w0) & __mask); T8__w1 = T3__w1 ^ ((T3__w1 ^ T4__w1) & __mask); T8__w2 = T3__w2 ^ ((T3__w2 ^ T4__w2) & __mask); T8__w3 = T3__w3 ^ ((T3__w3 ^ T4__w3) & __mask); }
  { modMultiply__op1Mod_shadow.values[0] = T8__w0; modMultiply__op1Mod_shadow.values[1] = T8__w1; modMultiply__op1Mod_shadow.values[2] = T8__w2; modMultiply__op1Mod_shadow.values[3] = T8__w3; }
  val_t T9__w0;
  T9__w0 = !T5__w0;
  val_t T10__w0;
  { T10__w0 = T6__w0&&T9__w0; }
  val_t T11__w0;
  { val_t __mask = -T10__w0; T11__w0 = modMultiply__flag1.values[0] ^ ((modMultiply__flag1.values[0] ^ 0x1L) & __mask); }
  { modMultiply__flag1_shadow.values[0] = T11__w0; }
  val_t T12__w0, T12__w1, T12__w2, T12__w3;
  { val_t __mask = -T2__w0; T12__w0 = modMultiply__op2Mod.values[0] ^ ((modMultiply__op2Mod.values[0] ^ modMultiply__io_control_req_op2.values[0]) & __mask); T12__w1 = modMultiply__op2Mod.values[1] ^ ((modMultiply__op2Mod.values[1] ^ modMultiply__io_control_req_op2.values[1]) & __mask); T12__w2 = modMultiply__op2Mod.values[2] ^ ((modMultiply__op2Mod.values[2] ^ modMultiply__io_control_req_op2.values[2]) & __mask); T12__w3 = modMultiply__op2Mod.values[3] ^ ((modMultiply__op2Mod.values[3] ^ modMultiply__io_control_req_op2.values[3]) & __mask); }
  val_t T13__w0, T13__w1, T13__w2, T13__w3;
  { T13__w0 = modMultiply__op2Mod.values[0]-modMultiply__modulo.values[0]; val_t __c = modMultiply__op2Mod.values[0]-modMultiply__modulo.values[0] > modMultiply__op2Mod.values[0]; T13__w1 = modMultiply__op2Mod.values[1]-modMultiply__modulo.values[1]-__c; __c = modMultiply__op2Mod.values[1]-modMultiply__modulo.values[1] > modMultiply__op2Mod.values[1] || modMultiply__op2Mod.values[1]-modMultiply__modulo.values[1] < T13__w1; T13__w2 = modMultiply__op2Mod.values[2]-modMultiply__modulo.values[2]-__c; __c = modMultiply__op2Mod.values[2]-modMultiply__modulo.values[2] > modMultiply__op2Mod.values[2] || modMultiply__op2Mod.values[2]-modMultiply__modulo.values[2] < T13__w2; T13__w3 = modMultiply__op2Mod.values[3]-modMultiply__modulo.values[3]-__c; }
  val_t T14__w0;
  T14__w0 = (((modMultiply__op2Mod.values[0]>=modMultiply__modulo.values[0]) & modMultiply__op2Mod.values[1] == modMultiply__modulo.values[1] || modMultiply__op2Mod.values[1]>modMultiply__modulo.values[1]) & modMultiply__op2Mod.values[2] == modMultiply__modulo.values[2] || modMultiply__op2Mod.values[2]>modMultiply__modulo.values[2]) & modMultiply__op2Mod.values[3] == modMultiply__modulo.values[3] || modMultiply__op2Mod.values[3]>modMultiply__modulo.values[3];
  val_t T15__w0;
  { T15__w0 = T6__w0&&T14__w0; }
  val_t T16__w0, T16__w1, T16__w2, T16__w3;
  { val_t __mask = -T15__w0; T16__w0 = T12__w0 ^ ((T12__w0 ^ T13__w0) & __mask); T16__w1 = T12__w1 ^ ((T12__w1 ^ T13__w1) & __mask); T16__w2 = T12__w2 ^ ((T12__w2 ^ T13__w2) & __mask); T16__w3 = T12__w3 ^ ((T12__w3 ^ T13__w3) & __mask); }
  { modMultiply__op2Mod_shadow.values[0] = T16__w0; modMultiply__op2Mod_shadow.values[1] = T16__w1; modMultiply__op2Mod_shadow.values[2] = T16__w2; modMultiply__op2Mod_shadow.values[3] = T16__w3; }
  val_t T17__w0, T17__w1, T17__w2, T17__w3;
  { val_t __mask = -T2__w0; T17__w0 = modMultiply__modulo.values[0] ^ ((modMultiply__modulo.values[0] ^ modMultiply__io_control_req_modulo.values[0]) & __mask); T17__w1 = modMultiply__modulo.values[1] ^ ((modMultiply__modulo.values[1] ^ modMultiply__io_control_req_modulo.values[1]) & __mask); T17__w2 = modMultiply__modulo.values[2] ^ ((modMultiply__modulo.values[2] ^ modMultiply__io_control_req_modulo.values[2]) & __mask); T17__w3 = modMultiply__modulo.values[3] ^ ((modMultiply__modulo.values[3] ^ modMultiply__io_control_req_modulo.values[3]) & __mask); }
  { modMultiply__modulo_shadow.values[0] = T17__w0; modMultiply__modulo_shadow.values[1] = T17__w1; modMultiply__modulo_shadow.values[2] = T17__w2; modMultiply__modulo_shadow.values[3] = T17__w3; }
  val_t T18__w0;
  T18__w0 = !T14__w0;
  val_t T19__w0;
  { T19__w0 = T6__w0&&T18__w0; }
  val_t T20__w0;
  { val_t __mask = -T19__w0; T20__w0 = modMultiply__flag2.values[0] ^ ((modMultiply__flag2.values[0] ^ 0x1L) & __mask); }
  { modMultiply__flag2_shadow.values[0] = T20__w0; }
  val_t T21__w0;
  { val_t __mask = -T2__w0; T21__w0 = modMultiply__state.values[0] ^ ((modMultiply__state.values[0] ^ 0x1L) & __mask); }
  val_t T22__w0;
  { T22__w0 = modMultiply__flag1.values[0]&modMultiply__flag2.values[0]; }
  val_t T23__w0;
  { T23__w0 = T6__w0&&T22__w0; }
  val_t T24__w0;
  { val_t __mask = -T23__w0; T24__w0 = T21__w0 ^ ((T21__w0 ^ 0x2L) & __mask); }
  val_t T25__w0, T25__w1, T25__w2, T25__w3, T25__w4, T25__w5, T25__w6, T25__w7;
  { T25__w0 = modMultiply__modulo.values[0]; T25__w1 = modMultiply__modulo.values[1]; T25__w2 = modMultiply__modulo.values[2]; T25__w3 = modMultiply__modulo.values[3]; T25__w4 = 0x0L; T25__w5 = 0L; T25__w6 = 0L; T25__w7 = 0L; }
  val_t T26__w0;
  T26__w0 = (((((((modMultiply__product.values[0]>=T25__w0) & modMultiply__product.values[1] == T25__w1 || modMultiply__product.values[1]>T25__w1) & modMultiply__product.values[2] == T25__w2 || modMultiply__product.values[2]>T25__w2) & modMultiply__product.values[3] == T25__w3 || modMultiply__product.values[3]>T25__w3) & modMultiply__product.values[4] == T25__w4 || modMultiply__product.values[4]>T25__w4) & modMultiply__product.values[5] == T25__w5 || modMultiply__product.values[5]>T25__w5) & modMultiply__product.values[6] == T25__w6 || modMultiply__product.values[6]>T25__w6) & modMultiply__product.values[7] == T25__w7 || modMultiply__product.values[7]>T25__w7;
  val_t T27__w0;
  T27__w0 = !T26__w0;
  val_t T28__w0;
  T28__w0 = modMultiply__state.values[0] == 0x2L;
  val_t T29__w0;
  { T29__w0 = T28__w0&&T27__w0; }
  val_t T30__w0;
  { val_t __mask = -T29__w0; T30__w0 = T24__w0 ^ ((T24__w0 ^ 0x3L) & __mask); }
  val_t T31__w0;
  T31__w0 = modMultiply__state.values[0] == 0x3L;
  val_t T32__w0;
  { val_t __mask = -T31__w0; T32__w0 = T30__w0 ^ ((T30__w0 ^ 0x0L) & __mask); }
  { modMultiply__state_shadow.values[0] = T32__w0; }
  val_t T33__w0, T33__w1, T33__w2, T33__w3, T33__w4, T33__w5, T33__w6, T33__w7;
  { val_t __mask = -T2__w0; T33__w0 = modMultiply__product.values[0] ^ ((modMultiply__product.values[0] ^ 0x0L) & __mask); T33__w1 = modMultiply__product.values[1] ^ ((modMultiply__product.values[1] ^ 0L) & __mask); T33__w2 = modMultiply__product.values[2] ^ ((modMultiply__product.values[2] ^ 0L) & __mask); T33__w3 = modMultiply__product.values[3] ^ ((modMultiply__product.values[3] ^ 0L) & __mask); T33__w4 = modMultiply__product.values[4] ^ ((modMultiply__product.values[4] ^ 0L) & __mask); T33__w5 = modMultiply__product.values[5] ^ ((modMultiply__product.values[5] ^ 0L) & __mask); T33__w6 = modMultiply__product.values[6] ^ ((modMultiply__product.values[6] ^ 0L) & __mask); T33__w7 = modMultiply__product.values[7] ^ ((modMultiply__product.values[7] ^ 0L) & __mask); }
  val_t T34__w0, T34__w1, T34__w2, T34__w3, T34__w4, T34__w5, T34__w6, T34__w7;
  { val_t __d[8]; val_t __x[4]; __x[0] = modMultiply__op1Mod.values[0]; __x[1] = modMultiply__op1Mod.values[1]; __x[2] = modMultiply__op1Mod.values[2]; __x[3] = modMultiply__op1Mod.values[3]; val_t __y[4]; __y[0] = modMultiply__op2Mod.values[0]; __y[1] = modMultiply__op2Mod.values[1]; __y[2] = modMultiply__op2Mod.values[2]; __y[3] = modMultiply__op2Mod.values[3]; mul_n(__d, __x, __y, 512, 256, 256); T34__w0 = __d[0]; T34__w1 = __d[1]; T34__w2 = __d[2]; T34__w3 = __d[3]; T34__w4 = __d[4]; T34__w5 = __d[5]; T34__w6 = __d[6]; T34__w7 = __d[7]; }
  val_t T35__w0, T35__w1, T35__w2, T35__w3, T35__w4, T35__w5, T35__w6, T35__w7;
  { val_t __mask = -T23__w0; T35__w0 = T33__w0 ^ ((T33__w0 ^ T34__w0) & __mask); T35__w1 = T33__w1 ^ ((T33__w1 ^ T34__w1) & __mask); T35__w2 = T33__w2 ^ ((T33__w2 ^ T34__w2) & __mask); T35__w3 = T33__w3 ^ ((T33__w3 ^ T34__w3) & __mask); T35__w4 = T33__w4 ^ ((T33__w4 ^ T34__w4) & __mask); T35__w5 = T33__w5 ^ ((T33__w5 ^ T34__w5) & __mask); T35__w6 = T33__w6 ^ ((T33__w6 ^ T34__w6) & __mask); T35__w7 = T33__w7 ^ ((T33__w7 ^ T34__w7) & __mask); }
  val_t T36__w0, T36__w1, T36__w2, T36__w3, T36__w4, T36__w5, T36__w6, T36__w7;
  { T36__w0 = modMultiply__modulo.values[0]; T36__w1 = modMultiply__modulo.values[1]; T36__w2 = modMultiply__modulo.values[2]; T36__w3 = modMultiply__modulo.values[3]; T36__w4 = 0x0L; T36__w5 = 0L; T36__w6 = 0L; T36__w7 = 0L; }
  val_t T37__w0, T37__w1, T37__w2, T37__w3, T37__w4, T37__w5, T37__w6, T37__w7;
  { T37__w0 = modMultiply__product.values[0]-T36__w0; val_t __c = modMultiply__product.values[0]-T36__w0 > modMultiply__product.values[0]; T37__w1 = modMultiply__product.values[1]-T36__w1-__c; __c = modMultiply__product.values[1]-T36__w1 > modMultiply__product.values[1] || modMultiply__product.values[1]-T36__w1 < T37__w1; T37__w2 = modMultiply__product.values[2]-T36__w2-__c; __c = modMultiply__product.values[2]-T36__w2 > modMultiply__product.values[2] || modMultiply__product.values[2]-T36__w2 < T37__w2; T37__w3 = modMultiply__product.values[3]-T36__w3-__c; __c = modMultiply__product.values[3]-T36__w3 > modMultiply__product.values[3] || modMultiply__product.values[3]-T36__w3 < T37__w3; T37__w4 = modMultiply__product.values[4]-T36__w4-__c; __c = modMultiply__product.values[4]-T36__w4 > modMultiply__product.values[4] || modMultiply__product.values[4]-T36__w4 < T37__w4; T37__w5 = modMultiply__product.values[5]-T36__w5-__c; __c = modMultiply__product.values[5]-T36__w5 > modMultiply__product.values[5] || modMultiply__product.values[5]-T36__w5 < T37__w5; T37__w6 = modMultiply__product.values[6]-T36__w6-__c; __c = modMultiply__product.values[6]-T36__w6 > modMultiply__product.values[6] || modMultiply__product.values[6]-T36__w6 < T37__w6; T37__w7 = modMultiply__product.values[7]-T36__w7-__c; }
  val_t T38__w0;
  { T38__w0 = T28__w0&&T26__w0; }
  val_t T39__w0, T39__w1, T39__w2, T39__w3, T39__w4, T39__w5, T39__w6, T39__w7;
  { val_t __mask = -T38__w0; T39__w0 = T35__w0 ^ ((T35__w0 ^ T37__w0) & __mask); T39__w1 = T35__w1 ^ ((T35__w1 ^ T37__w1) & __mask); T39__w2 = T35__w2 ^ ((T35__w2 ^ T37__w2) & __mask); T39__w3 = T35__w3 ^ ((T35__w3 ^ T37__w3) & __mask); T39__w4 = T35__w4 ^ ((T35__w4 ^ T37__w4) & __mask); T39__w5 = T35__w5 ^ ((T35__w5 ^ T37__w5) & __mask); T39__w6 = T35__w6 ^ ((T35__w6 ^ T37__w6) & __mask); T39__w7 = T35__w7 ^ ((T35__w7 ^ T37__w7) & __mask); }
  { modMultiply__product_shadow.values[0] = T39__w0; modMultiply__product_shadow.values[1] = T39__w1; modMultiply__product_shadow.values[2] = T39__w2; modMultiply__product_shadow.values[3] = T39__w3; modMultiply__product_shadow.values[4] = T39__w4; modMultiply__product_shadow.values[5] = T39__w5; modMultiply__product_shadow.values[6] = T39__w6; modMultiply__product_shadow.values[7] = T39__w7; }
  val_t T40__w0, T40__w1, T40__w2, T40__w3;
  { T40__w0 = modMultiply__product.values[0]; T40__w1 = modMultiply__product.values[1]; T40__w2 = modMultiply__product.values[2]; T40__w3 = modMultiply__product.values[3]; }
  val_t T41__w0, T41__w1, T41__w2, T41__w3;
  { val_t __mask = -T31__w0; T41__w0 = 0x0L ^ ((0x0L ^ T40__w0) & __mask); T41__w1 = 0L ^ ((0L ^ T40__w1) & __mask); T41__w2 = 0L ^ ((0L ^ T40__w2) & __mask); T41__w3 = 0L ^ ((0L ^ T40__w3) & __mask); }
  { modMultiply__io_control_resp_data.values[0] = T41__w0; modMultiply__io_control_resp_data.values[1] = T41__w1; modMultiply__io_control_resp_data.values[2] = T41__w2; modMultiply__io_control_resp_data.values[3] = T41__w3; }
}
void modMultiply_t::clock_hi ( dat_t<1> reset ) {
  modMultiply__op1Mod = modMultiply__op1Mod_shadow;
  modMultiply__flag1 = modMultiply__flag1_shadow;
  modMultiply__op2Mod = modMultiply__op2Mod_shadow;
  modMultiply__modulo = modMultiply__modulo_shadow;
  modMultiply__flag2 = modMultiply__flag2_shadow;
  modMultiply__state = modMultiply__state_shadow;
  modMultiply__product = modMultiply__product_shadow;
}
int modMultiply_t::clock ( dat_t<1> reset ) {
  uint32_t min = ((uint32_t)1<<31)-1;
  if (clk_cnt < min) min = clk_cnt;
  clk_cnt-=min;
  if (clk_cnt == 0) clock_lo( reset );
  if (clk_cnt == 0) clock_hi( reset );
  if (clk_cnt == 0) clk_cnt = clk-1;
  return min;
}
void modMultiply_t::print ( FILE* f ) {
}
bool modMultiply_t::scan ( FILE* f ) {
  return(!feof(f));
}
void modMultiply_t::dump(FILE *f, int t) {
}
