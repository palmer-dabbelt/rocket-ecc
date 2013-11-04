import Chisel._;

package ChiselCrypt {
  // This is like a UInt but it keeps track of overflow which is
  // necessary for some crypto calculations.
  class BigInt extends Node {
  }
}
