import Chisel._
import ChiselCrypt._

class ModIntHarness extends Module {
  class IO extends Bundle {
    // In order to start this device, set "run" to TRUE, run for a
    // clock cycle, drop "run" to FALSE, and then run until "busy"
    // becomes false.
    val busy = Bool(OUTPUT)
    val run  = Bool(INPUT)

    // This unit can perform a number of functions.  This should
    // probably be an enum, but I'm not sure how to synchronize those
    // between C++ and Scala so I'm just doing it as another UInt.
    val func = UInt(INPUT, width = 3)

    // Here's the actual IO from this unit.
    val mod  = UInt(INPUT,  width=256)
    val ina  = UInt(INPUT,  width=256)
    val inb  = UInt(INPUT,  width=256)
    val out  = UInt(OUTPUT, width=256)
  }
  val io = new IO()

  // Here we essentially just register the busy value, which allows us
  // to do work for a while.
  val busy = Reg(init = Bool(false)); busy := busy
  io.busy := busy || io.run

  // This just registers all the state so we can somewhat dissociate
  // ourselves from the block that runs this code.
  val mod  = Reg(io.ina);  mod  := mod
  val ina  = Reg(io.ina);  ina  := ina
  val inb  = Reg(io.inb);  inb  := inb
  val func = Reg(io.func); func := func

  // I register the output to make it easier to test from C++
  val out  = Reg(io.out);  out  := out
  io.out := out

  // We use a single ModInv unit to compute the modulo inverse
  val modinv = Module(new modInv)
  modinv.io.control_req_val     := Bool(false)
  modinv.io.control_req_operand := io.ina
  modinv.io.control_req_modulo  := io.mod

  // Here we attempt to pull new arguments into this unit.  Note that
  // sometimes we're going to pass them directly on to the ModInv unit
  // and sometimes we're going to do them as a single cycle.
  when (!busy && io.run) {
    busy := Bool(true)
    func := io.func
    ina  := io.ina
    inb  := io.inb
    mod  := io.mod

    when (io.func === UInt(3)) {
      modinv.io.control_req_val := Bool(true)
    }
  }

  // Check to see if the ModInv unit has finished, which means we can
  // return data back to the caller
  when (busy && io.func === UInt(3) && modinv.io.control_resp_val) {
    busy := Bool(false)
    out  := modinv.io.control_resp_data
  }
}

object Main {
  def main(args: Array[String]): Unit = {
    chiselMain(args :+ "--vcd", () => Module(new ModIntHarness()))
  }
}
