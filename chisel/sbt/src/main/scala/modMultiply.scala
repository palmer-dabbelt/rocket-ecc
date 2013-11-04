//Modular multiplication block for ECC

//TODO: Turn this into Montgomery Multiply

package Work{

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


	//Registers, using variable notation from McIvor Algorithms 1 and 2
	val op1 = Reg(Bits(0, 256))
	val op2 = Reg(Bits(0, 256))
	val modulo = Reg(Bits(0, 256))
	val op1Mod = Reg(Bits(0, 256))
	val op2Mod = Reg(Bits(0, 256))
	val product = Reg(Bits(0, 512))
	val flag1 = Reg(Bool(false))
	val flag2 = Reg(Bool(false))

	//Default values of outputs
	io.control_resp_data := Bits(0, 256)

	//For some reason I have to do states this way, Enum isn't working for me, even though I'm doing the exact same things as I did in lab???
	val state = Reg(UInt(0, 3))

	//Valid when you are in the finish state
	io.control_resp_val := (state === UInt(3))

	//Idle State, grab operands when valid signal goes high
	when(state === UInt(0)){
		when(io.control_req_val){
			op1 := io.control_req_op1
			op2 := io.control_req_op2
			modulo := io.control_req_modulo

			op1Mod := io.control_req_op1
			op2Mod := io.control_req_op2

			product := Bits(0, 512)

			state := UInt(1)
		}
	}

	//To do A*B mod C, first do AmodC and BmodC
	when(state === UInt(1)){
		when(op1Mod >= modulo){
			op1Mod := op1Mod - modulo
		}

		.otherwise{
			flag1 := Bool(true)
		}

		when(op2Mod >= modulo){
			op2Mod := op2Mod - modulo
		}

		.otherwise{
			flag2 := Bool(true)
		}

		when(flag1 & flag2){
			product := op1Mod*op2Mod
			state := UInt(2)
		}
	}

	//Now do (AmodC*BmodC) mod C
	when(state === UInt(2)){
		when(product >= modulo){
			product := product - modulo
		}
		.otherwise{
			state := UInt(3)
		}
	}

	when(state === UInt(3)){
		io.control_resp_data := product(255, 0)
		state := UInt(0)
	}

}

}