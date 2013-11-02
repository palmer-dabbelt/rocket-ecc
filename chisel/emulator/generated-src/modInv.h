#ifndef __modInv__
#define __modInv__

#include "emulator.h"

class modInv_t : public mod_t {
 public:
  dat_t<1> modInv__io_control_resp_val;
  dat_t<256> modInv__io_control_req_modulo;
  dat_t<1> modInv__io_control_req_val;
  dat_t<256> modInv__modulo;
  dat_t<256> modInv__modulo_shadow;
  dat_t<256> modInv__s2;
  dat_t<256> modInv__s2_shadow;
  dat_t<256> modInv__s1;
  dat_t<256> modInv__s1_shadow;
  dat_t<256> modInv__z;
  dat_t<256> modInv__z_shadow;
  dat_t<256> modInv__u;
  dat_t<256> modInv__u_shadow;
  dat_t<256> modInv__io_control_req_operand;
  dat_t<256> modInv__v;
  dat_t<256> modInv__v_shadow;
  dat_t<2> modInv__state;
  dat_t<2> modInv__state_shadow;
  dat_t<256> modInv__r1;
  dat_t<256> modInv__r1_shadow;
  dat_t<256> modInv__io_control_resp_data;
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
