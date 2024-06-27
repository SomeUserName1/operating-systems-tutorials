#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	// screen resolution
	const int WIDTH = 80;
	const int HEIGHT = 25;
	
	// scan resolution and rendering
	const double WIDTH_STEP = 2.0 * M_PI / ((double) WIDTH);
	const double HEIGHT_STEP = 2.0 / ((double) HEIGHT);
	const double THICKNESS = 1.2;
	
	// loop line by line, from left to right
	for (double y = 1.0; y >= -1.0; y -= HEIGHT_STEP)
	{
		for (double x = 0.0; x <= 2.0 * M_PI; x += WIDTH_STEP)
		{
			double result = sin(x);
			if (fabs(y -  result) < THICKNESS * HEIGHT_STEP) {
				printf("*");
			} else {
				printf(" ");
			}
		}
		 printf("\n"); // new line
	}
	
	// success
	return 0;
}

