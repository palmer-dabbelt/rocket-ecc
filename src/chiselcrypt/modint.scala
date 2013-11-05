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
      res.mod := mod

      when (dat.oflo || dat.data > mod.data) {
        res.dat.data := subdat.data
      }.otherwise {
        res.dat.data := dat.data
      }

      res
    }

    def -(b: ModInt): ModInt = {
      val a = this
      val mod = a.mod
      val res = new ModInt

      val dat = a.dat.data - b.dat.data
      val subdat = mod.data - (b.dat.data - a.dat.data)

      res.dat.data := UInt(0)
      res.dat.oflo := Bool(false)
      res.mod := mod

      when (a.dat.data > b.dat.data) {
        res.dat.data := dat
      }.otherwise {
        res.dat.data := subdat
      }

      res
    }
  }
}
