#include "hough.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned char* houghCircleDetection(unsigned char* edges, int width, int height, int r_min, int r_max, int threshold) {
    int r_step = 1;
    int max_r = r_max - r_min;

    int* accumulator = (int*)calloc((width * height) * max_r, sizeof(int)); // each width*height elements refer to one value of r ( r1 | r2 | ...)

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (edges[y * width + x] == 255) {  // Edge pixel
                for (int r = r_min; r < r_max; r += r_step) {
                    for (int theta = 0; theta < 360; theta++) {
                        int a = x - r * cos(theta * 3.14159265358979 / 180);
                        int b = y - r * sin(theta * 3.14159265358979 / 180);
                        if (a >= 0 && a < width && b >= 0 && b < height) {
                            accumulator[(b * width + a) + ((width * height) * (r - r_min))]++;
                        }
                    }
                }
            }
        }
    }

    unsigned char* circles = (unsigned char*)calloc(width * height, sizeof(unsigned char));
    
    // Find circles by thresholding the accumulator
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int r = 0; r < max_r; r++) {
                if (accumulator[(y * width + x) + ((width * height) * r)] > threshold) {
                    circles[y * width + x] = 255;
                }
            }
        }
    }

    // Free memory
    free(accumulator);

    return circles;
}
