#include "modInv.h"

void modInv_t::init ( bool rand_init ) {
  if (rand_init) modInv__modulo.randomize();
  if (rand_init) modInv__s2.randomize();
  if (rand_init) modInv__s1.randomize();
  if (rand_init) modInv__z.randomize();
  if (rand_init) modInv__v.randomize();
  if (rand_init) modInv__u.randomize();
  if (rand_init) modInv__state.randomize();
  if (rand_init) modInv__r1.randomize();
}
void modInv_t::clock_lo ( dat_t<1> reset ) {
  val_t T0__w0;
  T0__w0 = modInv__state.values[0] == 0x4L;
  { modInv__io_control_resp_val.values[0] = T0__w0; }
  val_t T1__w0;
  T1__w0 = modInv__state.values[0] == 0x0L;
  val_t T2__w0;
  { T2__w0 = T1__w0&&modInv__io_control_req_val.values[0]; }
  val_t T3__w0, T3__w1, T3__w2, T3__w3;
  { val_t __mask = -T2__w0; T3__w0 = modInv__modulo.values[0] ^ ((modInv__modulo.values[0] ^ modInv__io_control_req_modulo.values[0]) & __mask); T3__w1 = modInv__modulo.values[1] ^ ((modInv__modulo.values[1] ^ modInv__io_control_req_modulo.values[1]) & __mask); T3__w2 = modInv__modulo.values[2] ^ ((modInv__modulo.values[2] ^ modInv__io_control_req_modulo.values[2]) & __mask); T3__w3 = modInv__modulo.values[3] ^ ((modInv__modulo.values[3] ^ modInv__io_control_req_modulo.values[3]) & __mask); }
  { modInv__modulo_shadow.values[0] = T3__w0; modInv__modulo_shadow.values[1] = T3__w1; modInv__modulo_shadow.values[2] = T3__w2; modInv__modulo_shadow.values[3] = T3__w3; }
  val_t T4__w0, T4__w1, T4__w2, T4__w3;
  { val_t __mask = -T2__w0; T4__w0 = modInv__s2.values[0] ^ ((modInv__s2.values[0] ^ 0x1L) & __mask); T4__w1 = modInv__s2.values[1] ^ ((modInv__s2.values[1] ^ 0L) & __mask); T4__w2 = modInv__s2.values[2] ^ ((modInv__s2.values[2] ^ 0L) & __mask); T4__w3 = modInv__s2.values[3] ^ ((modInv__s2.values[3] ^ 0L) & __mask); }
  val_t T5__w0, T5__w1, T5__w2, T5__w3;
  { T5__w0 = modInv__s2.values[0]+modInv__s2.values[0]; val_t __c = modInv__s2.values[0]+modInv__s2.values[0] < modInv__s2.values[0]; T5__w1 = modInv__s2.values[1]+modInv__s2.values[1]+__c; __c = modInv__s2.values[1]+modInv__s2.values[1] < modInv__s2.values[1] || T5__w1 < __c; T5__w2 = modInv__s2.values[2]+modInv__s2.values[2]+__c; __c = modInv__s2.values[2]+modInv__s2.values[2] < modInv__s2.values[2] || T5__w2 < __c; T5__w3 = modInv__s2.values[3]+modInv__s2.values[3]+__c; }
  val_t T6__w0;
  T6__w0 = (modInv__u.values[0] >> 0) & 1;
  val_t T7__w0;
  T7__w0 = T6__w0 == 0x0L;
  val_t T8__w0;
  T8__w0 = modInv__state.values[0] == 0x2L;
  val_t T9__w0;
  { T9__w0 = T8__w0&&T7__w0; }
  val_t T10__w0, T10__w1, T10__w2, T10__w3;
  { val_t __mask = -T9__w0; T10__w0 = T4__w0 ^ ((T4__w0 ^ T5__w0) & __mask); T10__w1 = T4__w1 ^ ((T4__w1 ^ T5__w1) & __mask); T10__w2 = T4__w2 ^ ((T4__w2 ^ T5__w2) & __mask); T10__w3 = T4__w3 ^ ((T4__w3 ^ T5__w3) & __mask); }
  val_t T11__w0, T11__w1, T11__w2, T11__w3;
  { T11__w0 = modInv__s2.values[0]+modInv__s2.values[0]; val_t __c = modInv__s2.values[0]+modInv__s2.values[0] < modInv__s2.values[0]; T11__w1 = modInv__s2.values[1]+modInv__s2.values[1]+__c; __c = modInv__s2.values[1]+modInv__s2.values[1] < modInv__s2.values[1] || T11__w1 < __c; T11__w2 = modInv__s2.values[2]+modInv__s2.values[2]+__c; __c = modInv__s2.values[2]+modInv__s2.values[2] < modInv__s2.values[2] || T11__w2 < __c; T11__w3 = modInv__s2.values[3]+modInv__s2.values[3]+__c; }
  val_t T12__w0;
  T12__w0 = (((modInv__u.values[0]>modInv__v.values[0]) & modInv__u.values[1] == modInv__v.values[1] || modInv__u.values[1]>modInv__v.values[1]) & modInv__u.values[2] == modInv__v.values[2] || modInv__u.values[2]>modInv__v.values[2]) & modInv__u.values[3] == modInv__v.values[3] || modInv__u.values[3]>modInv__v.values[3];
  val_t T13__w0;
  T13__w0 = (modInv__v.values[0] >> 0) & 1;
  val_t T14__w0;
  T14__w0 = T13__w0 == 0x0L;
  val_t T15__w0;
  { T15__w0 = T7__w0||T14__w0; }
  val_t T16__w0;
  T16__w0 = !T15__w0;
  val_t T17__w0;
  { T17__w0 = T16__w0&&T12__w0; }
  val_t T18__w0;
  { T18__w0 = T8__w0&&T17__w0; }
  val_t T19__w0, T19__w1, T19__w2, T19__w3;
  { val_t __mask = -T18__w0; T19__w0 = T10__w0 ^ ((T10__w0 ^ T11__w0) & __mask); T19__w1 = T10__w1 ^ ((T10__w1 ^ T11__w1) & __mask); T19__w2 = T10__w2 ^ ((T10__w2 ^ T11__w2) & __mask); T19__w3 = T10__w3 ^ ((T10__w3 ^ T11__w3) & __mask); }
  val_t T20__w0, T20__w1, T20__w2, T20__w3;
  { T20__w0 = modInv__s2.values[0]+modInv__s1.values[0]; val_t __c = modInv__s2.values[0]+modInv__s1.values[0] < modInv__s2.values[0]; T20__w1 = modInv__s2.values[1]+modInv__s1.values[1]+__c; __c = modInv__s2.values[1]+modInv__s1.values[1] < modInv__s2.values[1] || T20__w1 < __c; T20__w2 = modInv__s2.values[2]+modInv__s1.values[2]+__c; __c = modInv__s2.values[2]+modInv__s1.values[2] < modInv__s2.values[2] || T20__w2 < __c; T20__w3 = modInv__s2.values[3]+modInv__s1.values[3]+__c; }
  val_t T21__w0;
  { T21__w0 = T15__w0||T12__w0; }
  val_t T22__w0;
  T22__w0 = !T21__w0;
  val_t T23__w0;
  { T23__w0 = T8__w0&&T22__w0; }
  val_t T24__w0, T24__w1, T24__w2, T24__w3;
  { val_t __mask = -T23__w0; T24__w0 = T19__w0 ^ ((T19__w0 ^ T20__w0) & __mask); T24__w1 = T19__w1 ^ ((T19__w1 ^ T20__w1) & __mask); T24__w2 = T19__w2 ^ ((T19__w2 ^ T20__w2) & __mask); T24__w3 = T19__w3 ^ ((T19__w3 ^ T20__w3) & __mask); }
  { modInv__s2_shadow.values[0] = T24__w0; modInv__s2_shadow.values[1] = T24__w1; modInv__s2_shadow.values[2] = T24__w2; modInv__s2_shadow.values[3] = T24__w3; }
  val_t T25__w0, T25__w1, T25__w2, T25__w3;
  { val_t __mask = -T2__w0; T25__w0 = modInv__s1.values[0] ^ ((modInv__s1.values[0] ^ 0x0L) & __mask); T25__w1 = modInv__s1.values[1] ^ ((modInv__s1.values[1] ^ 0L) & __mask); T25__w2 = modInv__s1.values[2] ^ ((modInv__s1.values[2] ^ 0L) & __mask); T25__w3 = modInv__s1.values[3] ^ ((modInv__s1.values[3] ^ 0L) & __mask); }
  val_t T26__w0, T26__w1, T26__w2, T26__w3;
  { T26__w0 = modInv__s1.values[0]+modInv__s1.values[0]; val_t __c = modInv__s1.values[0]+modInv__s1.values[0] < modInv__s1.values[0]; T26__w1 = modInv__s1.values[1]+modInv__s1.values[1]+__c; __c = modInv__s1.values[1]+modInv__s1.values[1] < modInv__s1.values[1] || T26__w1 < __c; T26__w2 = modInv__s1.values[2]+modInv__s1.values[2]+__c; __c = modInv__s1.values[2]+modInv__s1.values[2] < modInv__s1.values[2] || T26__w2 < __c; T26__w3 = modInv__s1.values[3]+modInv__s1.values[3]+__c; }
  val_t T27__w0;
  T27__w0 = !T7__w0;
  val_t T28__w0;
  { T28__w0 = T27__w0&&T14__w0; }
  val_t T29__w0;
  { T29__w0 = T8__w0&&T28__w0; }
  val_t T30__w0, T30__w1, T30__w2, T30__w3;
  { val_t __mask = -T29__w0; T30__w0 = T25__w0 ^ ((T25__w0 ^ T26__w0) & __mask); T30__w1 = T25__w1 ^ ((T25__w1 ^ T26__w1) & __mask); T30__w2 = T25__w2 ^ ((T25__w2 ^ T26__w2) & __mask); T30__w3 = T25__w3 ^ ((T25__w3 ^ T26__w3) & __mask); }
  val_t T31__w0, T31__w1, T31__w2, T31__w3;
  { T31__w0 = modInv__s1.values[0]+modInv__s2.values[0]; val_t __c = modInv__s1.values[0]+modInv__s2.values[0] < modInv__s1.values[0]; T31__w1 = modInv__s1.values[1]+modInv__s2.values[1]+__c; __c = modInv__s1.values[1]+modInv__s2.values[1] < modInv__s1.values[1] || T31__w1 < __c; T31__w2 = modInv__s1.values[2]+modInv__s2.values[2]+__c; __c = modInv__s1.values[2]+modInv__s2.values[2] < modInv__s1.values[2] || T31__w2 < __c; T31__w3 = modInv__s1.values[3]+modInv__s2.values[3]+__c; }
  val_t T32__w0, T32__w1, T32__w2, T32__w3;
  { val_t __mask = -T18__w0; T32__w0 = T30__w0 ^ ((T30__w0 ^ T31__w0) & __mask); T32__w1 = T30__w1 ^ ((T30__w1 ^ T31__w1) & __mask); T32__w2 = T30__w2 ^ ((T30__w2 ^ T31__w2) & __mask); T32__w3 = T30__w3 ^ ((T30__w3 ^ T31__w3) & __mask); }
  val_t T33__w0, T33__w1, T33__w2, T33__w3;
  { T33__w0 = modInv__s1.values[0]+modInv__s1.values[0]; val_t __c = modInv__s1.values[0]+modInv__s1.values[0] < modInv__s1.values[0]; T33__w1 = modInv__s1.values[1]+modInv__s1.values[1]+__c; __c = modInv__s1.values[1]+modInv__s1.values[1] < modInv__s1.values[1] || T33__w1 < __c; T33__w2 = modInv__s1.values[2]+modInv__s1.values[2]+__c; __c = modInv__s1.values[2]+modInv__s1.values[2] < modInv__s1.values[2] || T33__w2 < __c; T33__w3 = modInv__s1.values[3]+modInv__s1.values[3]+__c; }
  val_t T34__w0, T34__w1, T34__w2, T34__w3;
  { val_t __mask = -T23__w0; T34__w0 = T32__w0 ^ ((T32__w0 ^ T33__w0) & __mask); T34__w1 = T32__w1 ^ ((T32__w1 ^ T33__w1) & __mask); T34__w2 = T32__w2 ^ ((T32__w2 ^ T33__w2) & __mask); T34__w3 = T32__w3 ^ ((T32__w3 ^ T33__w3) & __mask); }
  { modInv__s1_shadow.values[0] = T34__w0; modInv__s1_shadow.values[1] = T34__w1; modInv__s1_shadow.values[2] = T34__w2; modInv__s1_shadow.values[3] = T34__w3; }
  val_t T35__w0, T35__w1, T35__w2, T35__w3;
  { val_t __mask = -T2__w0; T35__w0 = modInv__z.values[0] ^ ((modInv__z.values[0] ^ 0x0L) & __mask); T35__w1 = modInv__z.values[1] ^ ((modInv__z.values[1] ^ 0L) & __mask); T35__w2 = modInv__z.values[2] ^ ((modInv__z.values[2] ^ 0L) & __mask); T35__w3 = modInv__z.values[3] ^ ((modInv__z.values[3] ^ 0L) & __mask); }
  val_t T36__w0, T36__w1, T36__w2, T36__w3;
  { T36__w0 = modInv__z.values[0]+0x1L; val_t __c = modInv__z.values[0]+0x1L < modInv__z.values[0]; T36__w1 = modInv__z.values[1]+0L+__c; __c = modInv__z.values[1]+0L < modInv__z.values[1] || T36__w1 < __c; T36__w2 = modInv__z.values[2]+0L+__c; __c = modInv__z.values[2]+0L < modInv__z.values[2] || T36__w2 < __c; T36__w3 = modInv__z.values[3]+0L+__c; }
  val_t T37__w0, T37__w1, T37__w2, T37__w3;
  { val_t __mask = -T8__w0; T37__w0 = T35__w0 ^ ((T35__w0 ^ T36__w0) & __mask); T37__w1 = T35__w1 ^ ((T35__w1 ^ T36__w1) & __mask); T37__w2 = T35__w2 ^ ((T35__w2 ^ T36__w2) & __mask); T37__w3 = T35__w3 ^ ((T35__w3 ^ T36__w3) & __mask); }
  val_t T38__w0, T38__w1, T38__w2, T38__w3;
  { T38__w0 = modInv__z.values[0]-0x1L; val_t __c = modInv__z.values[0]-0x1L > modInv__z.values[0]; T38__w1 = modInv__z.values[1]-0L-__c; __c = modInv__z.values[1]-0L > modInv__z.values[1] || modInv__z.values[1]-0L < T38__w1; T38__w2 = modInv__z.values[2]-0L-__c; __c = modInv__z.values[2]-0L > modInv__z.values[2] || modInv__z.values[2]-0L < T38__w2; T38__w3 = modInv__z.values[3]-0L-__c; }
  val_t T39__w0;
  T39__w0 = modInv__state.values[0] == 0x3L;
  val_t T40__w0, T40__w1, T40__w2, T40__w3;
  { val_t __mask = -T39__w0; T40__w0 = T37__w0 ^ ((T37__w0 ^ T38__w0) & __mask); T40__w1 = T37__w1 ^ ((T37__w1 ^ T38__w1) & __mask); T40__w2 = T37__w2 ^ ((T37__w2 ^ T38__w2) & __mask); T40__w3 = T37__w3 ^ ((T37__w3 ^ T38__w3) & __mask); }
  { modInv__z_shadow.values[0] = T40__w0; modInv__z_shadow.values[1] = T40__w1; modInv__z_shadow.values[2] = T40__w2; modInv__z_shadow.values[3] = T40__w3; }
  val_t T41__w0, T41__w1, T41__w2, T41__w3;
  { val_t __mask = -T2__w0; T41__w0 = modInv__v.values[0] ^ ((modInv__v.values[0] ^ modInv__io_control_req_operand.values[0]) & __mask); T41__w1 = modInv__v.values[1] ^ ((modInv__v.values[1] ^ modInv__io_control_req_operand.values[1]) & __mask); T41__w2 = modInv__v.values[2] ^ ((modInv__v.values[2] ^ modInv__io_control_req_operand.values[2]) & __mask); T41__w3 = modInv__v.values[3] ^ ((modInv__v.values[3] ^ modInv__io_control_req_operand.values[3]) & __mask); }
  val_t T42__w0, T42__w1, T42__w2, T42__w3;
  { T42__w0 = modInv__v.values[0]-modInv__u.values[0]; val_t __c = modInv__v.values[0]-modInv__u.values[0] > modInv__v.values[0]; T42__w1 = modInv__v.values[1]-modInv__u.values[1]-__c; __c = modInv__v.values[1]-modInv__u.values[1] > modInv__v.values[1] || modInv__v.values[1]-modInv__u.values[1] < T42__w1; T42__w2 = modInv__v.values[2]-modInv__u.values[2]-__c; __c = modInv__v.values[2]-modInv__u.values[2] > modInv__v.values[2] || modInv__v.values[2]-modInv__u.values[2] < T42__w2; T42__w3 = modInv__v.values[3]-modInv__u.values[3]-__c; }
  val_t T43__w0;
  T43__w0 = (((modInv__v.values[0]>=modInv__u.values[0]) & modInv__v.values[1] == modInv__u.values[1] || modInv__v.values[1]>modInv__u.values[1]) & modInv__v.values[2] == modInv__u.values[2] || modInv__v.values[2]>modInv__u.values[2]) & modInv__v.values[3] == modInv__u.values[3] || modInv__v.values[3]>modInv__u.values[3];
  val_t T44__w0;
  T44__w0 = modInv__state.values[0] == 0x1L;
  val_t T45__w0;
  { T45__w0 = T44__w0&&T43__w0; }
  val_t T46__w0, T46__w1, T46__w2, T46__w3;
  { val_t __mask = -T45__w0; T46__w0 = T41__w0 ^ ((T41__w0 ^ T42__w0) & __mask); T46__w1 = T41__w1 ^ ((T41__w1 ^ T42__w1) & __mask); T46__w2 = T41__w2 ^ ((T41__w2 ^ T42__w2) & __mask); T46__w3 = T41__w3 ^ ((T41__w3 ^ T42__w3) & __mask); }
  val_t T47__w0, T47__w1, T47__w2, T47__w3;
  { val_t __x[4]; __x[0] = modInv__v.values[0]; __x[1] = modInv__v.values[1]; __x[2] = modInv__v.values[2]; __x[3] = modInv__v.values[3]; val_t __c = 0; val_t __w = 0x1L / 64; val_t __s = 0x1L % 64; val_t __r = 64 - __s; val_t __v3 = MASK(__x[CLAMP(3+__w,0,3)],__w+3<4); T47__w3 = __v3 >> __s | __c; __c = MASK(__v3 << __r, __s != 0); val_t __v2 = MASK(__x[CLAMP(2+__w,0,3)],__w+2<4); T47__w2 = __v2 >> __s | __c; __c = MASK(__v2 << __r, __s != 0); val_t __v1 = MASK(__x[CLAMP(1+__w,0,3)],__w+1<4); T47__w1 = __v1 >> __s | __c; __c = MASK(__v1 << __r, __s != 0); val_t __v0 = MASK(__x[CLAMP(0+__w,0,3)],__w+0<4); T47__w0 = __v0 >> __s | __c; __c = MASK(__v0 << __r, __s != 0); }
  val_t T48__w0, T48__w1, T48__w2, T48__w3;
  { val_t __mask = -T29__w0; T48__w0 = T46__w0 ^ ((T46__w0 ^ T47__w0) & __mask); T48__w1 = T46__w1 ^ ((T46__w1 ^ T47__w1) & __mask); T48__w2 = T46__w2 ^ ((T46__w2 ^ T47__w2) & __mask); T48__w3 = T46__w3 ^ ((T46__w3 ^ T47__w3) & __mask); }
  val_t T49__w0, T49__w1, T49__w2, T49__w3;
  { T49__w0 = modInv__v.values[0]-modInv__u.values[0]; val_t __c = modInv__v.values[0]-modInv__u.values[0] > modInv__v.values[0]; T49__w1 = modInv__v.values[1]-modInv__u.values[1]-__c; __c = modInv__v.values[1]-modInv__u.values[1] > modInv__v.values[1] || modInv__v.values[1]-modInv__u.values[1] < T49__w1; T49__w2 = modInv__v.values[2]-modInv__u.values[2]-__c; __c = modInv__v.values[2]-modInv__u.values[2] > modInv__v.values[2] || modInv__v.values[2]-modInv__u.values[2] < T49__w2; T49__w3 = modInv__v.values[3]-modInv__u.values[3]-__c; }
  val_t T50__w0, T50__w1, T50__w2, T50__w3;
  { val_t __x[4]; __x[0] = T49__w0; __x[1] = T49__w1; __x[2] = T49__w2; __x[3] = T49__w3; val_t __c = 0; val_t __w = 0x1L / 64; val_t __s = 0x1L % 64; val_t __r = 64 - __s; val_t __v3 = MASK(__x[CLAMP(3+__w,0,3)],__w+3<4); T50__w3 = __v3 >> __s | __c; __c = MASK(__v3 << __r, __s != 0); val_t __v2 = MASK(__x[CLAMP(2+__w,0,3)],__w+2<4); T50__w2 = __v2 >> __s | __c; __c = MASK(__v2 << __r, __s != 0); val_t __v1 = MASK(__x[CLAMP(1+__w,0,3)],__w+1<4); T50__w1 = __v1 >> __s | __c; __c = MASK(__v1 << __r, __s != 0); val_t __v0 = MASK(__x[CLAMP(0+__w,0,3)],__w+0<4); T50__w0 = __v0 >> __s | __c; __c = MASK(__v0 << __r, __s != 0); }
  val_t T51__w0, T51__w1, T51__w2, T51__w3;
  { val_t __mask = -T23__w0; T51__w0 = T48__w0 ^ ((T48__w0 ^ T50__w0) & __mask); T51__w1 = T48__w1 ^ ((T48__w1 ^ T50__w1) & __mask); T51__w2 = T48__w2 ^ ((T48__w2 ^ T50__w2) & __mask); T51__w3 = T48__w3 ^ ((T48__w3 ^ T50__w3) & __mask); }
  { modInv__v_shadow.values[0] = T51__w0; modInv__v_shadow.values[1] = T51__w1; modInv__v_shadow.values[2] = T51__w2; modInv__v_shadow.values[3] = T51__w3; }
  val_t T52__w0, T52__w1, T52__w2, T52__w3;
  { val_t __mask = -T2__w0; T52__w0 = modInv__u.values[0] ^ ((modInv__u.values[0] ^ modInv__io_control_req_modulo.values[0]) & __mask); T52__w1 = modInv__u.values[1] ^ ((modInv__u.values[1] ^ modInv__io_control_req_modulo.values[1]) & __mask); T52__w2 = modInv__u.values[2] ^ ((modInv__u.values[2] ^ modInv__io_control_req_modulo.values[2]) & __mask); T52__w3 = modInv__u.values[3] ^ ((modInv__u.values[3] ^ modInv__io_control_req_modulo.values[3]) & __mask); }
  val_t T53__w0, T53__w1, T53__w2, T53__w3;
  { val_t __x[4]; __x[0] = modInv__u.values[0]; __x[1] = modInv__u.values[1]; __x[2] = modInv__u.values[2]; __x[3] = modInv__u.values[3]; val_t __c = 0; val_t __w = 0x1L / 64; val_t __s = 0x1L % 64; val_t __r = 64 - __s; val_t __v3 = MASK(__x[CLAMP(3+__w,0,3)],__w+3<4); T53__w3 = __v3 >> __s | __c; __c = MASK(__v3 << __r, __s != 0); val_t __v2 = MASK(__x[CLAMP(2+__w,0,3)],__w+2<4); T53__w2 = __v2 >> __s | __c; __c = MASK(__v2 << __r, __s != 0); val_t __v1 = MASK(__x[CLAMP(1+__w,0,3)],__w+1<4); T53__w1 = __v1 >> __s | __c; __c = MASK(__v1 << __r, __s != 0); val_t __v0 = MASK(__x[CLAMP(0+__w,0,3)],__w+0<4); T53__w0 = __v0 >> __s | __c; __c = MASK(__v0 << __r, __s != 0); }
  val_t T54__w0, T54__w1, T54__w2, T54__w3;
  { val_t __mask = -T9__w0; T54__w0 = T52__w0 ^ ((T52__w0 ^ T53__w0) & __mask); T54__w1 = T52__w1 ^ ((T52__w1 ^ T53__w1) & __mask); T54__w2 = T52__w2 ^ ((T52__w2 ^ T53__w2) & __mask); T54__w3 = T52__w3 ^ ((T52__w3 ^ T53__w3) & __mask); }
  val_t T55__w0, T55__w1, T55__w2, T55__w3;
  { T55__w0 = modInv__u.values[0]-modInv__v.values[0]; val_t __c = modInv__u.values[0]-modInv__v.values[0] > modInv__u.values[0]; T55__w1 = modInv__u.values[1]-modInv__v.values[1]-__c; __c = modInv__u.values[1]-modInv__v.values[1] > modInv__u.values[1] || modInv__u.values[1]-modInv__v.values[1] < T55__w1; T55__w2 = modInv__u.values[2]-modInv__v.values[2]-__c; __c = modInv__u.values[2]-modInv__v.values[2] > modInv__u.values[2] || modInv__u.values[2]-modInv__v.values[2] < T55__w2; T55__w3 = modInv__u.values[3]-modInv__v.values[3]-__c; }
  val_t T56__w0, T56__w1, T56__w2, T56__w3;
  { val_t __x[4]; __x[0] = T55__w0; __x[1] = T55__w1; __x[2] = T55__w2; __x[3] = T55__w3; val_t __c = 0; val_t __w = 0x1L / 64; val_t __s = 0x1L % 64; val_t __r = 64 - __s; val_t __v3 = MASK(__x[CLAMP(3+__w,0,3)],__w+3<4); T56__w3 = __v3 >> __s | __c; __c = MASK(__v3 << __r, __s != 0); val_t __v2 = MASK(__x[CLAMP(2+__w,0,3)],__w+2<4); T56__w2 = __v2 >> __s | __c; __c = MASK(__v2 << __r, __s != 0); val_t __v1 = MASK(__x[CLAMP(1+__w,0,3)],__w+1<4); T56__w1 = __v1 >> __s | __c; __c = MASK(__v1 << __r, __s != 0); val_t __v0 = MASK(__x[CLAMP(0+__w,0,3)],__w+0<4); T56__w0 = __v0 >> __s | __c; __c = MASK(__v0 << __r, __s != 0); }
  val_t T57__w0, T57__w1, T57__w2, T57__w3;
  { val_t __mask = -T18__w0; T57__w0 = T54__w0 ^ ((T54__w0 ^ T56__w0) & __mask); T57__w1 = T54__w1 ^ ((T54__w1 ^ T56__w1) & __mask); T57__w2 = T54__w2 ^ ((T54__w2 ^ T56__w2) & __mask); T57__w3 = T54__w3 ^ ((T54__w3 ^ T56__w3) & __mask); }
  { modInv__u_shadow.values[0] = T57__w0; modInv__u_shadow.values[1] = T57__w1; modInv__u_shadow.values[2] = T57__w2; modInv__u_shadow.values[3] = T57__w3; }
  val_t T58__w0;
  { val_t __mask = -T2__w0; T58__w0 = modInv__state.values[0] ^ ((modInv__state.values[0] ^ 0x1L) & __mask); }
  val_t T59__w0;
  T59__w0 = !T43__w0;
  val_t T60__w0;
  { T60__w0 = T44__w0&&T59__w0; }
  val_t T61__w0;
  { val_t __mask = -T60__w0; T61__w0 = T58__w0 ^ ((T58__w0 ^ 0x2L) & __mask); }
  val_t T62__w0;
  T62__w0 = (((modInv__v.values[0] == 0x0L) & (modInv__v.values[1] == 0L)) & (modInv__v.values[2] == 0L)) & (modInv__v.values[3] == 0L);
  val_t T63__w0;
  { T63__w0 = T8__w0&&T62__w0; }
  val_t T64__w0;
  { val_t __mask = -T63__w0; T64__w0 = T61__w0 ^ ((T61__w0 ^ 0x3L) & __mask); }
  val_t T65__w0;
  T65__w0 = (((modInv__z.values[0] == 0x2L) & (modInv__z.values[1] == 0L)) & (modInv__z.values[2] == 0L)) & (modInv__z.values[3] == 0L);
  val_t T66__w0;
  { T66__w0 = T39__w0&&T65__w0; }
  val_t T67__w0;
  { val_t __mask = -T66__w0; T67__w0 = T64__w0 ^ ((T64__w0 ^ 0x4L) & __mask); }
  val_t T68__w0;
  T68__w0 = modInv__state.values[0] == 0x4L;
  val_t T69__w0;
  { val_t __mask = -T68__w0; T69__w0 = T67__w0 ^ ((T67__w0 ^ 0x0L) & __mask); }
  { modInv__state_shadow.values[0] = T69__w0; }
  val_t T70__w0, T70__w1, T70__w2, T70__w3;
  { val_t __mask = -T2__w0; T70__w0 = modInv__r1.values[0] ^ ((modInv__r1.values[0] ^ 0x0L) & __mask); T70__w1 = modInv__r1.values[1] ^ ((modInv__r1.values[1] ^ 0L) & __mask); T70__w2 = modInv__r1.values[2] ^ ((modInv__r1.values[2] ^ 0L) & __mask); T70__w3 = modInv__r1.values[3] ^ ((modInv__r1.values[3] ^ 0L) & __mask); }
  val_t T71__w0, T71__w1, T71__w2, T71__w3;
  { T71__w0 = modInv__modulo.values[0]+modInv__modulo.values[0]; val_t __c = modInv__modulo.values[0]+modInv__modulo.values[0] < modInv__modulo.values[0]; T71__w1 = modInv__modulo.values[1]+modInv__modulo.values[1]+__c; __c = modInv__modulo.values[1]+modInv__modulo.values[1] < modInv__modulo.values[1] || T71__w1 < __c; T71__w2 = modInv__modulo.values[2]+modInv__modulo.values[2]+__c; __c = modInv__modulo.values[2]+modInv__modulo.values[2] < modInv__modulo.values[2] || T71__w2 < __c; T71__w3 = modInv__modulo.values[3]+modInv__modulo.values[3]+__c; }
  val_t T72__w0, T72__w1, T72__w2, T72__w3;
  { T72__w0 = T71__w0-modInv__s1.values[0]; val_t __c = T71__w0-modInv__s1.values[0] > T71__w0; T72__w1 = T71__w1-modInv__s1.values[1]-__c; __c = T71__w1-modInv__s1.values[1] > T71__w1 || T71__w1-modInv__s1.values[1] < T72__w1; T72__w2 = T71__w2-modInv__s1.values[2]-__c; __c = T71__w2-modInv__s1.values[2] > T71__w2 || T71__w2-modInv__s1.values[2] < T72__w2; T72__w3 = T71__w3-modInv__s1.values[3]-__c; }
  val_t T73__w0;
  T73__w0 = (((modInv__s1.values[0]>=modInv__modulo.values[0]) & modInv__s1.values[1] == modInv__modulo.values[1] || modInv__s1.values[1]>modInv__modulo.values[1]) & modInv__s1.values[2] == modInv__modulo.values[2] || modInv__s1.values[2]>modInv__modulo.values[2]) & modInv__s1.values[3] == modInv__modulo.values[3] || modInv__s1.values[3]>modInv__modulo.values[3];
  val_t T74__w0;
  { T74__w0 = T63__w0&&T73__w0; }
  val_t T75__w0, T75__w1, T75__w2, T75__w3;
  { val_t __mask = -T74__w0; T75__w0 = T70__w0 ^ ((T70__w0 ^ T72__w0) & __mask); T75__w1 = T70__w1 ^ ((T70__w1 ^ T72__w1) & __mask); T75__w2 = T70__w2 ^ ((T70__w2 ^ T72__w2) & __mask); T75__w3 = T70__w3 ^ ((T70__w3 ^ T72__w3) & __mask); }
  val_t T76__w0, T76__w1, T76__w2, T76__w3;
  { T76__w0 = modInv__modulo.values[0]-modInv__s1.values[0]; val_t __c = modInv__modulo.values[0]-modInv__s1.values[0] > modInv__modulo.values[0]; T76__w1 = modInv__modulo.values[1]-modInv__s1.values[1]-__c; __c = modInv__modulo.values[1]-modInv__s1.values[1] > modInv__modulo.values[1] || modInv__modulo.values[1]-modInv__s1.values[1] < T76__w1; T76__w2 = modInv__modulo.values[2]-modInv__s1.values[2]-__c; __c = modInv__modulo.values[2]-modInv__s1.values[2] > modInv__modulo.values[2] || modInv__modulo.values[2]-modInv__s1.values[2] < T76__w2; T76__w3 = modInv__modulo.values[3]-modInv__s1.values[3]-__c; }
  val_t T77__w0;
  T77__w0 = !T73__w0;
  val_t T78__w0;
  { T78__w0 = T63__w0&&T77__w0; }
  val_t T79__w0, T79__w1, T79__w2, T79__w3;
  { val_t __mask = -T78__w0; T79__w0 = T75__w0 ^ ((T75__w0 ^ T76__w0) & __mask); T79__w1 = T75__w1 ^ ((T75__w1 ^ T76__w1) & __mask); T79__w2 = T75__w2 ^ ((T75__w2 ^ T76__w2) & __mask); T79__w3 = T75__w3 ^ ((T75__w3 ^ T76__w3) & __mask); }
  val_t T80__w0, T80__w1, T80__w2, T80__w3;
  { val_t __x[4]; __x[0] = modInv__r1.values[0]; __x[1] = modInv__r1.values[1]; __x[2] = modInv__r1.values[2]; __x[3] = modInv__r1.values[3]; val_t __c = 0; val_t __w = 0x1L / 64; val_t __s = 0x1L % 64; val_t __r = 64 - __s; val_t __v3 = MASK(__x[CLAMP(3+__w,0,3)],__w+3<4); T80__w3 = __v3 >> __s | __c; __c = MASK(__v3 << __r, __s != 0); val_t __v2 = MASK(__x[CLAMP(2+__w,0,3)],__w+2<4); T80__w2 = __v2 >> __s | __c; __c = MASK(__v2 << __r, __s != 0); val_t __v1 = MASK(__x[CLAMP(1+__w,0,3)],__w+1<4); T80__w1 = __v1 >> __s | __c; __c = MASK(__v1 << __r, __s != 0); val_t __v0 = MASK(__x[CLAMP(0+__w,0,3)],__w+0<4); T80__w0 = __v0 >> __s | __c; __c = MASK(__v0 << __r, __s != 0); }
  val_t T81__w0;
  T81__w0 = (modInv__r1.values[0] >> 0) & 1;
  val_t T82__w0;
  T82__w0 = T81__w0 == 0x0L;
  val_t T83__w0;
  { T83__w0 = T39__w0&&T82__w0; }
  val_t T84__w0, T84__w1, T84__w2, T84__w3;
  { val_t __mask = -T83__w0; T84__w0 = T79__w0 ^ ((T79__w0 ^ T80__w0) & __mask); T84__w1 = T79__w1 ^ ((T79__w1 ^ T80__w1) & __mask); T84__w2 = T79__w2 ^ ((T79__w2 ^ T80__w2) & __mask); T84__w3 = T79__w3 ^ ((T79__w3 ^ T80__w3) & __mask); }
  val_t T85__w0, T85__w1, T85__w2, T85__w3;
  { T85__w0 = modInv__r1.values[0]+modInv__modulo.values[0]; val_t __c = modInv__r1.values[0]+modInv__modulo.values[0] < modInv__r1.values[0]; T85__w1 = modInv__r1.values[1]+modInv__modulo.values[1]+__c; __c = modInv__r1.values[1]+modInv__modulo.values[1] < modInv__r1.values[1] || T85__w1 < __c; T85__w2 = modInv__r1.values[2]+modInv__modulo.values[2]+__c; __c = modInv__r1.values[2]+modInv__modulo.values[2] < modInv__r1.values[2] || T85__w2 < __c; T85__w3 = modInv__r1.values[3]+modInv__modulo.values[3]+__c; }
  val_t T86__w0, T86__w1, T86__w2, T86__w3;
  { val_t __x[4]; __x[0] = T85__w0; __x[1] = T85__w1; __x[2] = T85__w2; __x[3] = T85__w3; val_t __c = 0; val_t __w = 0x1L / 64; val_t __s = 0x1L % 64; val_t __r = 64 - __s; val_t __v3 = MASK(__x[CLAMP(3+__w,0,3)],__w+3<4); T86__w3 = __v3 >> __s | __c; __c = MASK(__v3 << __r, __s != 0); val_t __v2 = MASK(__x[CLAMP(2+__w,0,3)],__w+2<4); T86__w2 = __v2 >> __s | __c; __c = MASK(__v2 << __r, __s != 0); val_t __v1 = MASK(__x[CLAMP(1+__w,0,3)],__w+1<4); T86__w1 = __v1 >> __s | __c; __c = MASK(__v1 << __r, __s != 0); val_t __v0 = MASK(__x[CLAMP(0+__w,0,3)],__w+0<4); T86__w0 = __v0 >> __s | __c; __c = MASK(__v0 << __r, __s != 0); }
  val_t T87__w0;
  T87__w0 = !T82__w0;
  val_t T88__w0;
  { T88__w0 = T39__w0&&T87__w0; }
  val_t T89__w0, T89__w1, T89__w2, T89__w3;
  { val_t __mask = -T88__w0; T89__w0 = T84__w0 ^ ((T84__w0 ^ T86__w0) & __mask); T89__w1 = T84__w1 ^ ((T84__w1 ^ T86__w1) & __mask); T89__w2 = T84__w2 ^ ((T84__w2 ^ T86__w2) & __mask); T89__w3 = T84__w3 ^ ((T84__w3 ^ T86__w3) & __mask); }
  { modInv__r1_shadow.values[0] = T89__w0; modInv__r1_shadow.values[1] = T89__w1; modInv__r1_shadow.values[2] = T89__w2; modInv__r1_shadow.values[3] = T89__w3; }
  val_t T90__w0, T90__w1, T90__w2, T90__w3;
  { val_t __mask = -T68__w0; T90__w0 = 0x0L ^ ((0x0L ^ modInv__r1.values[0]) & __mask); T90__w1 = 0L ^ ((0L ^ modInv__r1.values[1]) & __mask); T90__w2 = 0L ^ ((0L ^ modInv__r1.values[2]) & __mask); T90__w3 = 0L ^ ((0L ^ modInv__r1.values[3]) & __mask); }
  { modInv__io_control_resp_data.values[0] = T90__w0; modInv__io_control_resp_data.values[1] = T90__w1; modInv__io_control_resp_data.values[2] = T90__w2; modInv__io_control_resp_data.values[3] = T90__w3; }
}
void modInv_t::clock_hi ( dat_t<1> reset ) {
  modInv__modulo = modInv__modulo_shadow;
  modInv__s2 = modInv__s2_shadow;
  modInv__s1 = modInv__s1_shadow;
  modInv__z = modInv__z_shadow;
  modInv__v = modInv__v_shadow;
  modInv__u = modInv__u_shadow;
  modInv__state = modInv__state_shadow;
  modInv__r1 = modInv__r1_shadow;
}
int modInv_t::clock ( dat_t<1> reset ) {
  uint32_t min = ((uint32_t)1<<31)-1;
  if (clk_cnt < min) min = clk_cnt;
  clk_cnt-=min;
  if (clk_cnt == 0) clock_lo( reset );
  if (clk_cnt == 0) clock_hi( reset );
  if (clk_cnt == 0) clk_cnt = clk-1;
  return min;
}
void modInv_t::print ( FILE* f ) {
}
bool modInv_t::scan ( FILE* f ) {
  return(!feof(f));
}
void modInv_t::dump(FILE *f, int t) {
}
