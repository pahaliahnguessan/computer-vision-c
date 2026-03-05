#include "filters.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

unsigned char* toGrayscale(Image img) {
    unsigned char* grayscale = (unsigned char*)malloc(img.width * img.height);
    for (int i = 0; i < img.width * img.height; i++) {
        grayscale[i] = (img.data[3 * i] + img.data[3 * i + 1] + img.data[3 * i + 2]) / 3; // (r + g + b)/3
    }
    return grayscale;
}

unsigned char* toBinary(unsigned char* img, int width, int height) {
    unsigned char* binary = (unsigned char*)calloc(width * height, sizeof(unsigned char));
    for (int i = 0; i < width * height; i++) {
        if (img[i] < 210) {
            binary[i] = 255; //black -> white and viceversa
        }
    }
    return binary;
}

unsigned char* sobelEdgeDetection(unsigned char* img, int width, int height) {
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    unsigned char* edges = (unsigned char*)calloc(width * height, sizeof(unsigned char));
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            int sumX = 0, sumY = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    sumX += img[(y + i) * width + (x + j)] * Gx[i + 1][j + 1];
                    sumY += img[(y + i) * width + (x + j)] * Gy[i + 1][j + 1];
                }
            }
            int magnitude = abs(sumX) + abs(sumY);
            edges[y * width + x] = (magnitude >= 150) ? 255 : magnitude;
        }
    }
    return edges;
}

unsigned char* erosion(unsigned char* img, int width, int height) {
    unsigned char* output = (unsigned char*)calloc(width * height, sizeof(unsigned char));
    
    //00100
    //00100
    //11111
    //00100
    //00100

    for (int y = 2; y < height - 2; y++) {
        for (int x = 2; x < width - 2; x++) {
            if (img[y * width + x] == 255 &&
                img[(y - 1) * width + x] == 255 &&
                img[(y + 1) * width + x] == 255 &&
                img[(y - 2) * width + x] == 255 &&
                img[(y + 2) * width + x] == 255 &&
                img[y * width + (x - 1)] == 255 &&
                img[y * width + (x + 1)] == 255 &&
                img[y * width + (x - 2)] == 255 &&
                img[y * width + (x + 2)] == 255) {
                output[y * width + x] = 255;
            }
        }
    }
    return output;
}

unsigned char* dilation(unsigned char* img, int width, int height) {
    unsigned char* output = (unsigned char*)calloc(width * height, sizeof(unsigned char));

    //11111
    //11111
    //11111
    //11111
    //11111

    for (int y = 2; y < height - 2; y++) {
        for (int x = 2; x < width - 2; x++) {
            if (img[y * width + x] == 255) {
                for (int dy = -2; dy <= 2; dy++) {
                    for (int dx = -2; dx <= 2; dx++) {
                        output[(y + dy) * width + (x + dx)] = 255;
                    }
                }
            }
        }
    }
    return output;
}


unsigned char* morphHat(unsigned char* img, unsigned char* operated, int width, int height) {
    unsigned char* output = (unsigned char*)malloc(width * height);
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (operated[y * width + x] == 255 && img[y * width + x] == 255) {
                output[y * width + x] = 0;
            } else {
                output[y * width + x] = img[y * width + x];
            }
        }
    }
    return output;
}
