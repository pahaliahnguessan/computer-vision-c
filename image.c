#include "image.h"
#include <stdio.h>
#include <stdlib.h>

Image loadPPM(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Error opening file\n");
        exit(1);
    }
    Image img;
    fscanf(file, "P6\n%d %d\n255\n", &img.width, &img.height);
    img.data = (unsigned char*)malloc(3 * img.width * img.height);
    fread(img.data, 3, img.width * img.height, file);
    fclose(file);
    return img;
}

void savePPM(const char* filename, unsigned char* data, int width, int height) { 
    char filePath[256];
    sprintf(filePath, "outputImages/%s", filename); 
    FILE* file = fopen(filePath, "wb");
    if (file == NULL) {
        printf("Error occurred in saving file'%s'\n", filePath);
        return;
    }
    fprintf(file, "P5\n%d %d\n255\n", width, height);
    fwrite(data, 1, width * height, file);
    fclose(file);
}

void saveTransformation(unsigned char* saving_name, unsigned char* output_prefix, unsigned char* file, int w, int h) {
    char outputFile[256];
    sprintf(outputFile, "%s%s", output_prefix, saving_name);
    savePPM(outputFile, file, w, h);
    printf("Saved: %s\n", outputFile);
}

