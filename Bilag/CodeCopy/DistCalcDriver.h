#ifndef __DIST_CALC_DRIVER__
#define __DIST_CALC_DRIVER__
#include <systemc.h>

SC_MODULE(DistCalcDriver) {

	//CLOCK
	sc_in <bool> clk;

	//RESET
	sc_in<bool> reset;

	//OUTPUTS
	sc_out<int> numberOfPoints;
	sc_out<bool> ready;

	// Input buffers for coordinates
	sc_fifo_out<int> x;
	sc_fifo_out<int> y;	

	//INPUTS
	sc_in<float> outputDist;
	sc_in<bool> busy;

	int retval;

	//Process Declaration
	void test();

	//Constructor
	SC_CTOR(DistCalcDriver) : retval(-1) {

		//Process Registration
		SC_CTHREAD(test,clk.pos());
	}
};

#endif
