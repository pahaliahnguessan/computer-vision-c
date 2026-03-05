#ifndef IMAGE_H
#define IMAGE_H

typedef struct {
    int width, height;
    unsigned char* data;
} Image;

Image loadPPM(const char* filename);
void savePPM(const char* filename, unsigned char* data, int width, int height);
void saveTransformation(unsigned char* saving_name, unsigned char* output_prefix, unsigned char* file, int w, int h);

#endif
