#include "sizef.h"

namespace hsm{

sizef::sizef(float width, float height){
    _w = width;
    _h = height;
}

float sizef::width() const{
    return _w;
}

float sizef::height() const{
    return _h;
}

void sizef::set_width(float width){
    if(width < 0)
        width = 0;
    _w = width;
}

void sizef::set_height(float height){
    if(height < 0)
        height = 0;
    _h = height;
}

void sizef::set(float width, float height){
    set_width(width);
    set_height(height);
}

float sizef::surface() const{
    return _w*_h;
}

}
