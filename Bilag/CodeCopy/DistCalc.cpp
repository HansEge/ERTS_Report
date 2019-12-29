#include "DistCalc.h"
#include <math.h>

// Thread that IP implements
void DistCalc::DistCalcThread(void)
{
	// Start as "not busy"
	busy.write(false);

	// Enter infinite while loop
	while (1)
	{
		// Wait until new data is available
		if (ready.read())
		{
			// Set busy, indicating that calculations are being done.
			busy.write(true);
			
			// Read how many points actually contain valid data.
			unsigned int nPoints = numberOfPoints.read();

			// Initiate total distance as 0, which will be counted up.
			double totalDist = 0;

			// Read first 2 coordinates
			int x0 = x.read();
			int y0 = y.read();

			for (int i = 1; i < 10; i++)
			{
				// Do loop unrolling to optimize for latency/speed.
				#pragma HLS unroll factor = 3

				// Read next points
				int x1 = x.read();
				int y1 = y.read();

				// If valid data, compute distance and add to totalDist.
				if (i< nPoints)
					totalDist += sqrt((x1-x0) * (x1-x0) + (y1 - y0) * (y1 - y0));
				
				// Overwrite "old" coordinates
				x0 = x1;
				y0 = y1;
			}

			// Output result.
			outputDist.write(totalDist);

			// Indicate that answer is ready.
			busy.write(false); 
		}

		// Do nothing
		wait();
	}
};
