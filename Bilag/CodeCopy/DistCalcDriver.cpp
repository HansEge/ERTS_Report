#include "DistCalcDriver.h"

void DistCalcDriver::test() {

	//Variables
	bool isReady;
	int _numberOfPoints = 10;

	// Points to write
	int xs_1[10] = { 1, 2, 3, 4, 5, 6, 7 ,8, 9 ,10};
	int ys_1[10] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

	int xs_2[10] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
	int ys_2[10] = {19, 17, 15, 13, 11, 9, 7, 5, 3, 1};

	float result_1;
	float expectedResult_1 = 12.7279; // Calculated in MATLAB

	float result_2;
	float expectedResult_2 = 25.4558; // Calculated in MATLAB

	// Wait for reset
	wait();
	wait();


	// Write stimuli to DUT
	for (int i = 0; i < _numberOfPoints; i++)
	{
		x.write(xs_1[i]);
		y.write(ys_1[i]);
	}

	// Write number of points with actual data.
	numberOfPoints.write(_numberOfPoints);

	// Indicate that data is ready
	ready.write(true);

	// Wait one cycle, to let IP recognize that data is ready, then set ready to false, 
	// to indicate that no new data is read.
	wait();
	ready.write(false);

	// Wait until result is ready.
	while (busy.read() == true);

	// Wait one additional clock cycle to let answer appear at signal
	wait();

	// Read output
	result_1 = outputDist.read();

	// Write stimuli to DUT
	for (int i = 0; i < _numberOfPoints; i++)
	{
		x.write(xs_2[i]);
		y.write(ys_2[i]);
	}

	// Write number of points with actual data.
	numberOfPoints.write(_numberOfPoints);

	// Indicate that data is ready
	ready.write(true);

	// Wait one cycle, to let IP recognize that data is ready, then set ready to false, 
	// to indicate that no new data is read.
	wait();
	ready.write(false);

	// Wait until result is ready.
	while (busy.read() == true);

	// Wait one additional clock cycle to let answer appear at signal
	wait();

	// Read output
	result_2 = outputDist.read();


	// Compare output to expected value.
	// Written like this to tolerate a bit of rounding error in result.
	if ( (abs(result_1 - expectedResult_1) < 0.001) && (abs(result_2 - expectedResult_2) < 0.001))
		retval = 0;
	else
		retval = 1;

}
