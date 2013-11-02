//Base case control block for ECC point multiplication
//This unit runs through the double and add algorithm (also includes subtraction)
//It just does an integer add right and double right now, the idea is to replace
//these ops with elliptic curve operations later

//TODO: Add bits to input multiplier, because multiplying by 3 could overflow
//		Add ready signals (already have valids)

package Work{

import Chisel._
import Node._

class multiplyControlIO extends Bundle {
	val control_req_val = Bool(INPUT)
	val control_req_xData = Bits(INPUT, 256)
	val control_req_yData = Bits(INPUT, 256)
	val control_req_k = Bits(INPUT, 256)

	val control_resp_val = Bool(OUTPUT)
	val control_resp_xData = Bits(OUTPUT, 256)
	val control_resp_yData = Bits(OUTPUT, 256)

//Placeholders for later
/*
	val addition_req_val = Bool(OUTPUT)
	val addition_req_Op1x = Bits(OUTPUT, 256)
	val addition_req_Op1y = Bits(OUTPUT, 256)
	val addition_req_Op2x = Bits(OUTPUT, 256)
	val addition_req_Op2y = Bits(OUTPUT, 256) 

	val addition_resp_val = Bool(INPUT)
	val addition_resp_xData = Bits(INPUT, 256)
	val addition_resp_yData = Bits(INPUT, 256)

	val double_req_val = Bool(OUTPUT)
	val double_req_Opx = Bits(OUTPUT, 256)
	val double_req_Opy = Bits(OUTPUT, 256)

	val double_resp_val = Bool(INPUT)
	val double_resp_xData = Bits(INTPUT, 256)
	val double_resp_yData = Bits(INPUT, 256)
*/
}

class multiplyControl extends Module {
	val io = new multiplyControlIO


	//Registers
	val multiplier = Reg(Bits(0, 256))
	val multX3 = Reg(Bits(0, 256))
	val xData = Reg(Bits(0, 256))
	val yData = Reg(Bits(0, 256))
	val xAccum = Reg(Bits(0, 256))
	val yAccum = Reg(Bits(0, 256))
	val flag = Reg(Bool(false))
	val accNum = Reg(Bits(0, 256))

	//Default values for outputs
	io.control_resp_xData := Bits(0, 256)
	io.control_resp_yData := Bits(0, 256)

	//For some reason I have to label states as numbers... Enum isn't working for me, even though I'm doing the exact same things as I did in lab???
	val state = Reg(UInt(0, 3))

	io.control_resp_val := (state === UInt(2))

	//Idle State, grab operands when valid signal goes high
	when(state === UInt(0)){
		when(io.control_req_val){
			multiplier := io.control_req_k
			multX3 := io.control_req_k*UInt(3)
			xData := io.control_req_xData
			yData := io.control_req_yData
			xAccum := UInt(0, 256)
			yAccum := UInt(0, 256)
			accNum := UInt(255)
			state := UInt(1)	
		}
	}

	//Compute state, this does a double and add algorithm. It also includes subtractions, I found an algorithm that said that if you take the 
	//muliplier (call it k), and multiply it by three, and then iterate through the bits, you can either add or subtract, this is faster than 
	//only using doubles and adds! 
	when(state === UInt(1)){
		flag := Bool(false)
		xAccum := xAccum + xAccum
		yAccum := yAccum + yAccum

		when(io.control_req_k(accNum) === UInt(1) & multX3(accNum) === UInt(0)){
			xAccum := xAccum + xAccum - io.control_req_xData
			yAccum := yAccum + yAccum - io.control_req_yData
		}

		when(io.control_req_k(accNum) === UInt(0) & multX3(accNum) === UInt(1)){
			xAccum := xAccum + xAccum + io.control_req_xData
			yAccum := yAccum + yAccum + io.control_req_yData
		}

		accNum := accNum - UInt(1)
		when(accNum === UInt(1)){
			state := UInt(2)
		}
	}


	//Finish state
	when(state === UInt(2)){
		io.control_resp_xData := xAccum
		io.control_resp_yData := yAccum
		state := UInt(0)
	}

	//These would be add and Double state laters
	when(state === UInt(3)){
		state := UInt(1)
	}

	when(state === UInt(4)){
		state := UInt(1)
	}

}

}