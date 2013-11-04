import Chisel._
//import ChiselCrypt._

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
  val ina  = Reg(init = UInt(0, width=512));  ina  := ina
  val inao  = Reg(init = Bool(false));        inao := inao
  val inb  = Reg(init = UInt(0, width=512));  inb  := inb
  val inbo  = Reg(init = Bool(false));        inbo := inbo
  val func = Reg(io.func);                    func := func
  val out  = Reg(init = UInt(0, width=512));  out  := out

  // The "run" command signals that there's work to be done.  We only
  // accept "run" commands when we're not busy to avoid losing things.
  when (!busy && io.run) {
    busy := Bool(true)
    ina  := io.ina
    inao := io.inao
    inb  := io.inb
    inbo := io.inbo
    func := io.func
  }

  // Here's the actual compute block.  Be sure this switch statement
  // matches with the C++ test code!
  when (busy) {
    when (func === UInt(0)) {
      out := ina + inb
    }.elsewhen (func === UInt(1)) {
      out := ina - inb
    }.elsewhen (func === UInt(2)) {
      out := ina * inb
    }

    busy := Bool(false)
  }

  // We output both the low bits and a flag that determines if there
  // is overflow.
  io.out  := out
  io.oflo := (out > (UInt(1) << UInt(256))) || inao || inbo
}

object Main {
  def main(args: Array[String]): Unit = {
    chiselMain(args :+ "--vcd", () => Module(new BigIntHarness()))
  }
}
