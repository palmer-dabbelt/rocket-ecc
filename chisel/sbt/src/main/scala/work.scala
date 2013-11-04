package Work

import Chisel._

object Work{
	def main(args: Array[String]) = {

		val res = chiselMain(args, () => Module(new modInv()))
	}

}
