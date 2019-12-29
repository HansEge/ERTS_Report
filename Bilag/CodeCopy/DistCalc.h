#pragma once
#include <systemc.h>

SC_MODULE(DistCalc)
{
	//CLOCK
	sc_in <bool> clk;

	//RESET
	sc_in <bool > reset;

	// BUSY SIGNAL
	sc_out<bool > busy;

	//INPUTS
	// Unsigned int, indicating how many points are to be read
	sc_in<int> numberOfPoints;
	sc_in<bool> ready;

	// Input buffers for coordinates
	sc_fifo_in<int> x;
	sc_fifo_in<int> y;

	//OUTPUTS
	sc_out<float> outputDist;

	// Prototype for IP thread.
	void DistCalcThread(void);

	// Constructor
	SC_CTOR(DistCalc)
	{
		// A single thread, , that triggers on the clock going positive.
		SC_CTHREAD(DistCalcThread,clk.pos());
		reset_signal_is(reset, false);
	}


};
