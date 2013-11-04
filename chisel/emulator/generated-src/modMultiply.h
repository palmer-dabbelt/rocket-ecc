#ifndef __modMultiply__
#define __modMultiply__

#include "emulator.h"

class modMultiply_t : public mod_t {
 public:
  dat_t<1> modMultiply__io_control_resp_val;
  dat_t<256> modMultiply__io_control_req_op1;
  dat_t<1> modMultiply__io_control_req_val;
  dat_t<256> modMultiply__op1Mod;
  dat_t<256> modMultiply__op1Mod_shadow;
  dat_t<1> modMultiply__flag1;
  dat_t<1> modMultiply__flag1_shadow;
  dat_t<256> modMultiply__io_control_req_op2;
  dat_t<256> modMultiply__op2Mod;
  dat_t<256> modMultiply__op2Mod_shadow;
  dat_t<256> modMultiply__io_control_req_modulo;
  dat_t<256> modMultiply__modulo;
  dat_t<256> modMultiply__modulo_shadow;
  dat_t<1> modMultiply__flag2;
  dat_t<1> modMultiply__flag2_shadow;
  dat_t<2> modMultiply__state;
  dat_t<2> modMultiply__state_shadow;
  dat_t<512> modMultiply__product;
  dat_t<512> modMultiply__product_shadow;
  dat_t<256> modMultiply__io_control_resp_data;
  int clk;
  int clk_cnt;

  void init ( bool rand_init = false );
  void clock_lo ( dat_t<1> reset );
  void clock_hi ( dat_t<1> reset );
  int clock ( dat_t<1> reset );
  void print ( FILE* f );
  bool scan ( FILE* f );
  void dump ( FILE* f, int t );
};

#endif
