#include "modInv.h"

static uint32_t src[][2] = { {48, 59}, {52, 73}, {59, 48}, {234523, 51}};
static uint32_t sink[] = {16, 66, 35, 49};

int main (int argc, char* argv[]) {

	modInv_t* c = new modInv_t();

	int lim = 10000;

	c-> init();

	uint32_t num_tests = 4;
	uint32_t testCount = 1;

	int cycle;
	int done = 0;

	for(cycle = 0; lim < 0 || cycle < lim && (testCount <= num_tests) ; cycle++) {

/*	val control_req_val = Bool(INPUT)
	val control_req_xData = Bits(INPUT, 256)
	val control_req_yData = Bits(INPUT, 256)
	val control_req_k = Bits(INPUT, 256)

	val control_resp_val = Bool(OUTPUT)
	val control_resp_xData = Bits(OUTPUT, 256)
	val control_resp_yData = Bits(OUTPUT, 256)*/

		dat_t<1> reset = LIT<1>(cycle==0);

		c->modInv__io_control_req_val = LIT<1>(testCount-1 < num_tests);
		c->modInv__io_control_req_operand = LIT<256>(src[testCount-1][0]);
		c->modInv__io_control_req_modulo = LIT<256>(src[testCount-1][1]);

		c->clock_lo(reset);

		if((c->modInv__io_control_resp_val.lo_word() == 1) && (testCount > 0)){
			uint32_t result_bits = c->modInv__io_control_resp_data.lo_word();

			if(result_bits == sink[testCount-1]){
				printf("[Passed] Test #%d: %dmodinv%d=%d\n", testCount, src[testCount-1][0], src[testCount-1][1], result_bits);
			}
			else{
				printf("[Failed]\n");
				printf("Reason: %d != %d\n", result_bits, sink[testCount-1]);
			}

			if(testCount == num_tests){
				done=1;
			}

			testCount ++;
		}

		//testCount++;

		c->clock_hi(reset);

	}

	if(done){
		printf("All tests passed, simulation finished after %d cycles.\n", cycle);
		return 0;
	}

	printf("[Failed] Timed out after %d cycles!\n", cycle);
	return -1;

}
