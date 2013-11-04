import Chisel._
import ChiselCrypt._

class BigIntHarness extends Module {
  class IO extends Bundle {
    // In order to start this device, set "run" to TRUE, run for a
    // clock cycle, drop "run" to FALSE, and then run until "busy"
    // becomes false.
    val busy = Bool(OUTPUT)
    val run  = Bool(INPUT)

    // This unit can perform a number of functions.  This should
    // probably be an enum, but I'm not sure how to synchronize those
    // between C++ and Scala so I'm just doing it as another UInt.
    val func = UInt(INPUT, width = 2)

    // Here's the actual IO from this unit.
    val ina  = UInt(INPUT,  width=256)
    val inao = Bool(INPUT)
    val inb  = UInt(INPUT,  width=256)
    val inbo = Bool(INPUT)
    val out  = UInt(OUTPUT, width=256)
    val oflo = Bool(OUTPUT)
  }
  val io = new IO()

  // Here we essentially just register the busy value, which allows us
  // to do work for a while.
  val busy = Reg(init = Bool(false)); busy := busy
  io.busy := busy || io.run

  // This just registers all the state so we can somewhat dissociate
  // ourselves from the block that runs this code.
  val ina  = Reg(new BigUInt); ina  := ina
  val inb  = Reg(new BigUInt); inb  := inb
  val func = Reg(io.func);     func := func
  val out  = Reg(new BigUInt); out  := out

  // The "run" command signals that there's work to be done.  We only
  // accept "run" commands when we're not busy to avoid losing things.
  when (!busy && io.run) {
    busy := Bool(true)
    ina.data := io.ina
    ina.oflo := io.inao
    inb.data := io.inb
    inb.oflo := io.inbo
    func     := io.func
  }.otherwise {
    busy := Bool(true)
    func     := func
  }

  // FIXME: These have to be written here as otherwise it seems that
  // Chisel builds some internal nodes and barfs about them not having
  val add = ina + inb
  val sub = ina - inb
  val mul = ina * inb

  // Here's the actual compute block.  Be sure this switch statement
  // matches with the C++ test code!
  when (busy) {
    when (func === UInt(0)) {
      out := add // ina + inb
    }.elsewhen (func === UInt(1)) {
      out := sub // ina - inb
    }.elsewhen (func === UInt(2)) {
      out := mul // ina * inb
    }

    busy := Bool(false)
  }

  // We output both the low bits and a flag that determines if there
  // is overflow.
  io.out  := out.data
  io.oflo := out.oflo
}

object Main {
  def main(args: Array[String]): Unit = {
    chiselMain(args :+ "--vcd", () => Module(new BigIntHarness()))
  }
}
