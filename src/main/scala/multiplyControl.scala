//Base case control block for ECC point multiplication

import Chisel._
import Node._
import scala.collection.mutable.HashMap
import util.Random

class multiplyControlIO extends Bundle {
	val control_req_val = Bool(INPUT)
	val control_req_xData = Bits(INPUT, 256)
	val control_req_yData = Bits(INPUT, 256)
	val control_req_k = Bits(INPUT, 256)

	val control_resp_val = Bool(OUTPUT)
	val control_resp_xData = Bits(OUTPUT, 256)
	val control_resp_yData = Bits(OUTPUT, 256)
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

	val multiplier = Reg(Bits(0, 256))
	val xData = Reg(Bits(0, 256))
	val yData = Reg(Bits(0, 256))
	val xAccum = Reg(Bits(0, 256))
	val yAccum = Reg(Bits(0, 256))
	val flag = Reg(Bool(false))

	val sIdle :: sCompute :: sAddWait :: sDoubleWait :: sFinish :: Nil = Enum(UInt(), 5)
	val state = Reg(init=sIdle)

	io.control_resp_val := (state === sFinish)


	when(state === sIdle){
		when(io.control_req_val){
			multiplier := io.control_req_k
			xData := io.control_req_xData
			yData := io.control_req_yData
			state := sCompute	
		}
	}

	when(state === sCompute){
		//val multX3 = Bits((multiplier<<UInt(1) + multiplier), 256)
		val multX3 = multiplier*UInt(3)
		flag := Bool(false)
		xAccum := UInt(0, 256)
		yAccum := UInt(0, 256)

		for(i <- 255 until 1){
			xAccum := xAccum + xAccum
			yAccum := yAccum + yAccum

			when(multiplier(i) === UInt(1) & multX3(i) === UInt(0)){
				xAccum := xAccum - xData
				yAccum := yAccum - yData
			}

			when(multiplier(i) === UInt(0) & multX3(i) === UInt(1)){
				xAccum := xAccum + xData
				yAccum := yAccum + yData
			}
		}

		state := sFinish
	}

	when(state === sAddWait){
		state := sCompute
	}

	when(state === sDoubleWait){
		state := sCompute
	}

	when(state === sFinish){
		control_resp_xData := xAccum
		control_resp_yData := yAccum
		state := sIdle
	}

}

class multiplyControlTest(c: multiplyControl) extends Tester(x, Array(c.io)){
	defTests{
		var allGood = true
		val vars = new HashMap[Node, Node]()
		vars.clear()
		vars(c.io.control_req_val) = Bool(true)
		vars(c.io.control_req_k) = UInt(13, 256)
		vars(c.io.control_req_xData) = UInt(22, 256)
		vars(c.io.control_req_yData) = UInt(33, 256)
		vars(c.io.control_resp_xData) = UInt(286, 256)
		vars(c.io.control_resp_yData) = UInt(429, 256)
		allGood = step(vars) && allGood
		allGood
	}
}