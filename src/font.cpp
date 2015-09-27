#include "font.h"
#include "fontlibrary.h"
#include "fontmetrics.h"

namespace hsm{

font::font(const std::string & family, int pixel_size, Style style){
    _family = family;
    _pixel_size = pixel_size;
    _style = style;
    _raw = 0;
    _update();
}

bool font::exists(const std::string & family){
    return fontlibrary::exists(family);
}

rawfont *font::raw() const{
    return _raw;
}

fontmetrics font::metrics() const{
    return fontmetrics(*this);
}

const std::string & font::family() const{
    return _family;
}

void font::setFamily(const std::string & str){
    _family = str;
    _update();
}

int font::pixelSize() const{
    return _pixel_size;
}

void font::setPixelSize(int size){
    _pixel_size = size;
    _update();
}

font::Style font::style() const{
    return _style;
}

void font::setStyle(Style style){
    _style = style;
    _update();
}

void font::_update(){
    _raw = fontlibrary::query(_family, _style);
}

}
