#include "matrix4x4.h"
#include <cstring>
#include <math.h>

#define PI 3.14159265359

namespace hsm{

matrix4x4::matrix4x4(){
    set_to_identity();
}

matrix4x4::matrix4x4(const matrix4x4 & m){
    memcpy(_data, m._data, 16*sizeof(float));
    _flags = m._flags;
}

matrix4x4::matrix4x4(float *data, Format format){
    _flags = Any;
    if(data == (float*)(void*)1)
        memset(_data, 0, 16*sizeof(float));
    else{
        memcpy(_data, data, 16*sizeof(float));
        if(format != ColumnMajorFormat)
            transpose();
        optimize();
    }
}

matrix4x4::matrix4x4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44){
    _flags = Any;
    set(m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44);
    optimize();
}

void matrix4x4::set(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44){
    _data[0][0] = m11;
    _data[0][1] = m12;
    _data[0][2] = m13;
    _data[0][3] = m14;
    _data[1][0] = m21;
    _data[1][1] = m22;
    _data[1][2] = m23;
    _data[1][3] = m24;
    _data[2][0] = m31;
    _data[2][1] = m32;
    _data[2][2] = m33;
    _data[2][3] = m34;
    _data[3][0] = m41;
    _data[3][1] = m42;
    _data[3][2] = m43;
    _data[3][3] = m44;
}

void matrix4x4::optimize(){
    // If the last element is not 1, then it can never be special.
    if(_data[3][3] != 1.0f){
        _flags = Any;
        return;
    }
    // If the upper three elements m12, m13, and m21 are not all zero,
    // or the lower elements below the diagonal are not all zero, then
    // the matrix can never be special.
    if(_data[1][0] != 0.0f || _data[2][0] != 0.0f || _data[2][1] != 0.0f){
        _flags = Any;
        return;
    }
    if(_data[0][1] != 0.0f || _data[0][2] != 0.0f || _data[0][3] != 0.0f ||
        _data[1][2] != 0.0f || _data[1][3] != 0.0f || _data[2][3] != 0.0f){
        _flags = Any;
        return;
    }
    // Determine what we have in the remaining regions of the matrix.
    bool identityAlongDiagonal = (_data[0][0] == 1.0f && _data[1][1] == 1.0f && _data[2][2] == 1.0f);
    bool translationPresent = (_data[3][0] != 0.0f || _data[3][1] != 0.0f || _data[3][2] != 0.0f);
    // Now determine the special matrix type.
    if(translationPresent && identityAlongDiagonal)
        _flags = Translation;
    else if (translationPresent)
        _flags = (Translation | Scale);
    else if (identityAlongDiagonal)
        _flags = Identity;
    else
        _flags = Scale;
}

void matrix4x4::set_to_identity(){
    memset(_data, 0, 16*sizeof(float));
    _data[0][0] = _data[1][1] = _data[2][2] = _data[3][3] = 1.0f;
    _flags = Identity;
}

bool matrix4x4::identity() const{
    if(_flags == Identity)
        return true;
    bool i = _data[0][0] == 1.0f && _data[1][0] == 0.0f && _data[2][0] == 0.0f && _data[3][0] == 0.0f
            && _data[0][1] == 1.0f && _data[1][1] == 1.0f && _data[2][1] == 0.0f && _data[3][1] == 0.0f
            && _data[0][2] == 1.0f && _data[1][2] == 0.0f && _data[2][2] == 1.0f && _data[3][2] == 0.0f
            && _data[0][3] == 1.0f && _data[1][3] == 0.0f && _data[2][3] == 0.0f && _data[3][3] == 1.0f;
    if(i)
        _flags = Identity;
    return i;
}

// The 4x4 matrix inverse algorithm is based on that described at:
// http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q24
// Some optimization has been done by Qt to avoid making copies of 3x3
// sub-matrices and to unroll the loops.
// Calculate the determinant of a 3x3 sub-matrix.
//     | A B C |
// M = | D E F |    det(M) = A * (EI - HF) - B * (DI - GF) + C * (DH - GE)
//     | G H I |

static inline float matrixDet3(const float _data[4][4], int col0, int col1, int col2, int row0, int row1, int row2){
    return _data[col0][row0] * (_data[col1][row1] * _data[col2][row2] - _data[col1][row2] * _data[col2][row1])
        - _data[col1][row0] * (_data[col0][row1] * _data[col2][row2] - _data[col0][row2] * _data[col2][row1])
        + _data[col2][row0] * (_data[col0][row1] * _data[col1][row2] - _data[col0][row2] * _data[col1][row1]);
}

static inline float matrixDet4(const float _data[4][4]){
    float det;
    det = _data[0][0] * matrixDet3(_data, 1, 2, 3, 1, 2, 3);
    det -= _data[1][0] * matrixDet3(_data, 0, 2, 3, 1, 2, 3);
    det += _data[2][0] * matrixDet3(_data, 0, 1, 3, 1, 2, 3);
    det -= _data[3][0] * matrixDet3(_data, 0, 1, 2, 1, 2, 3);
    return det;
}

float matrix4x4::determinant() const{
    return float(matrixDet4(_data));
}

void matrix4x4::invert(bool *invertible){
    // Handle some of the easy cases first.
    if(_flags == Identity){
        if(invertible)
            *invertible = true;
        return;
    }else if(_flags == Translation){
        _data[3][0] = -_data[3][0];
        _data[3][1] = -_data[3][1];
        _data[3][2] = -_data[3][2];
        if(invertible)
            *invertible = true;
        return;
    }else if(_flags == Rotation || _flags == (Rotation | Translation)){
        if (invertible)
            *invertible = true;
        // Orthonormal inverse
        float inv[4][4];
        memset(inv, 0, 16*sizeof(float));
        inv[0][0] = _data[0][0];
        inv[1][0] = _data[0][1];
        inv[2][0] = _data[0][2];
        inv[0][1] = _data[1][0];
        inv[1][1] = _data[1][1];
        inv[2][1] = _data[1][2];
        inv[0][2] = _data[2][0];
        inv[1][2] = _data[2][1];
        inv[2][2] = _data[2][2];
        inv[0][3] = 0.0f;
        inv[1][3] = 0.0f;
        inv[2][3] = 0.0f;
        inv[3][0] = -(inv[0][0] * _data[3][0] + inv[1][0] * _data[3][1] + inv[2][0] * _data[3][2]);
        inv[3][1] = -(inv[0][1] * _data[3][0] + inv[1][1] * _data[3][1] + inv[2][1] * _data[3][2]);
        inv[3][2] = -(inv[0][2] * _data[3][0] + inv[1][2] * _data[3][1] + inv[2][2] * _data[3][2]);
        inv[3][3] = 1.0f;
        memcpy(_data, inv, 16*sizeof(float));
        return;
    }
    float det = determinant();
    if(det == 0.0f){
        if(invertible)
            *invertible = false;
        return;
    }
    float inv[4][4];
    memset(inv, 0, 16*sizeof(float));
    det = 1.0f/det;
    inv[0][0] = matrixDet3(_data, 1, 2, 3, 1, 2, 3) * det;
    inv[0][1] = -matrixDet3(_data, 0, 2, 3, 1, 2, 3) * det;
    inv[0][2] = matrixDet3(_data, 0, 1, 3, 1, 2, 3) * det;
    inv[0][3] = -matrixDet3(_data, 0, 1, 2, 1, 2, 3) * det;
    inv[1][0] = -matrixDet3(_data, 1, 2, 3, 0, 2, 3) * det;
    inv[1][1] = matrixDet3(_data, 0, 2, 3, 0, 2, 3) * det;
    inv[1][2] = -matrixDet3(_data, 0, 1, 3, 0, 2, 3) * det;
    inv[1][3] = matrixDet3(_data, 0, 1, 2, 0, 2, 3) * det;
    inv[2][0] = matrixDet3(_data, 1, 2, 3, 0, 1, 3) * det;
    inv[2][1] = -matrixDet3(_data, 0, 2, 3, 0, 1, 3) * det;
    inv[2][2] = matrixDet3(_data, 0, 1, 3, 0, 1, 3) * det;
    inv[2][3] = -matrixDet3(_data, 0, 1, 2, 0, 1, 3) * det;
    inv[3][0] = -matrixDet3(_data, 1, 2, 3, 0, 1, 2) * det;
    inv[3][1] = matrixDet3(_data, 0, 2, 3, 0, 1, 2) * det;
    inv[3][2] = -matrixDet3(_data, 0, 1, 3, 0, 1, 2) * det;
    inv[3][3] = matrixDet3(_data, 0, 1, 2, 0, 1, 2) * det;
    if(invertible)
        *invertible = true;
    memcpy(_data, inv, 16*sizeof(float));
}

void matrix4x4::transpose(){
    float tmp;
    for(int row = 0; row < 4; ++row){
        for (int col = 0; col < 4; ++col){
            tmp = _data[row][col];
            _data[row][col] = _data[col][row];
            _data[col][row] = tmp;
        }
    }
}

void matrix4x4::translate(const vector3d & v){
    translate(v.x(), v.y(), v.z());
}

void matrix4x4::translate(float x, float y, float z){
    if(_flags == Identity){
        _data[3][0] = x;
        _data[3][1] = y;
        _data[3][2] = z;
        _flags = Translation;
    }else if (_flags == Translation){
        _data[3][0] += x;
        _data[3][1] += y;
        _data[3][2] += z;
    }else if(_flags == Scale){
        _data[3][0] = _data[0][0] * x;
        _data[3][1] = _data[1][1] * y;
        _data[3][2] = _data[2][2] * z;
        _flags |= Translation;
    }else if(_flags == (Scale | Translation)){
        _data[3][0] += _data[0][0] * x;
        _data[3][1] += _data[1][1] * y;
        _data[3][2] += _data[2][2] * z;
    }else{
        _data[3][0] += _data[0][0] * x + _data[1][0] * y + _data[2][0] * z;
        _data[3][1] += _data[0][1] * x + _data[1][1] * y + _data[2][1] * z;
        _data[3][2] += _data[0][2] * x + _data[1][2] * y + _data[2][2] * z;
        _data[3][3] += _data[0][3] * x + _data[1][3] * y + _data[2][3] * z;
        if(_flags == Rotation)
            _flags |= Translation;
        else if(_flags != (Rotation | Translation))
            _flags = Any; //General
    }
}

void matrix4x4::scale(const vector3d & v){
    scale(v.x(), v.y(), v.z());
}

void matrix4x4::scale(float factor){
    scale(factor, factor, factor);
}

void matrix4x4::scale(float x, float y, float z){
    if (_flags == Identity){
        _data[0][0] = x;
        _data[1][1] = y;
        _data[2][2] = z;
        _flags = Scale;
    }else if(_flags == Scale || _flags == (Scale | Translation)){
        _data[0][0] *= x;
        _data[1][1] *= y;
        _data[2][2] *= z;
    }else if(_flags == Translation){
        _data[0][0] = x;
        _data[1][1] = y;
        _data[2][2] = z;
        _flags |= Scale;
    }else{
        _data[0][0] *= x;
        _data[0][1] *= x;
        _data[0][2] *= x;
        _data[0][3] *= x;
        _data[1][0] *= y;
        _data[1][1] *= y;
        _data[1][2] *= y;
        _data[1][3] *= y;
        _data[2][0] *= z;
        _data[2][1] *= z;
        _data[2][2] *= z;
        _data[2][3] *= z;
        _flags = Any; // General
    }
}

void matrix4x4::rotate(float angle, const vector3d & v){
    rotate(angle, v.x(), v.y(), v.z());
}

void matrix4x4::rotate(float angle, float x, float y, float z){
    if(angle == 0.0f)
        return;
    matrix4x4 m((float*)(void*)1); // The "1" says to not load the identity.
    real c, s, ic;
    if(angle == 90.0f || angle == -270.0f) {
        s = 1.0f;
        c = 0.0f;
    }else if (angle == -90.0f || angle == 270.0f){
        s = -1.0f;
        c = 0.0f;
    }else if (angle == 180.0f || angle == -180.0f){
        s = 0.0f;
        c = -1.0f;
    }else{
        real a = angle * PI/180.0f;
        c = cos(a);
        s = sin(a);
    }
    bool quick = false;
    if(x == 0.0f){
        if(y == 0.0f){
            if(z != 0.0f){
                // Rotate around the Z axis.
                m.set_to_identity();
                m._data[0][0] = c;
                m._data[1][1] = c;
                if(z < 0.0f){
                    m._data[1][0] = s;
                    m._data[0][1] = -s;
                }else{
                    m._data[1][0] = -s;
                    m._data[0][1] = s;
                }
                m._flags = Any; // General
                quick = true;
            }
        }else if(z == 0.0f){
            // Rotate around the Y axis.
            m.set_to_identity();
            m._data[0][0] = c;
            m._data[2][2] = c;
            if (y < 0.0f){
                m._data[2][0] = -s;
                m._data[0][2] = s;
            }else{
                m._data[2][0] = s;
                m._data[0][2] = -s;
            }
            m._flags = Any; // General
            quick = true;
        }
    }else if(y == 0.0f && z == 0.0f){
        // Rotate around the X axis.
        m.set_to_identity();
        m._data[1][1] = c;
        m._data[2][2] = c;
        if(x < 0.0f){
            m._data[2][1] = s;
            m._data[1][2] = -s;
        }else{
            m._data[2][1] = -s;
            m._data[1][2] = s;
        }
        m._flags = Any; // General
        quick = true;
    }
    if(!quick){
        real len = x * x + y * y + z * z;
        if(!fuzzy_is_null(len - 1.0f) && !fuzzy_is_null(len)){
            len = sqrt(len);
            x /= len;
            y /= len;
            z /= len;
        }
        ic = 1.0f - c;
        m._data[0][0] = x * x * ic + c;
        m._data[1][0] = x * y * ic - z * s;
        m._data[2][0] = x * z * ic + y * s;
        m._data[3][0] = 0.0f;
        m._data[0][1] = y * x * ic + z * s;
        m._data[1][1] = y * y * ic + c;
        m._data[2][1] = y * z * ic - x * s;
        m._data[3][1] = 0.0f;
        m._data[0][2] = x * z * ic - y * s;
        m._data[1][2] = y * z * ic + x * s;
        m._data[2][2] = z * z * ic + c;
        m._data[3][2] = 0.0f;
        m._data[0][3] = 0.0f;
        m._data[1][3] = 0.0f;
        m._data[2][3] = 0.0f;
        m._data[3][3] = 1.0f;
    }
    int flags = _flags;
    *this *= m;
    if(flags != Identity)
        _flags = flags | Rotation;
    else
        _flags = Rotation;
}

matrix4x4 matrix4x4::inverted(bool *invertible) const{
    matrix4x4 m(*this);
    bool iv = false;
    m.invert(&iv);
    if(!iv)
        m.set_to_identity();
    if(invertible)
        *invertible = iv;
    return m;
}

matrix4x4 matrix4x4::transposed() const{
    matrix4x4 m(*this);
    m.transpose();
    return m;
}

matrix4x4 matrix4x4::translated(const vector3d & v) const{
    matrix4x4 m(*this);
    m.translate(v);
    return m;
}

matrix4x4 matrix4x4::translated(float x, float y, float z) const{
    matrix4x4 m(*this);
    m.translate(x, y, z);
    return m;
}

matrix4x4 matrix4x4::scaled(const vector3d & v) const{
    matrix4x4 m(*this);
    m.scale(v);
    return m;
}

matrix4x4 matrix4x4::scaled(float x, float y, float z) const{
    matrix4x4 m(*this);
    m.scale(x, y, z);
    return m;
}

matrix4x4 matrix4x4::scaled(float factor) const{
    matrix4x4 m(*this);
    m.scale(factor);
    return m;
}

matrix4x4 matrix4x4::rotated(float angle, const vector3d & v) const{
    matrix4x4 m(*this);
    m.rotate(angle, v);
    return m;
}

matrix4x4 matrix4x4::rotated(float angle, float x, float y, float z) const{
    matrix4x4 m(*this);
    m.rotate(angle, x, y, z);
    return m;
}

void matrix4x4::look_at(const vector3d &eye, const vector3d & center, const vector3d &up){
    vector3d forward = (center - eye).normalized();
    vector3d side = vector3d::crossProduct(forward, up).normalized();
    vector3d upVector = vector3d::crossProduct(side, forward);
    matrix4x4 m((float*)(void*)1);
    /*m._data[0][0] = side.x();
    m._data[0][1] = side.y();
    m._data[0][2] = side.z();
    m._data[0][3] = 0.0f;
    m._data[1][0] = upVector.x();
    m._data[1][1] = upVector.y();
    m._data[1][2] = upVector.z();
    m._data[1][3] = 0.0f;
    m._data[2][0] = -forward.x();
    m._data[2][1] = -forward.y();
    m._data[2][2] = -forward.z();
    m._data[2][3] = 0.0f;
    m._data[3][0] = 0.0f;
    m._data[3][1] = 0.0f;
    m._data[3][2] = 0.0f;
    m._data[3][3] = 1.0f;*/
    m._data[0][0] = side.x();
    m._data[1][0] = side.y();
    m._data[2][0] = side.z();
    m._data[3][0] = 0.0f;
    m._data[0][1] = upVector.x();
    m._data[1][1] = upVector.y();
    m._data[2][1] = upVector.z();
    m._data[3][1] = 0.0f;
    m._data[0][2] = -forward.x();
    m._data[1][2] = -forward.y();
    m._data[2][2] = -forward.z();
    m._data[3][2] = 0.0f;
    m._data[0][3] = 0.0f;
    m._data[1][3] = 0.0f;
    m._data[2][3] = 0.0f;
    m._data[3][3] = 1.0f;
    *this *= m;
    translate(-eye);
}

vector3d matrix4x4::position() const{
    return vector3d(_data[3][0], _data[3][1], _data[3][2]);
}

vector3d matrix4x4::rotation() const{
    return vector3d(atan2(_data[2][3], _data[3][3])*57.2957795,
            atan2(-_data[1][3], hypot(-_data[1][3], -_data[3][3]))*57.2957795,
            atan2(_data[1][2], _data[1][1])*57.2957795);
}

vector3d matrix4x4::scale() const{
    // facteur d'ortho de la sous-matrice de rotation
    // plus tard...
    return vector3d();
}

float matrix4x4::at(int row, int column) const{
    return _data[column][row];
}

const float & matrix4x4::operator ()(int row, int column) const{
    return _data[column][row];
}

float & matrix4x4::operator ()(int row, int column){
    return _data[column][row];
}

vector3d matrix4x4::map(const vector3d & v) const{
    return *this * v;
}

const float *matrix4x4::data() const{
    return (float*)_data;
}

}

std::ostream & operator<<(std::ostream & stream, const hsm::matrix4x4 & m){
    stream << "|" << m(0, 0) << ", " << m(0, 1) << ", " << m(0, 2) << ", " << m(0, 3) << "|" << std::endl;
    stream << "|" << m(1, 0) << ", " << m(1, 1) << ", " << m(1, 2) << ", " << m(1, 3) << "|" << std::endl;
    stream << "|" << m(2, 0) << ", " << m(2, 1) << ", " << m(2, 2) << ", " << m(2, 3) << "|" << std::endl;
    stream << "|" << m(3, 0) << ", " << m(3, 1) << ", " << m(3, 2) << ", " << m(3, 3) << "|" << std::endl;
    return stream;
}
