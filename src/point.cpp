#include "point.h"

namespace hsm{

point::point(int x, int y){
    _x = x;
    _y = y;
}

point::point() : point(0, 0){
    //
}

int point::x() const{
    return _x;
}

int point::y() const{
    return _y;
}

void point::set_x(int x){
    _x = x;
}

void point::set_y(int y){
    _y = y;
}

void point::set(int x, int y){
    _x = x;
    _y = y;
}

point point::operator +(const hsm::point & point) const{
    return hsm::point(_x+point.x(), _y+point.y());
}

point point::operator -(const hsm::point & point) const{
    return hsm::point(_x-point.x(), _y-point.y());
}

point point::operator -() const{
    return hsm::point(-_x, -_y);
}

point point::operator +() const{
    return *this;
}

const point & point::operator +=(const hsm::point & point){
    _x += point.x();
    _y += point.y();
    return *this;
}

const point & point::operator -=(const hsm::point & point){
    _x -= point.x();
    _y -= point.y();
    return *this;
}

bool point::operator ==(const hsm::point & point) const{
    return (_x == point.x() && _y == point.y());
}

bool point::operator !=(const hsm::point & point) const{
    return (_x != point.x() || _y != point.y());
}

}

/*swapi::TextStream & operator << (swapi::TextStream & stream, const swapi::point & value){
    return stream << "(" << value.x() << ", " << value.y() << ")";
}*/
