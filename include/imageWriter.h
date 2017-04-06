#ifndef _IMAGEWRITE_H_
#define _IMAGEWRITE_H_

namespace Renderer
{
	typedef struct {
		unsigned char r, g, b;
	} Pixel255;

	typedef struct {
		float r, g, b;
	} PixelF;

	Pixel255 pixelFloat2Char(PixelF p); 
	void writePixelsToFile(const char* filename, int w, int h, Pixel255* data);
}

#endif