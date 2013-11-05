import Chisel._;

package ChiselCrypt {
  // This is like a UInt, but all calculations are done modulo some
  // given value.  This means that in addition to providing a bit width
  // of this integer we need to provide.
  class ModInt extends Bundle {
    val dat = new BigUInt()
    val mod = new BigUInt()

    def +(b: ModInt): ModInt = {
      val a = this
      val mod = a.mod
      val res = new ModInt

      val dat = a.dat + b.dat
      val subdat = dat - mod

      res.dat.data := UInt(0)
      res.dat.oflo := Bool(false)
      when (dat.oflo || dat.data > mod.data) {
        res.dat.data := subdat.data
      }.otherwise {
        res.dat.data := dat.data
      }

      res.dat.oflo := Bool(false)
      res.mod := mod

      res
    }
  }
}
