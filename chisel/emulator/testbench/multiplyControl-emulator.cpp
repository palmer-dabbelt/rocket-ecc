#include "multiplyControl.h"

static uint32_t src[][3] = { {4, 5, 10}, {8, 5, 20}, {7, 3, 4}};
static uint32_t sink[][2] = {{40, 50}, {160, 100}, {28, 12}};

int main (int argc, char* argv[]) {

	multiplyControl_t* c = new multiplyControl_t();

	int lim = 5000;

	c-> init();

	uint32_t num_tests = 3;
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

		c->multiplyControl__io_control_req_val = LIT<1>(testCount-1 < num_tests);
		c->multiplyControl__io_control_req_xData = LIT<256>(src[testCount-1][0]);
		c->multiplyControl__io_control_req_yData = LIT<256>(src[testCount-1][1]);
		c->multiplyControl__io_control_req_k = LIT<256>(src[testCount-1][2]);


		c->clock_lo(reset);

		if((c->multiplyControl__io_control_resp_val.lo_word() == 1) && (testCount > 0)){
			uint32_t result_bits_x = c->multiplyControl__io_control_resp_xData.lo_word();
			uint32_t result_bits_y = c->multiplyControl__io_control_resp_yData.lo_word();

			if(result_bits_x == sink[testCount-1][0] && result_bits_y == sink[testCount-1][1]){
				printf("[Passed] Test X #%d: %d*%d=%d\n", testCount, src[testCount-1][0], src[testCount-1][2], result_bits_x);
				printf("[Passed] Test X #%d: %d*%d=%d\n", testCount, src[testCount-1][1], src[testCount-1][2], result_bits_y);
			}
			else{
				printf("[Failed]\n");
				printf("Reason: %d != %d\n", result_bits_x, sink[testCount-1][0]);
				printf("Reason: %d != %d\n", result_bits_y, sink[testCount-1][1]);
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
