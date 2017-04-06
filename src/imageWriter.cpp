#include "../include/imageWriter.h"

#include <cstdio>

namespace Renderer
{
	Pixel255 pixelFloat2Char(PixelF p)
	{
		Pixel255 out;
		out.r = (unsigned char)(255.0f * p.r);
		out.g = (unsigned char)(255.0f * p.g);
		out.b = (unsigned char)(255.0f * p.b);
		return out;
	}

	void writePixelsToFile(const char* filename, int w, int h, Pixel255* data)
	{
		FILE* out = fopen(filename, "wb");
		fprintf(out, "P6\n%d %d\n255\n", w, h);
		fwrite((const void*)data, sizeof(unsigned char), 3 * h*w, out);
		fclose(out);
	}
}