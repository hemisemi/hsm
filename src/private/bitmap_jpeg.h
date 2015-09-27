#ifndef BITMAP_JPEG_H
#define BITMAP_JPEG_H

#include <jpeglib.h>

namespace hsm{

const static JOCTET EOI_BUFFER[1] = {JPEG_EOI};

struct swjpeg_source_mgr{
    struct jpeg_source_mgr pub;
    const JOCTET *data;
    size_t       len;
};

static void swjpeg_init_source(j_decompress_ptr){
    //
}

static boolean swjpeg_fill_input_buffer(j_decompress_ptr cinfo) {
    swjpeg_source_mgr* src = (swjpeg_source_mgr*)cinfo->src;
    // No more data.  Probably an incomplete image;  just output EOI.
    src->pub.next_input_byte = EOI_BUFFER;
    src->pub.bytes_in_buffer = 1;
    return TRUE;
}

static void swjpeg_skip_input_data(j_decompress_ptr cinfo, long num_bytes) {
    swjpeg_source_mgr* src = (swjpeg_source_mgr*)cinfo->src;
    if(src->pub.bytes_in_buffer < (unsigned long)num_bytes) {
        // Skipping over all of remaining data;  output EOI.
        src->pub.next_input_byte = EOI_BUFFER;
        src->pub.bytes_in_buffer = 1;
    }else{
        // Skipping over only some of the remaining data.
        src->pub.next_input_byte += num_bytes;
        src->pub.bytes_in_buffer -= num_bytes;
    }
}

static void swjpeg_term_source(j_decompress_ptr){
    //
}

static void swjpeg_set_source_mgr(j_decompress_ptr cinfo, const char* data, size_t len){
    swjpeg_source_mgr* src;
    if (cinfo->src == 0) { // if this is first time;  allocate memory
    cinfo->src = (struct jpeg_source_mgr *)(*cinfo->mem->alloc_small)
        ((j_common_ptr) cinfo, JPOOL_PERMANENT, sizeof(swjpeg_source_mgr));
    }
    src = (swjpeg_source_mgr*) cinfo->src;
    src->pub.init_source = swjpeg_init_source;
    src->pub.fill_input_buffer = swjpeg_fill_input_buffer;
    src->pub.skip_input_data = swjpeg_skip_input_data;
    src->pub.resync_to_restart = jpeg_resync_to_restart; // default
    src->pub.term_source = swjpeg_term_source;
    // fill the buffers
    src->data = (const JOCTET *)data;
    src->len = len;
    src->pub.bytes_in_buffer = len;
    src->pub.next_input_byte = src->data;
}

static uint8 *fromJPEG(const bytearray & data, bool *ok, bitmap::pixel_format *format, char *internal_format, int *width, int *height){
    *ok = false;
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    // setup decompression structure
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    swjpeg_set_source_mgr(&cinfo, data.data(), data.size());
    // read info from header
    int r = jpeg_read_header(&cinfo, TRUE);
    if(r == JPEG_SUSPENDED){
        return 0;
    }

    int n = 0;
    if(cinfo.out_color_space == JCS_RGB){
        n = 3;
        *format = bitmap::pixel_format::rgb;
    }else if(cinfo.out_color_space == JCS_GRAYSCALE){
        n = 1;
        *format = bitmap::pixel_format::gray;
    }else{
        return 0;
    }
    *internal_format = n;

    jpeg_start_decompress(&cinfo);

    *width = cinfo.output_width;
    *height = cinfo.output_height;

    uint8 *bytes = new uint8[cinfo.output_width*cinfo.output_height*n];
    while(cinfo.output_scanline < cinfo.output_height){
        //uint8 *pos = bytes+(cinfo.output_width*n*(cinfo.output_height-cinfo.output_scanline-1));
        uint8 *pos = bytes+(cinfo.output_width*n*cinfo.output_scanline);
        jpeg_read_scanlines(&cinfo, &pos, 1);
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    *ok = true;
    return bytes;
}

}

#endif // BITMAP_JPEG_H
