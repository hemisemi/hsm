#include "size.h"

namespace hsm{

size::size(int width, int height){
    _w = width;
    _h = height;
}

int size::width() const{
    return _w;
}

int size::height() const{
    return _h;
}

void size::set_width(int width){
    if(width < 0)
        width = 0;
    _w = width;
}

void size::set_height(int height){
    if(height < 0)
        height = 0;
    _h = height;
}

void size::set(int width, int height){
    set_width(width);
    set_height(height);
}

int size::surface() const{
    return _w*_h;
}

}
