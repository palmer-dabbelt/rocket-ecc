import Chisel._;

package ChiselCrypt {
  class BigUInt() extends Bundle {
    val data = UInt(INPUT)
    val oflo = Bool(INPUT)

    def +(b: BigUInt): BigUInt = {
      val a = this
      val res = new BigUInt

      // By default Chisel will generate additions of the same bit
      // width as the inputs.  This cat magic essentially just
      // zero-extends the inputs so we can check for overflow later.
      val adat = Cat(UInt(0, width = 1), a.data)
      val bdat = Cat(UInt(0, width = 1), b.data)

      val odat = adat + bdat
      val sdat = a.data + b.data

      res.data := odat
      res.oflo := (odat > sdat) || a.oflo || b.oflo
      res
    }

    def -(b: BigUInt): BigUInt = {
      val a = this
      val res = new BigUInt
      res.data := a.data - b.data
      res.oflo := (b.data > a.data) || a.oflo || b.oflo
      res
    }

    def *(b: BigUInt): BigUInt = {
      val a = this
      val res = new BigUInt

      // By default Chisel will generation multiplications of the full
      // bit width (ie, a.width + b.width).  These masks essentially
      // just undo that in order to chechk for overflow (note that
      // "x^x" is 0).  Note that I'd love to be able to do something
      // like "UInt(-1, a.width)", but because of how Chisel generates
      // widths that doesn't seem to be possible.  Essentially the
      // problem is that "UInt(-1, a.width)" can compile to "UInt(-1,
      // -1)".  That means "infer any width for the UInt", essentially
      // losing the information that it needs to have the same width
      // as "a".
      val amask = ~(a.data ^ a.data)
      val bmask = ~(b.data ^ b.data)

      val odat = a.data * b.data
      val sdat = (amask | bmask) & (a.data * b.data)

      res.data := odat
      res.oflo := (odat > sdat) || a.oflo || b.oflo
      res
    }
  }
}
