#ifndef BITMAP_BMP_H
#define BITMAP_BMP_H

#include <ios>
#include "../bytearray.h"

namespace hsm{

/*typedef struct tagBITMAPFILEHEADER{
    WORD bfType;  //specifies the file type
    DWORD bfSize;  //specifies the size in bytes of the bitmap file
    WORD bfReserved1;  //reserved; must be 0
    WORD bfReserved2;  //reserved; must be 0
    DWORD bOffBits;  //species the offset in bytes from the bitmapfileheader to the bitmap bits
}BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{
    DWORD biSize;  //specifies the number of bytes required by the struct
    LONG biWidth;  //specifies width in pixels
    LONG biHeight;  //species height in pixels
    WORD biPlanes; //specifies the number of color planes, must be 1
    WORD biBitCount; //specifies the number of bit per pixel
    DWORD biCompression;//spcifies the type of compression
    DWORD biSizeImage;  //size of image in bytes
    LONG biXPelsPerMeter;  //number of pixels per meter in x axis
    LONG biYPelsPerMeter;  //number of pixels per meter in y axis
    DWORD biClrUsed;  //number of colors used by th ebitmap
    DWORD biClrImportant;  //number of colors that are important
}BITMAPINFOHEADER;*/

/*static unsigned int bmp_read(void *dest, size_t len, unsigned int count, const ByteArray & data, unsigned int pos){
    len *= count;
    if(pos+len > data.size())
        return pos;
    memcpy(dest, data->data()+pos, len);
    return pos+len;
}

static uint8 *fromBMP(const ByteArray & data, bool *ok, Bitmap::Format *format, char *internal_format, int *width, int *height){
    *ok = false;
    unsigned int pos = 0;

    BITMAPFILEHEADER bitmapFileHeader; //our bitmap file header
    BITMAPINFOHEADER bitmapInfoHeader;

    unsigned char *bitmapImage;  //store image data
    int imageIdx = 0;  //image index counter
    unsigned char tempRGB;  //our swap variable

    //read the bitmap file header
    pos = bmp_read(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, data, pos);
    //verify that this is a bmp file by check bitmap id
    if(bitmapFileHeader.bfType != 0x4D42)
        return 0;

    //read the bitmap info header
    pos = bmp_read(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, data, pos);

    //move file point to the begging of bitmap data
    pos = bitmapFileHeader.bfOffBits;

    //allocate enough memory for the bitmap image data
    bitmapImage = (unsigned char*)malloc(bitmapInfoHeader.biSizeImage);

    //verify memory allocation
    if(!bitmapImage){
        free(bitmapImage);
        return 0;
    }

    //read in the bitmap image data
    pos = bmp_read(&bitmapImage, bitmapInfoHeader->biSizeImage, 1, data, pos);

    //make sure bitmap image data was read
    if (bitmapImage == NULL){
        fclose(file);
        return NULL;
    }

    //swap the r and b values to get RGB (bitmap is BGR)
    for(imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3){
        tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx + 2] = tempRGB;
    }

    *format = Bitmap::Format_RGB;
    *internal_format = 3;
    *width = bitmapInfoHeader.biWidth;
    *height = bitmapInfoHeader.biHeight;

    return bitmapImage;
}*/

}


#endif // BITMAP_BMP_H
