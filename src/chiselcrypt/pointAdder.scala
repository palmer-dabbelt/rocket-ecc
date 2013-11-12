package ChiselCrypt {

import Chisel._
import Node._
import scala.collection.mutable.HashMap
import util.Random

class pointAdderIO extends Bundle {
	val Op1X = Bits(INPUT, 256)
	val Op1Y = Bits(INPUT, 256)
	val Op2X = Bits(INPUT, 256)
	val Op2Y = Bits(INPUT, 256)
	val curveA = Bits(INPUT, 256)
	val modulo = Bits(INPUT, 256)
	val control_req_val = Bool(INPUT)

	val control_resp_val = Bool(OUTPUT)
	val outX = Bits(OUTPUT, 256)
	val outY = Bits(OUTPUT, 256)
}

class pointAdder extends Module {
	val io = new pointAdderIO

	val modinv = Module(new modInv())
        modinv.io.control_req_val     := Bool(false)
        modinv.io.control_req_operand := UInt(0)
        modinv.io.control_req_modulo  := UInt(0)

	val modmul = Module(new modMultiply())
        modmul.io.control_req_val     := Bool(false)
        modmul.io.control_req_op1     := UInt(0)
        modmul.io.control_req_op2     := UInt(0)
        modmul.io.control_req_modulo  := UInt(0)

	//Registers
	val slope = Reg(Bits(0, 256));     slope := slope
	val slopeSq = Reg(Bits(0, 256));   slopeSq := slopeSq
	val modulo = Reg(Bits(0, 256));    modulo := modulo
	val Op1X = Reg(Bits(0, 256));      Op1X := Op1X
	val Op1Y = Reg(Bits(0, 256));      Op1Y := Op1Y
	val Op2X = Reg(Bits(0, 256));      Op2X := Op2X
	val Op2Y = Reg(Bits(0, 256));      Op2Y := Op2Y
	val curveA = Reg(Bits(0, 256));    curveA := curveA
	val outX = Reg(Bits(0, 256));      outX := outX
	val outY = Reg(Bits(0, 256));      outY := outY
	val deltaXInv = Reg(Bits(0, 256)); deltaXInv := deltaXInv

        // Default values for output wires
        io.control_resp_val := Bool(false)
        io.outX := UInt(0)
        io.outY := UInt(0)

	//Combinational Wires
	val deltaY = Op1Y - Op2Y
	val deltaX = Op1X - Op2X
	val xSum = Op1X + Op2X
	val outDeltaX = Op1X - outX

	//State Machine
	val state = Reg(init = UInt(0, 4))

	//Output values
	io.control_resp_val := state === UInt(7)

	when(state === UInt(0)){
		when(io.control_req_val){
			//Grab inputs
			Op1X := io.Op1X
			Op1Y := io.Op1Y
			Op2X := io.Op2X
			Op2Y := io.Op2Y
			curveA := io.curveA
			modulo := io.modulo

			//Reset accumulator registers
			slope := UInt(0)
			outX := UInt(0)
			outY := UInt(0)
			deltaXInv := UInt(0)

			//run modinv on deltaX
			state := UInt(1)
			modinv.io.control_req_operand := deltaX
			modinv.io.control_req_modulo  := modulo
			modinv.io.control_req_val := Bool(true)
		}
	}

	//Wait for the modinv of deltaX to finish
	when(state === UInt(1)){
		modinv.io.control_req_val := Bool(false)
		when(modinv.io.control_resp_val){
			deltaXInv := modinv.io.control_resp_data
			state := UInt(2)

			//set values for multiply to get slope
			modmul.io.control_req_val := Bool(true)
			modmul.io.control_req_op1 := modinv.io.control_resp_data
			modmul.io.control_req_op2 := deltaY
			modmul.io.control_req_modulo := modulo
		}
	}

	//Wait for slope multiply to finish
	when(state === UInt(2)){
		modmul.io.control_req_val := Bool(false)
		when(modmul.io.control_resp_val){
			slope := modmul.io.control_resp_data
			state := UInt(3)
		}
	}

	//Now square the slope
	when(state === UInt(3)){
		modmul.io.control_req_val := Bool(true)
		modmul.io.control_req_op1 := slope
		modmul.io.control_req_op2 := slope
		modmul.io.control_req_modulo := modulo
		state := UInt(4)
	}

	//Wait for squaring hte slope to finish
	when(state === UInt(4)){
		modmul.io.control_req_val := Bool(false)
		when(modmul.io.control_resp_val){
			slopeSq := modmul.io.control_resp_data
			outX := modmul.io.control_resp_data - xSum
			state := UInt(5)
		}
	}

	//now mutliply slope by deltaX
	when(state === UInt(5)){
		modmul.io.control_req_val := Bool(true)
		modmul.io.control_req_op1 := slope
		modmul.io.control_req_op2 := outDeltaX
		modmul.io.control_req_modulo := modulo
		state := UInt(6)
	}

	when(state === UInt(6)){
		modmul.io.control_req_val := Bool(false)
		when(modmul.io.control_resp_val){
			outY := modmul.io.control_resp_data - Op1Y
			state := UInt(7)
		}
	}

	//Finished with everything!
	when(state === UInt(7)){
		io.outX := outX
		io.outY := outY
		state := UInt(0)
	}
}

}
