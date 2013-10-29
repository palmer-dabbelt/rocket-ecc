import Chisel._
import Node._
import scala.collection.mutable.HashMap
import util.Random

class pointDoublerIO extends Bundle {
	val OpX = Bits(INPUT, 256)
	val OpY = Bits(INPUT, 256)
	val curveA = Bits(INPUT, 256)
	val curveB = Bits(INPUT, 256)
	val curverOrder = Bits(INPUT, 256)
	val control_req_val = Bool(INPUT)

	val control_resp_val = Bool(OUTPUT)
	val outX = Bits(OUTPUT, 256)
	val outY = Bits(OUTPUT, 256)
}

class pointDoubler extends Module {
	val io = new pointDoublerIO


}
	