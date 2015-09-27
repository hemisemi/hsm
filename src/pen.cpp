#include "pen.h"

namespace hsm{

pen::pen(){
    _null = true;
}

pen::pen(const hsm::color &c){
    _color = c;
    _null = false;
}

const color & pen::color() const{
    return _color;
}

void pen::setColor(const hsm::color &c){
    _color = c;
    _null = false;
}

bool pen::isNull() const{
    return _null;
}

}
