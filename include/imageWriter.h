#ifndef _IMAGEWRITE_H_
#define _IMAGEWRITE_H_

namespace Renderer
{
	typedef struct {
		unsigned char R, G, B;
	} Pixel255;

	void writePixelsToFile(const char* filename, int w, int h, Pixel255* data);
}

#endif