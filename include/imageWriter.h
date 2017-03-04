#ifndef _IMAGEWRITE_H_
#define _IMAGEWRITE_H_

#include <glm/glm.hpp>

typedef struct {
	unsigned char R, G, B;
} Pixel255;

typedef glm::vec3 PixelFloat;

void writePixelsToFile(const char* filename, int w, int h, Pixel255* data);

#endif