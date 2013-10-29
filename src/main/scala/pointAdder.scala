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
	val curverOrder = Bits(INPUT, 256)
	val control_req_val = Bool(INPUT)

	val control_resp_val = Bool(OUTPUT)
	val outX = Bits(OUTPUT, 256)
	val outY = Bits(OUTPUT, 256)
}

class pointAdder extends Module {
	val io = pointAdderIO


}
	