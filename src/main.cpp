#include <iostream>
#include <cmath>
#include "../include/imageWriter.h"


int main()
{
	int h = 100, w = 200;
	Pixel255 data[h * w];
	for(int i = 0; i < h; i++)
		for(int j = 0; j < w; j++)
			data[i*w + j] = (Pixel255){0, 0, 50};

	writePixelsToFile("../output/test.ppm", w, h, data);

	return 0;
}