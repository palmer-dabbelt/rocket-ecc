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

  // Builds a pair of ModInts from the current state of the circuit.
  // This is essentially a cast, but much uglier.
  // FIXME: Make this pretty
  val inami = new ModInt
  inami.dat.data := ina
  inami.dat.oflo := Bool(false)
  inami.mod.data := mod
  inami.mod.oflo := Bool(false)
  val inbmi = new ModInt
  inbmi.dat.data := inb
  inbmi.dat.oflo := Bool(false)
  inbmi.mod.data := mod
  inbmi.mod.oflo := Bool(false)

  // These results need to be placed outside of the switch statement
  // below because otherwise Chisel barfs about unconnected inputs.
  val add = inami + inbmi
  val sub = inami - inbmi

  // We use a single ModInv unit to compute the modulo inverse
  val modinv = Module(new modInv)
  modinv.io.control_req_val     := Bool(false)
  modinv.io.control_req_operand := io.ina
  modinv.io.control_req_modulo  := io.mod

  // ... and a single modMultiply to compute products
  val modmul = Module(new modMultiply)
  modmul.io.control_req_val    := Bool(false)
  modmul.io.control_req_op1    := io.ina
  modmul.io.control_req_op2    := io.inb
  modmul.io.control_req_modulo := io.mod

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
    }.elsewhen (io.func === UInt(2)) {
      modmul.io.control_req_val := Bool(true)
    }
  }

  // Check to see if the ModInv unit has finished, which means we can
  // return data back to the caller
  when (busy && func === UInt(3) && modinv.io.control_resp_val) {
    busy := Bool(false)
    out  := modinv.io.control_resp_data
  }

  // Check to see if the ModMul unit has finished, which means we can
  // return data back to the caller
  when (busy && func === UInt(2) && modmul.io.control_resp_val) {
    busy := Bool(false)
    out  := modmul.io.control_resp_data
  }

  when (busy && func === UInt(0)) {
    busy := Bool(false)
    out  := add.dat.data
  }

  when (busy && func === UInt(1)) {
    busy := Bool(false)
    out  := sub.dat.data
  }
}

object Main {
  def main(args: Array[String]): Unit = {
    chiselMain(args :+ "--vcd", () => Module(new ModIntHarness()))
  }
}
