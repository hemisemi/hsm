#include "pointf.h"

namespace hsm{

pointf::pointf(float x, float y){
    _x = x;
    _y = y;
}

pointf::pointf() : pointf(0, 0){
    //
}

float pointf::x() const{
    return _x;
}

float pointf::y() const{
    return _y;
}

void pointf::set_x(float x){
    _x = x;
}

void pointf::set_y(float y){
    _y = y;
}

void pointf::set(float x, float y){
    _x = x;
    _y = y;
}

pointf pointf::operator +(const pointf & point) const{
    return pointf(_x+point.x(), _y+point.y());
}

pointf pointf::operator -(const pointf & point) const{
    return pointf(_x-point.x(), _y-point.y());
}

pointf pointf::operator -() const{
    return pointf(-_x, -_y);
}

pointf pointf::operator +() const{
    return *this;
}

const pointf & pointf::operator +=(const pointf & point){
    _x += point.x();
    _y += point.y();
    return *this;
}

const pointf & pointf::operator -=(const pointf & point){
    _x -= point.x();
    _y -= point.y();
    return *this;
}

bool pointf::operator ==(const pointf & point) const{
    return (_x == point.x() && _y == point.y());
}

bool pointf::operator !=(const pointf & point) const{
    return (_x != point.x() || _y != point.y());
}

}

/*swapi::TextStream & operator << (swapi::TextStream & stream, const swapi::PointF & value){
    return stream << "(" << value.x() << ", " << value.y() << ")";
}*/
