//Modular inversion block for ECC

//TODO: Make sure I do all checks from algos 1 and 2, specifically step 3 from algo 1 (s1 > p)

package Work{

import Chisel._
import Node._


class modInvIO extends Bundle {
	val control_req_val = Bool(INPUT)
	val control_req_operand = Bits(INPUT, 256)
	val control_req_modulo = Bits(INPUT, 256)

	val control_resp_val = Bool(OUTPUT)
	val control_resp_data = Bits(OUTPUT, 256)
}

class modInv extends Module {
	val io = new modInvIO


	//Registers, using variable notation from McIvor Algorithms 1 and 2
	val operand = Reg(Bits(0, 256))
	val modulo = Reg(Bits(0, 256))
	val u = Reg(Bits(0, 256))
	val v = Reg(Bits(0, 256))
	val s1 = Reg(Bits(0, 256))
	val s2 = Reg(Bits(0, 256))	
	val z = Reg(Bits(0, 256))
	val r1 = Reg(Bits(0, 256))

	//Default values of outputs
	io.control_resp_data := Bits(0, 256)

	//For some reason I have to do states this way, Enum isn't working for me, even though I'm doing the exact same things as I did in lab???
	val state = Reg(UInt(0, 3))

	//Valid when you are in the finish state
	io.control_resp_val := (state === UInt(4))

	//Idle State, grab operands when valid signal goes high
	when(state === UInt(0)){
		when(io.control_req_val){
			operand := io.control_req_operand
			modulo := io.control_req_modulo

			u := io.control_req_modulo
			v := io.control_req_operand
			s1 := Bits(0, 256)
			s2 := Bits(1, 256)
			z := Bits(0, 256)
			r1 := Bits(0, 256)


			state := UInt(1)	
		}
	}

	when(state === UInt(1)){
		when(v >= u){
			v := v - u
		}
		.otherwise{
			state := UInt(2)
		}
	}

	//Phase 1 of algorithm 1 in McIvor paper, don't ask me why it works :)
	when(state === UInt(2)){

		when(v === UInt(0, 256)){
			//go to next phase

			when(s1 >= modulo){
				r1 := modulo + modulo - s1
			}
			.otherwise{
				r1 := modulo - s1
			}

			state := UInt(3)
		}

		otherwise{
			when(u(0) === UInt(0)){
				u := u >> UInt(1)
				s2 := s2 + s2
			}

			.elsewhen(v(0) === UInt(0)){
				v := v >> UInt(1)
				s1 := s1 + s1
			}

			.elsewhen(u > v){
				u := (u - v) >> UInt(1)
				s1 := s1 + s2
				s2 := s2 + s2
			}

			.otherwise{
				v := (v - u) >> UInt(1)
				s2 := s2 + s1
				s1 := s1 + s1
			}	

			z := z + UInt(1)
		}


	}

	//Phase 2 of algorithm 2 in McIvor paper
	when(state === UInt(3)){

		when(r1(0) === UInt(0)){
			r1 := r1 >> UInt(1)
		}

		.otherwise{
			r1 := (r1 + modulo) >> UInt(1)
		}

		z := z - UInt(1)

		when(z === UInt(2)){
			state := UInt(4)
		}
	}

	//Finish state
	when(state === UInt(4)){
		io.control_resp_data := r1
		state := UInt(0)
	}

}

}