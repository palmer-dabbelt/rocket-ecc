import Chisel._
import ChiselCrypt._

class PointHarness extends Module {
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
    val curve_a = UInt(INPUT,  width=256)
    val mod     = UInt(INPUT,  width=256)
    val inax    = UInt(INPUT,  width=256)
    val inay    = UInt(INPUT,  width=256)
    val inbx    = UInt(INPUT,  width=256)
    val inby    = UInt(INPUT,  width=256)
    val outx    = UInt(OUTPUT, width=256)
    val outy    = UInt(OUTPUT, width=256)
  }
  val io = new IO

  // Here we essentially just register the busy value, which allows us
  // to do work for a while.
  val busy = Reg(init = Bool(false)); busy := busy
  io.busy := busy || io.run

  // This just registers all the state so we can somewhat dissociate
  // ourselves from the block that runs this code.
  val func = Reg(io.func); func := func

  // I register the output to make it easier to test from C++
  val outx  = Reg(io.outx);  outx  := outx
  val outy  = Reg(io.outy);  outy  := outy
  io.outx := outx
  io.outy := outy

  // A single point addition unit
  val pointadd = Module(new pointAdder)
  pointadd.io.Op1X   := io.inax
  pointadd.io.Op1Y   := io.inay
  pointadd.io.Op2X   := io.inbx
  pointadd.io.Op2Y   := io.inby
  pointadd.io.curveA := io.curve_a
  pointadd.io.modulo := io.mod
  pointadd.io.control_req_val := Bool(false)

  // Here we attempt to pull new arguments into this unit.
  when (!busy && io.run) {
    busy := Bool(true)
    func := io.func

    when (io.func === UInt(0)) {
      pointadd.io.control_req_val := Bool(true)
    }
  }

  // Check to see if the PoindAdd unit has finished
  when (busy && func === UInt(0) && pointadd.io.control_resp_val) {
    busy := Bool(false)
    outx := pointadd.io.outX
    outy := pointadd.io.outY
  }

}

object Main {
  def main(args: Array[String]): Unit = {
    chiselMain(args :+ "--vcd", () => Module(new PointHarness()))
  }
}
