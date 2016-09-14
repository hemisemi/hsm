#include "bitmap.h"
#include <png.h>
#include <cstring>
#include <iostream>
#include "bytearray.h"
/*#include "file.h"
#include "bitmap_paintengine.h"

#include "private/bitmap_png.h"
#include "private/bitmap_bmp.h"
#include "private/bitmap_jpeg.h"*/

namespace hsm{

bitmap::bitmap(){
    _width = 0;
    _height = 0;
    _stride = 0;
    _data = 0;
    _format = pixel_format::invalid;
    _depth = 0;
}

bitmap::bitmap(uint8_t *data, size_t width, size_t height, bitmap::pixel_format format, bool copy){
    _width = width;
    _height = height;
    _stride = _width;
    _format = format;
    if(copy){
        _data = new uint8_t[length()];
        memcpy(_data, data, length());
    }else{
        _data = data;
    }
}

bitmap::bitmap(uint8_t *data, size_t width, size_t height, bitmap::pixel_format format, size_t stride, bool copy){
    _width = width;
    _height = height;
    _format = format;
    _stride = stride;
    if(copy){
        _data = new uint8_t[length()];
        memcpy(_data, data, length());
    }else{
        _data = data;
    }
}

bitmap::bitmap(size_t width, size_t height, bitmap::pixel_format format) : bitmap(){
    _width = width;
    _height = height;
    _format = format;
    _stride = _width;
    _data = new uint8_t[length()];
    clear();
}

bitmap::bitmap(size_t width, size_t height, bitmap::pixel_format format, size_t stride) : bitmap(){
    _width = width;
    _height = height;
    _format = format;
    _stride = stride;
    _data = new uint8_t[length()];
    clear();
}

bitmap::bitmap(const hsm::bitmap &bitmap){
    _width = bitmap._width;
    _height = bitmap._height;
    _format = bitmap._format;
    _stride = bitmap._stride;
    _data = new uint8_t[length()];
    memcpy(_data, bitmap._data, length());
}

bitmap & bitmap::operator=(const hsm::bitmap & bitmap){
    if(bitmap._data == _data)
        return *this;
    _width = bitmap._width;
    _height = bitmap._height;
    _format = bitmap._format;
    _data = new uint8_t[length()];
    memcpy(_data, bitmap._data, length());
    return *this;
}

bitmap::~bitmap(){
    delete[] _data;
}

bitmap::pixel_format bitmap::format() const{
    return _format;
}

void bitmap::setFormat(bitmap::pixel_format format){
    if(_data && format != bitmap::pixel_format::invalid && format != _format){
        size_t depth = bitmap::depth(format);
        uint8_t *data = new uint8_t[length()];
        //
        uint8_t *src = _data;
        uint8_t *dst = data;
        while(src < _data+(length())){
            uint8_t red = src[0];
            uint8_t green = src[0];
            uint8_t blue = src[0];
            uint8_t alpha = 255;
            switch(_format){
            case pixel_format::gray_alpha:
                alpha = src[1];
                break;
            case pixel_format::rgb:
                green = src[1];
                blue = src[2];
                break;
            case pixel_format::argb:
                alpha = src[0];
                red = src[1];
                green = src[2];
                blue = src[3];
                break;
            default:
                break;
            }
            switch(format){
            case pixel_format::gray:
                dst[0] = red;
                break;
            case pixel_format::gray_alpha:
                dst[0] = red;
                dst[1] = alpha;
                break;
            case pixel_format::rgb:
                dst[0] = red;
                dst[1] = green;
                dst[2] = blue;
                break;
            case pixel_format::argb:
                dst[0] = alpha;
                dst[1] = red;
                dst[2] = green;
                dst[3] = blue;
                break;
            default:
                delete[] data;
                return;
            }
            //
            dst += depth;
            src += this->depth();
        }
        //
        delete[] _data;
        _data = data;
        refresh();
    }
}

static color src_pixel(uint8_t *src, int internal_format){
    switch(internal_format){
    case 1:
        return color(src[0], src[0], src[0]);
    case 2:
        return color(src[0], src[0], src[0], src[1]);
    case 3:
        return color(src[0], src[1], src[2]);
    case 4:
        return color(src[1], src[2], src[3], src[0]);
    default:
        break;
    }
    return color();
}

static void dst_pixel(uint8_t *dst, const color & color, int internal_format){
    switch(internal_format){
    case 1:
        dst[0] = color.red();
        break;
    case 2:
        dst[0] = color.red();
        dst[1] = color.alpha();
        break;
    case 3:
        dst[0] = color.red();
        dst[1] = color.green();
        dst[2] = color.blue();
        break;
    case 4:
        dst[0] = color.alpha();
        dst[1] = color.red();
        dst[2] = color.green();
        dst[3] = color.blue();
        break;
    default:
        break;
    }
}

/*void bitmap::hueChange(int hue){
    uint8 *src = _data;
    uint8 *end = _data+(_width*_height*_internal_format);
    while(src < end){
        color::HSV hsv = src_pixel(src, _internal_format).toHSV();
        hsv.hue = hsv.hue+hue;
        dst_pixel(src, color::fromHSV(hsv), _internal_format);
        src += _internal_format;
    }
}*/

void bitmap::clear(){
    if(_data){
        memset(_data, 0, length());
        refresh();
    }
}

bitmap bitmap::copy(const hsm::rect &rect) const{
    if(rect.width() == 0 || rect.height() == 0){
        return copy(0, 0, width(), height());
    }
    return copy(rect.x(), rect.y(), rect.width(), rect.height());
}

bitmap bitmap::copy(int x, int y, int w, int h) const{
    y = height()-y-h;
    bitmap bmp;
    bmp._width = w;
    bmp._height = h;
    bmp._format = _format;
    bmp._data = new uint8_t[w*h*depth()];
    for(int r = 0; r < h; ++r){
        memcpy(bmp._data+(r*w*depth()), _data+(((r+y)*stride())+x)*depth(), w*depth());
    }
    return bmp;
}

size_t bitmap::width() const{
    return _width;
}

size_t bitmap::height() const{
    return _height;
}

size_t bitmap::stride() const{
    return _stride;
}

size_t bitmap::depth(pixel_format format){
    switch(format){
    case bitmap::pixel_format::gray:
        return 1;
    case bitmap::pixel_format::gray_alpha:
        return 2;
    case bitmap::pixel_format::rgb:
        return 3;
    case bitmap::pixel_format::argb:
        return 4;
    case bitmap::pixel_format::invalid:
    default:
        break;
    }
    return 0;
}

size_t bitmap::depth() const{
    return depth(_format);
}

color bitmap::pixel(int x, int y) const{
    uint8_t *src = _data+(_stride*y+x)*depth();
    return src_pixel(src, depth());
}

void bitmap::setPixel(int x, int y, const color &color){
    uint8_t *dst = _data+(_stride*y+x)*depth();
    dst_pixel(dst, color, depth());
}

bitmap bitmap::scaled(int width, int height, bitmap::transformation t) const{
    uint8_t *data = new uint8_t[length()];
    switch(t){
    case transformation::fast:
    {
        uint8_t *dst = data;
        int y = 0;
        int x = 0;
        for(int i = 0; i < width*height; ++i){
            color c = pixel(x*_width/width, y*_height/height);
            switch(depth()){
            case 1:
                dst[0] = c.red();
                break;
            case 2:
                dst[0] = c.red();
                dst[1] = c.green();
                break;
            case 3:
                dst[0] = c.red();
                dst[1] = c.green();
                dst[2] = c.blue();
                break;
            case 4:
                dst[0] = c.alpha();
                dst[1] = c.red();
                dst[2] = c.green();
                dst[3] = c.blue();
                break;
            default:
                return bitmap();
            }
            dst += depth();
            ++x;
            if(x >= width){
                x = 0;
                ++y;
            }
        }
    }
        break;
    case transformation::smooth:
    {
        float dx = 1.0/_width;
        float dy = 1.0/_height;
        float dxyi = 1.0/(dx*dy)*255;
        uint8_t *dst = data;
        int x1i, x2i, y1i, y2i;
        float sx, sy, x1, x2, y1, y2, xf, yf;
        color q11, q21, q12, q22;
        int y = 0;
        int x = 0;
        for(int i = 0; i < width*height; ++i){
        /*for(int y = 0; y < height; ++y){
            for(int x = 0; x < width; ++x){*/
            sx = x*_width/width;
            sy = y*_height/height;
            x1i = (int)sx;
            x2i = x1i+1;
            y1i = (int)sy;
            y2i = y1i+1;
            x1 = (float)x1i/_width;
            x2 = (float)x2i/_width;
            y1 = (float)y1i/_height;
            y2 = (float)y2i/_height;
            xf = (float)x/width;
            yf = (float)y/height;
            q11 = pixel(x1i, y1i);
            q21 = pixel(x2i, y1i);
            q12 = pixel(x1i, y2i);
            q22 = pixel(x2i, y2i);
            float a = ((x2-xf)*(y2-yf));
            float b = ((xf-x1)*(y2-yf));
            float c = ((x2-xf)*(yf-y1));
            float d = ((xf-x1)*(yf-y1));
            int red = dxyi*((q11.redf()*a)
                                     +(q21.redf()*b)
                                     +(q12.redf()*c)
                                     +(q22.redf()*d));
            int green = dxyi*((q11.greenf()*a)
                              +(q21.greenf()*b)
                              +(q12.greenf()*c)
                              +(q22.greenf()*d));
            int blue = dxyi*((q11.bluef()*a)
                             +(q21.bluef()*b)
                             +(q12.bluef()*c)
                             +(q22.bluef()*d));
            int alpha = dxyi*((q11.bluef()*a)
                              +(q21.alphaf()*b)
                              +(q12.alphaf()*c)
                              +(q22.alphaf()*d));
            //uint8 *dst = data+(width*y+x)*_internal_format;
            switch(depth()){
            case 1:
                dst[0] = red;
                break;
            case 2:
                dst[0] = red;
                dst[1] = green;
                break;
            case 3:
                dst[0] = red;
                dst[1] = green;
                dst[2] = blue;
                break;
            case 4:
                dst[0] = alpha;
                dst[1] = red;
                dst[2] = green;
                dst[3] = blue;
                break;
            default:
                return bitmap();
            }
            dst += depth();
            ++x;
            if(x >= width){
                x = 0;
                ++y;
            }
            //}
        }
    }
        break;
    }
    return bitmap(data, width, height, _format, false);
}

rect bitmap::rect() const{
    return hsm::rect(0, 0, _width, _height);
}

/*void bitmap::bind() const{
    if(_map.find(GraphicContext::current()) != _map.end()){
        uint id = _map.at(GraphicContext::current());
        GraphicContext::current()->bindTexture(id);
    }else{
        uint id = 0;
        _map[GraphicContext::current()] = (id = GraphicContext::current()->getTextureId(_data, _internal_format, _width, _height));
        GraphicContext::current()->bindTexture(id);
    }
}*/

void bitmap::refresh(){
    /*for(std::pair<GraphicContext *, uint> pair : _map){
        pair.first->refreshTexture(pair.second, _data, _internal_format, _width, _height);
    }*/
}

/*void bitmap::release() const{
    if(_map.find(GraphicContext::current()) != _map.end()){
        GraphicContext::current()->releaseTexture();
    }
}*/

/*void bitmap::dispose(){
    if(_data){
        delete[] _data;
        _data = 0;
        for(std::pair<GraphicContext *, uint> pair : _map){
            pair.first->destroyTexture(pair.second);
        }
    }
}*/

const uint8_t *bitmap::data() const{
    return _data;
}

size_t bitmap::length() const{
    return _stride*_height*depth();
}

/*paintengine *bitmap::paint_engine() const{
    return new bitmap_paintengine;
}*/

}
