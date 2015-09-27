#ifndef BITMAP_PNG_H
#define BITMAP_PNG_H

#include <png.h>

namespace hsm{

bitmap::pixel_format png_format(int color_type, char *internal_format){
    switch(color_type){
    case PNG_COLOR_TYPE_GRAY:
        *internal_format = 1;
        return bitmap::pixel_format::gray;
    case PNG_COLOR_TYPE_GRAY_ALPHA:
        *internal_format = 2;
        return bitmap::pixel_format::gray_alpha;
    case PNG_COLOR_TYPE_RGB:
        *internal_format = 3;
        return bitmap::pixel_format::rgb;
    case PNG_COLOR_TYPE_RGB_ALPHA:
        *internal_format = 4;
        return bitmap::pixel_format::rgba;
    default:
        break;
    }
    *internal_format = 0;
    return bitmap::pixel_format::invalid;
}

struct png_buffer_t{
    const bytearray *data;
    int offset;
};

static void png_read_from_mem(png_structp png_ptr, png_bytep data, png_size_t lenght){
    png_buffer_t *src = (png_buffer_t *)png_get_io_ptr(png_ptr);
    memcpy(data, src->data->data()+src->offset, lenght);
    src->offset += lenght;
}

static uint8 *fromPNG(const bytearray & data, bool *ok, bitmap::pixel_format *format, char *internal_format, int *width, int *height){
    *ok = false;
    if(data.size() < 8)
        return 0;
    // magic number
    char magic[8] = {data[0], data[1], data[2], data[3],
                        data[4], data[5], data[6], data[7]};
    if(!png_check_sig((png_bytep)magic, sizeof(magic))){
        return 0;
    }
    png_structp png_ptr = png_create_read_struct(
                PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png_ptr){
        //cerr << "cannot create png_struct" << endl;
        return 0;
    }
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if(!info_ptr){
        //cerr << "cannot create png_info" << endl;
        return 0;
    }
    uint8 *d = 0;
    // errors
    if(setjmp(png_jmpbuf(png_ptr))){
        *format = bitmap::pixel_format::invalid;
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        if(d){
            delete[] d;
        }
        return NULL;
    }
    // read
    png_buffer_t src;
    src.data = &data;
    src.offset = 0;
    png_set_read_fn(png_ptr, (png_voidp *)&src, png_read_from_mem);
    png_read_info(png_ptr, info_ptr);
    //
    int bit_depth, color_type;
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);
    if(color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png_ptr);
    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png_ptr);
    if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png_ptr);
    if(bit_depth == 16)
        png_set_strip_16(png_ptr);
    else if(bit_depth < 8)
        png_set_packing(png_ptr);
    png_read_update_info(png_ptr, info_ptr);
    //
    png_uint_32 w, h;
    png_get_IHDR (png_ptr, info_ptr, &w, &h, &bit_depth,
                  &color_type, NULL, NULL, NULL);
    //
    *format = png_format(color_type, internal_format);
    if(*format == bitmap::pixel_format::invalid){
        //cerr << "invalid image format" << endl;
        return 0;
    }
    *width = w;
    *height = h;
    d = new uint8[w*h*(*internal_format)];
    //
    png_bytep *row_pointers = new png_bytep[sizeof(png_bytep)*h];
    for(unsigned int i = 0; i < h; ++i){
        //row_pointers[i] = (png_bytep)(d+(h-i-1)*w*(*internal_format));
        row_pointers[i] = (png_bytep)(d+i*w*(*internal_format));
    }
    png_read_image(png_ptr, row_pointers);
    //
    delete[] row_pointers;
    png_read_end(png_ptr, NULL);
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    //
    *ok = true;
    return d;
}

}

#endif // BITMAP_PNG_H
