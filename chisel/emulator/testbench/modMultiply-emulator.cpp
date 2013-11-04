#include "modMultiply.h"

static uint32_t src[][3] = { {4, 5, 10}, {8, 5, 20}, {7, 3, 4}};
static uint32_t sink[] = {0, 0, 1};

int main (int argc, char* argv[]) {

	modMultiply_t* c = new modMultiply_t();

	int lim = 5000;

	c-> init();

	uint32_t num_tests = 3;
	uint32_t testCount = 1;

	int cycle;
	int done = 0;

	for(cycle = 0; lim < 0 || cycle < lim && (testCount <= num_tests) ; cycle++) {


		dat_t<1> reset = LIT<1>(cycle==0);

		c->modMultiply__io_control_req_val = LIT<1>(testCount-1 < num_tests);
		c->modMultiply__io_control_req_op1 = LIT<256>(src[testCount-1][0]);
		c->modMultiply__io_control_req_op2 = LIT<256>(src[testCount-1][1]);
		c->modMultiply__io_control_req_modulo = LIT<256>(src[testCount-1][2]);


		c->clock_lo(reset);

		if((c->modMultiply__io_control_resp_val.lo_word() == 1) && (testCount > 0)){
			uint32_t result_bits = c->modMultiply__io_control_resp_data.lo_word();

			if(result_bits == sink[testCount-1]){
				printf("[Passed] Test #%d: %d*%d=%d (mod %d) \n", testCount, src[testCount-1][0], src[testCount-1][1], result_bits, src[testCount-1][2]);
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
