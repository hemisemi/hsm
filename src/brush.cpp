#include "brush.h"

namespace hsm{

brush::brush(){
    _null = true;
}

brush::brush(const hsm::color &color){
    _color = color;
    _null = false;
}

const color & brush::color() const{
    return _color;
}

void brush::setColot(const hsm::color &color){
    _color = color;
    _null = false;
}

bool brush::isNull() const{
    return _null;
}

}
