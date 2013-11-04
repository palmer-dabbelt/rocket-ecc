import Chisel._;

package ChiselCrypt {
  // This is like a UInt, but all calculations are done modulo some
  // given value.  This means that in addition to providing a bit width
  // of this integer we need to provide.
  class ModInt extends Bundle {
    val dat = new BigUInt()
    val mod = new BigUInt()
  }
}
