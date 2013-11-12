//Modular multiplication block for ECC

//TODO: Turn this into Montgomery Multiply

package ChiselCrypt {

import Chisel._
import Node._


class modMultiplyIO extends Bundle {
	val control_req_val = Bool(INPUT)
	val control_req_op1 = Bits(INPUT, 256)
	val control_req_op2 = Bits(INPUT, 256)
	val control_req_modulo = Bits(INPUT, 256)

	val control_resp_val = Bool(OUTPUT)
	val control_resp_data = Bits(OUTPUT, 256)
}

class modMultiply extends Module {
	val io = new modMultiplyIO

	//Registers
	val op1 = Reg(UInt(0, 256))
	val op2 = Reg(UInt(0, 256))
	val modulo = Reg(UInt(0, 256))
	val accumReg = Reg(init = Bits(0, 256))
	val product = Reg(Bits(0, 512))
	val bigMod = Reg(Bits(0, 512))
	val remainder = Reg(Bits(0, 512))

	//combinational wires
	val remainderShift = (remainder << UInt(1))(511, 0)
	val dividendShift = product << UInt(1)
	val catRemain = Cat(remainderShift(511, 1), dividendShift(512))


	//Default values of outputs
	io.control_resp_data := Bits(0, 256)

	//For some reason I have to do states this way, Enum isn't working for me, even though I'm doing the exact same things as I did in lab???
	val state = Reg(init = UInt(0, 3))

	//Valid when you are in the finish state
	io.control_resp_val := (state === UInt(2))

	//Idle State, grab operands when valid signal goes high
	when(state === UInt(0)){
		when(io.control_req_val){
			op1 := io.control_req_op1
			op2 := io.control_req_op2
			modulo := io.control_req_modulo
			bigMod := io.control_req_modulo 
			accumReg := UInt(511)
			product := io.control_req_op1*io.control_req_op2
			remainder := UInt(0)
			state := UInt(1)
		}
	}

	//Algorithm for remainder obtained from division algorithm wikipedia
	//This will always take 512 cycles, probably inefficient
	when(state === UInt(1)){
		when(accumReg === UInt(0)){
			state := UInt(2)
		}
		when(catRemain >= bigMod){
				remainder := catRemain - bigMod
				product := (product << UInt(1))(511, 0)
				accumReg := accumReg - UInt(1)
		}
		.otherwise{
				remainder := catRemain
				product := (product << UInt(1))(511, 0)
				accumReg := accumReg - UInt(1)
		}
	}

	when(state === UInt(2)){
		io.control_resp_data := remainder(255, 0)
		state := UInt(0)
	}

}

}
