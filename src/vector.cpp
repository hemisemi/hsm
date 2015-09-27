#include "vector.h"
#include <cstring>
#include <math.h>

namespace hsm{

vector3d::vector3d(){
    memset(_data, 0, 3*sizeof(float));
}

vector3d::vector3d(const vector3d & v){
    memcpy(_data, v._data, 3*sizeof(float));
}

vector3d::vector3d(float x, float y, float z){
    _data[0] = x;
    _data[1] = y;
    _data[2] = z;
}

vector3d::vector3d(float *data){
    memcpy(_data, data, 3*sizeof(float));
}

float vector3d::distance(const vector3d & v) const{
    return (operator-(v)).length();
}

bool vector3d::isNull() const{
    return _data[0] == 0.0f && _data[1] == 0.0f && _data[2] == 0.0f;
}

float vector3d::length() const{
    return sqrt(_data[0]*_data[0]+_data[1]*_data[1]+_data[2]*_data[2]);
}

float vector3d::x() const{
    return _data[0];
}

float vector3d::y() const{
    return _data[1];
}

float vector3d::z() const{
    return _data[2];
}

void vector3d::setX(float v){
    _data[0] = v;
}

void vector3d::setY(float v){
    _data[1] = v;
}

void vector3d::setZ(float v){
    _data[2] = v;
}

void vector3d::set(float x, float y, float z){
    _data[0] = x;
    _data[1] = y;
    _data[2] = z;
}

void vector3d::normalize(){
    float len = length();
    _data[0] /= len;
    _data[1] /= len;
    _data[2] /= len;
}

vector3d vector3d::normalized() const{
    vector3d v(*this);
    v.normalize();
    return v;
}

void vector3d::operator +=(const vector3d & v){
    _data[0] += v.x();
    _data[1] += v.y();
    _data[2] += v.z();
}

void vector3d::operator -=(const vector3d & v){
    _data[0] -= v.x();
    _data[1] -= v.y();
    _data[2] -= v.z();
}

void vector3d::operator *=(float factor){
    _data[0] *= factor;
    _data[1] *= factor;
    _data[2] *= factor;
}

void vector3d::operator /=(float factor){
    _data[0] /= factor;
    _data[1] /= factor;
    _data[2] /= factor;
}

vector3d vector3d::operator +(const vector3d & v) const{
    vector3d r(*this);
    r += v;
    return r;
}

vector3d vector3d::operator -(const vector3d & v) const{
    vector3d r(*this);
    r -= v;
    return r;
}

vector3d vector3d::operator *(float factor) const{
    vector3d r(*this);
    r *= factor;
    return r;
}

vector3d vector3d::operator /(float factor) const{
    vector3d r(*this);
    r /= factor;
    return r;
}

vector3d vector3d::operator -() const{
    return vector3d(-_data[0], -_data[1], -_data[2]);
}

vector3d vector3d::crossProduct(const vector3d &a, const vector3d &b){
    return vector3d(a.y() * b.z() - a.z() * b.y(),
                    a.z() * b.x() - a.x() * b.z(),
                    a.x() * b.y() - a.y() * b.x());
}

float vector3d::dotProduct(const vector3d &a, const vector3d &b){
    return (a.x()*b.x())+(a.y()*b.y())+(a.z()*b.z());
}

const float *vector3d::data() const{
    return _data;
}

}

std::ostream & operator<<(std::ostream & stream, const hsm::vector3d & v){
    return (stream << "(" << v.x() << ", " << v.y() << ", " << v.z() << ")");
}
