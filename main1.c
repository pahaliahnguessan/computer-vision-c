#include "image.h"
#include "filters.h"
#include "hough.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc <= 3) {
        printf("Usage: %s <input.ppm> <output_prefix> [options]\n", argv[0]);
        printf("Options:\n");
        printf("  -gray     Convert to grayscale\n");
        printf("  -binary     Convert to binary\n");
        printf("  -sobel    Apply Sobel edge detection\n");
        printf("  -hough    Detect circles using Hough Transform\n");
        printf("  -erode    Apply erosion\n");
        printf("  -dilate   Apply dilation\n");
        printf("  -opening  Apply opening\n");
        printf("  -closing  Apply closing\n");
        printf("  -top      Apply top hat\n");
        printf("  -bottom  Apply bottom hat\n");
        return 1;
    } else {
        
        int threshold, r_min, r_max;

        Image img = loadPPM(argv[1]);
        char* outputPrefix = argv[2];

        unsigned char* grayscale = toGrayscale(img);
        unsigned char* binary = toBinary(grayscale, img.width, img.height);
        unsigned char* edges = sobelEdgeDetection(grayscale, img.width, img.height);

        for (int i = 3; i < argc; i++) {

            if (strstr(argv[i], "-gray")) {
                saveTransformation("1_gray.pgm", outputPrefix, grayscale, img.width, img.height);
            }

            if (strstr(argv[i], "-binary")) {
                saveTransformation("0_binary.pgm", outputPrefix, binary, img.width, img.height);
            }

            if (strstr(argv[i], "-sobel")) {
                saveTransformation("2_sobel.pgm", outputPrefix, edges, img.width, img.height);
            }

            if (strstr(argv[i], "-hough")) {
                printf("Insert an integer number as minimum value (pixels) for the radius of circles to be detected: ");
                scanf("%d", &r_min);
                printf("Insert an integer number as maximum value (pixels) for the radius of circles to be detected: ");
                scanf("%d", &r_max);
                printf("Insert an integer number as threshold value (pixels) for circle centers to be detected: ");
                scanf("%d", &threshold);
                unsigned char* circles = houghCircleDetection(edges, img.width, img.height, r_min, r_max, threshold);
                saveTransformation("3_houghed.pgm", outputPrefix, circles, img.width, img.height);

                free(circles);
            }
            
            if (strstr(argv[i], "-erode")) {
                unsigned char* eroded = erosion(binary, img.width, img.height);
                saveTransformation("4_eroded.pgm", outputPrefix, eroded, img.width, img.height);
                
                free(eroded);
            }

            if (strstr(argv[i], "-dilate")) {
                unsigned char* dilated = dilation(binary, img.width, img.height);
                saveTransformation("5_dilated.pgm", outputPrefix, dilated, img.width, img.height);

                free(dilated);
            }

            if (strstr(argv[i], "-opening")) {
                unsigned char* eroded = erosion(binary, img.width, img.height);
                unsigned char* opening = dilation(eroded, img.width, img.height);
                saveTransformation("6_opening.pgm", outputPrefix, opening, img.width, img.height);

                if (strstr(argv[i+1], "-top")) {
                    //Top Hat
                    unsigned char* top_hat = morphHat(binary, opening, img.width, img.height);
                    saveTransformation("7_top_hat.pgm", outputPrefix, top_hat, img.width, img.height);

                    free(top_hat);
                }
                
                free(eroded);
                free(opening);
            }

            if (strstr(argv[i], "-closing")) {
                unsigned char* dilated = dilation(binary, img.width, img.height);
                unsigned char* closing = erosion(dilated, img.width, img.height);
                saveTransformation("8_closing.pgm", outputPrefix, closing, img.width, img.height);

                if (strstr(argv[i+1], "-bottom")) {
                    //Bottom Hat
                    unsigned char* bottom_hat = morphHat(binary, closing, img.width, img.height);
                    saveTransformation("9_bottom_hat.pgm", outputPrefix, bottom_hat, img.width, img.height);

                    free(bottom_hat);
                }
            
                free(dilated);
                free(closing);
            }
        }

        // Free memory
        free(img.data);
        free(grayscale);
        free(binary);
        free(edges);

        printf("To diplay output images use these commands:\n");
        printf("montage [images] -tile [width x height] -geometry +10+10 output.ppm\ndisplay output.ppm\n");
    }

    return 0;
}
