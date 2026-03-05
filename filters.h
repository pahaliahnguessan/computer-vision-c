#ifndef FILTERS_H
#define FILTERS_H

#include "image.h"

unsigned char* toGrayscale(Image img);
unsigned char* toBinary(unsigned char* img, int width, int height);
unsigned char* sobelEdgeDetection(unsigned char* img, int width, int height);
unsigned char* erosion(unsigned char* img, int width, int height);
unsigned char* dilation(unsigned char* img, int width, int height);
unsigned char* morphHat(unsigned char* img, unsigned char* operated, int width, int height);

#endif
