#include "../include/imageWriter.h"

#include <cstdio>

void writePixelsToFile(const char* filename, int w, int h, Pixel255* data)
{
	FILE* out = fopen(filename, "wb");
	fprintf(out, "P6\n%d %d\n255\n", w, h);
	fwrite((const void*)data, sizeof(unsigned char), 3 * h*w, out);
	fclose(out);
}