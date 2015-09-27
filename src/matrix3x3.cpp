#include "matrix3x3.h"
#include "algorithm.h"
#include <cstring>
#include <math.h>

#define PI 3.14159265359

namespace hsm{

matrix3x3::matrix3x3(){
    set_to_identity();
}

matrix3x3::matrix3x3(const matrix3x3 & m){
    memcpy(_data, m._data, 9*sizeof(float));
    _flags = m._flags;
}

matrix3x3::matrix3x3(float *data, Format format){
    _flags = Any;
    if(data == (float*)(void*)1)
        memset(_data, 0, 9*sizeof(float));
    else{
        memcpy(_data, data, 9*sizeof(float));
        if(format != ColumnMajorFormat)
            transpose();
        optimize();
    }
}

bool matrix3x3::identity() const{
    if(_flags == Identity)
        return true;
    bool i = _data[0][0] == 1.0 && _data[1][0] == 0.0 && _data[2][0] == 0.0
            && _data[0][1] == 1.0 && _data[1][1] == 1.0 && _data[2][1] == 0.0
            && _data[0][2] == 1.0 && _data[1][2] == 0.0 && _data[2][2] == 1.0;
    if(i)
        _flags = Identity;
    return i;
}

void matrix3x3::set_to_identity(){
    _data[0][0] = 1.0;
    _data[0][1] = 0.0;
    _data[0][2] = 0.0;
    _data[1][0] = 0.0;
    _data[1][1] = 1.0;
    _data[1][2] = 0.0;
    _data[2][0] = 0.0;
    _data[2][1] = 0.0;
    _data[2][2] = 1.0;
}

void matrix3x3::transpose(){
    float tmp;
    for(int row = 0; row < 3; ++row){
        for (int col = 0; col < 3; ++col){
            tmp = _data[row][col];
            _data[row][col] = _data[col][row];
            _data[col][row] = tmp;
        }
    }
}

void matrix3x3::optimize(){
    // If the last element is not 1, then it can never be special.
    if(_data[2][2] != 1.0f){
        _flags = Any;
        return;
    }
    if(_data[0][1] != 0.0f || _data[0][2] != 0.0f || _data[1][0] != 0.0f || _data[1][2] != 0.0f){
        _flags = Any;
        return;
    }
    bool translationPresent = (_data[2][0] != 0.0f || _data[2][1] != 0.0f);
    bool identityAlongDiagonal = (_data[0][0] == 1.0f && _data[1][1] == 1.0f);
    _flags = 0;
    if(translationPresent)
        _flags |= Translation;
    if(!identityAlongDiagonal)
        _flags |= Scale;
    if(identityAlongDiagonal && !translationPresent)
        _flags = Identity;
}

bool matrix3x3::invertible() const{
    return !fuzzy_is_null(determinant());
}

bool matrix3x3::scaling() const{
    return _flags & Scale;
}

bool matrix3x3::rotating() const{
    return _flags & Rotation;
}

bool matrix3x3::translating() const{
    return _flags & Translation;
}

bool matrix3x3::affine() const{
    return _flags != Any && !(_flags & Projection);
}

int matrix3x3::type() const{
    return _flags;
}

// The 4x4 matrix inverse algorithm is based on that described at:
// http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q24
// Some optimization has been done by Qt to avoid making copies of 3x3
// sub-matrices and to unroll the loops.
// Calculate the determinant of a 3x3 sub-matrix.
//     | A B C |
// M = | D E F |    det(M) = A * (EI - HF) - B * (DI - GF) + C * (DH - GE)
//     | G H I |
float matrix3x3::determinant() const{
    return _data[0][0] * (_data[1][1] * _data[2][2] - _data[1][2] * _data[2][1])
        - _data[1][0] * (_data[0][1] * _data[2][2] - _data[0][2] * _data[2][1])
        + _data[2][0] * (_data[0][1] * _data[1][2] - _data[0][2] * _data[1][1]);
}

float matrix3x3::at(int row, int column) const{
    return _data[column][row];
}

const float & matrix3x3::operator ()(int row, int column) const{
    return _data[column][row];
}

float & matrix3x3::operator ()(int row, int column){
    return _data[column][row];
}

}
