#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"
#include "types.h"
#include "algorithm.h"
#include <ostream>

namespace hsm{

class matrix4x4{
public:
    enum Format{
        RowMajorFormat,
        ColumnMajorFormat
    };

    matrix4x4();
    matrix4x4(const matrix4x4 &);
    matrix4x4(float *data, Format format = RowMajorFormat); // row-major
    matrix4x4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);

    void set(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);
    void optimize();

    void set_to_identity();
    bool identity() const;

    float determinant() const;

    void invert(bool *invertible = 0);
    void transpose();
    void translate(const vector3d &);
    void translate(float x, float y, float z);
    void scale(const vector3d &);
    void scale(float x, float y, float z);
    void scale(float factor);
    void rotate(float angle, const vector3d &);
    void rotate(float angle, float x, float y, float z = 0.0f);

    matrix4x4 inverted(bool *invertible = 0) const;
    matrix4x4 transposed() const;
    matrix4x4 translated(const vector3d &) const;
    matrix4x4 translated(float x, float y, float z) const;
    matrix4x4 scaled(const vector3d &) const;
    matrix4x4 scaled(float x, float y, float z) const;
    matrix4x4 scaled(float factor) const;
    matrix4x4 rotated(float angle, const vector3d &) const;
    matrix4x4 rotated(float angle, float x, float y, float z) const;

    void look_at(const vector3d & eye, const vector3d & center, const vector3d & up);
    vector3d position() const;
    vector3d rotation() const;
    vector3d scale() const; // TODO

    float at(int row, int column) const;
    vector3d map(const vector3d &) const;

    const float & operator()(int row, int column) const;
    float & operator()(int row, int column);

    inline matrix4x4& operator +=(const matrix4x4 &);
    inline matrix4x4& operator -=(const matrix4x4 &);
    inline matrix4x4& operator *=(const matrix4x4 &);
    inline matrix4x4& operator *=(float);
    inline bool operator ==(const matrix4x4 &) const;
    inline bool operator !=(const matrix4x4 &) const;

    friend matrix4x4 operator+(const matrix4x4& m1, const matrix4x4& m2);
    friend matrix4x4 operator-(const matrix4x4& m1, const matrix4x4& m2);
    friend matrix4x4 operator*(const matrix4x4& m1, const matrix4x4& m2);
    friend vector3d operator*(const matrix4x4& m, const vector3d& v);
    friend vector3d operator*(const vector3d& v, const matrix4x4& m);
    friend matrix4x4 operator-(const matrix4x4& m);
    friend matrix4x4 operator*(float, const matrix4x4& m);
    friend matrix4x4 operator*(const matrix4x4& m, float);

    const float *data() const; // column-major

private:
    enum MatrixFlags{
        Any = 0,
        Identity = 1,
        Translation = 2,
        Rotation = 4,
        Scale = 8,
        Perspective = 16,
        Ortho = 32
    };

    float _data[4][4]; // column-major
    mutable int _flags;
};

inline matrix4x4& matrix4x4::operator+=(const matrix4x4& other)
{
    _data[0][0] += other._data[0][0];
    _data[0][1] += other._data[0][1];
    _data[0][2] += other._data[0][2];
    _data[0][3] += other._data[0][3];
    _data[1][0] += other._data[1][0];
    _data[1][1] += other._data[1][1];
    _data[1][2] += other._data[1][2];
    _data[1][3] += other._data[1][3];
    _data[2][0] += other._data[2][0];
    _data[2][1] += other._data[2][1];
    _data[2][2] += other._data[2][2];
    _data[2][3] += other._data[2][3];
    _data[3][0] += other._data[3][0];
    _data[3][1] += other._data[3][1];
    _data[3][2] += other._data[3][2];
    _data[3][3] += other._data[3][3];
    _flags = Any;
    return *this;
}

inline matrix4x4& matrix4x4::operator-=(const matrix4x4& other)
{
    _data[0][0] -= other._data[0][0];
    _data[0][1] -= other._data[0][1];
    _data[0][2] -= other._data[0][2];
    _data[0][3] -= other._data[0][3];
    _data[1][0] -= other._data[1][0];
    _data[1][1] -= other._data[1][1];
    _data[1][2] -= other._data[1][2];
    _data[1][3] -= other._data[1][3];
    _data[2][0] -= other._data[2][0];
    _data[2][1] -= other._data[2][1];
    _data[2][2] -= other._data[2][2];
    _data[2][3] -= other._data[2][3];
    _data[3][0] -= other._data[3][0];
    _data[3][1] -= other._data[3][1];
    _data[3][2] -= other._data[3][2];
    _data[3][3] -= other._data[3][3];
    _flags = Any;
    return *this;
}

inline matrix4x4& matrix4x4::operator*=(const matrix4x4& other)
{
    if (_flags == Identity) {
        *this = other;
        return *this;
    } else if (other._flags == Identity) {
        return *this;
    } else {
        *this = *this * other;
        return *this;
    }
}

inline matrix4x4& matrix4x4::operator*=(float factor)
{
    _data[0][0] *= factor;
    _data[0][1] *= factor;
    _data[0][2] *= factor;
    _data[0][3] *= factor;
    _data[1][0] *= factor;
    _data[1][1] *= factor;
    _data[1][2] *= factor;
    _data[1][3] *= factor;
    _data[2][0] *= factor;
    _data[2][1] *= factor;
    _data[2][2] *= factor;
    _data[2][3] *= factor;
    _data[3][0] *= factor;
    _data[3][1] *= factor;
    _data[3][2] *= factor;
    _data[3][3] *= factor;
    _flags = Any;
    return *this;
}

inline bool matrix4x4::operator==(const matrix4x4& other) const
{
    return _data[0][0] == other._data[0][0] &&
           _data[0][1] == other._data[0][1] &&
           _data[0][2] == other._data[0][2] &&
           _data[0][3] == other._data[0][3] &&
           _data[1][0] == other._data[1][0] &&
           _data[1][1] == other._data[1][1] &&
           _data[1][2] == other._data[1][2] &&
           _data[1][3] == other._data[1][3] &&
           _data[2][0] == other._data[2][0] &&
           _data[2][1] == other._data[2][1] &&
           _data[2][2] == other._data[2][2] &&
           _data[2][3] == other._data[2][3] &&
           _data[3][0] == other._data[3][0] &&
           _data[3][1] == other._data[3][1] &&
           _data[3][2] == other._data[3][2] &&
           _data[3][3] == other._data[3][3];
}

inline bool matrix4x4::operator!=(const matrix4x4& other) const
{
    return _data[0][0] != other._data[0][0] ||
           _data[0][1] != other._data[0][1] ||
           _data[0][2] != other._data[0][2] ||
           _data[0][3] != other._data[0][3] ||
           _data[1][0] != other._data[1][0] ||
           _data[1][1] != other._data[1][1] ||
           _data[1][2] != other._data[1][2] ||
           _data[1][3] != other._data[1][3] ||
           _data[2][0] != other._data[2][0] ||
           _data[2][1] != other._data[2][1] ||
           _data[2][2] != other._data[2][2] ||
           _data[2][3] != other._data[2][3] ||
           _data[3][0] != other._data[3][0] ||
           _data[3][1] != other._data[3][1] ||
           _data[3][2] != other._data[3][2] ||
           _data[3][3] != other._data[3][3];
}

inline matrix4x4 operator+(const matrix4x4& m1, const matrix4x4& m2)
{
    matrix4x4 m((float*)(void*)1);
    m._data[0][0] = m1._data[0][0] + m2._data[0][0];
    m._data[0][1] = m1._data[0][1] + m2._data[0][1];
    m._data[0][2] = m1._data[0][2] + m2._data[0][2];
    m._data[0][3] = m1._data[0][3] + m2._data[0][3];
    m._data[1][0] = m1._data[1][0] + m2._data[1][0];
    m._data[1][1] = m1._data[1][1] + m2._data[1][1];
    m._data[1][2] = m1._data[1][2] + m2._data[1][2];
    m._data[1][3] = m1._data[1][3] + m2._data[1][3];
    m._data[2][0] = m1._data[2][0] + m2._data[2][0];
    m._data[2][1] = m1._data[2][1] + m2._data[2][1];
    m._data[2][2] = m1._data[2][2] + m2._data[2][2];
    m._data[2][3] = m1._data[2][3] + m2._data[2][3];
    m._data[3][0] = m1._data[3][0] + m2._data[3][0];
    m._data[3][1] = m1._data[3][1] + m2._data[3][1];
    m._data[3][2] = m1._data[3][2] + m2._data[3][2];
    m._data[3][3] = m1._data[3][3] + m2._data[3][3];
    return m;
}

inline matrix4x4 operator-(const matrix4x4& m1, const matrix4x4& m2)
{
    matrix4x4 m((float*)(void*)1);
    m._data[0][0] = m1._data[0][0] - m2._data[0][0];
    m._data[0][1] = m1._data[0][1] - m2._data[0][1];
    m._data[0][2] = m1._data[0][2] - m2._data[0][2];
    m._data[0][3] = m1._data[0][3] - m2._data[0][3];
    m._data[1][0] = m1._data[1][0] - m2._data[1][0];
    m._data[1][1] = m1._data[1][1] - m2._data[1][1];
    m._data[1][2] = m1._data[1][2] - m2._data[1][2];
    m._data[1][3] = m1._data[1][3] - m2._data[1][3];
    m._data[2][0] = m1._data[2][0] - m2._data[2][0];
    m._data[2][1] = m1._data[2][1] - m2._data[2][1];
    m._data[2][2] = m1._data[2][2] - m2._data[2][2];
    m._data[2][3] = m1._data[2][3] - m2._data[2][3];
    m._data[3][0] = m1._data[3][0] - m2._data[3][0];
    m._data[3][1] = m1._data[3][1] - m2._data[3][1];
    m._data[3][2] = m1._data[3][2] - m2._data[3][2];
    m._data[3][3] = m1._data[3][3] - m2._data[3][3];
    return m;
}

inline matrix4x4 operator*(const matrix4x4& m1, const matrix4x4& m2)
{
    if (m1._flags == matrix4x4::Identity)
        return m2;
    else if (m2._flags == matrix4x4::Identity)
        return m1;

    matrix4x4 m((float*)(void*)1);
    m._data[0][0] = m1._data[0][0] * m2._data[0][0] +
                m1._data[1][0] * m2._data[0][1] +
                m1._data[2][0] * m2._data[0][2] +
                m1._data[3][0] * m2._data[0][3];
    m._data[0][1] = m1._data[0][1] * m2._data[0][0] +
                m1._data[1][1] * m2._data[0][1] +
                m1._data[2][1] * m2._data[0][2] +
                m1._data[3][1] * m2._data[0][3];
    m._data[0][2] = m1._data[0][2] * m2._data[0][0] +
                m1._data[1][2] * m2._data[0][1] +
                m1._data[2][2] * m2._data[0][2] +
                m1._data[3][2] * m2._data[0][3];
    m._data[0][3] = m1._data[0][3] * m2._data[0][0] +
                m1._data[1][3] * m2._data[0][1] +
                m1._data[2][3] * m2._data[0][2] +
                m1._data[3][3] * m2._data[0][3];
    m._data[1][0] = m1._data[0][0] * m2._data[1][0] +
                m1._data[1][0] * m2._data[1][1] +
                m1._data[2][0] * m2._data[1][2] +
                m1._data[3][0] * m2._data[1][3];
    m._data[1][1] = m1._data[0][1] * m2._data[1][0] +
                m1._data[1][1] * m2._data[1][1] +
                m1._data[2][1] * m2._data[1][2] +
                m1._data[3][1] * m2._data[1][3];
    m._data[1][2] = m1._data[0][2] * m2._data[1][0] +
                m1._data[1][2] * m2._data[1][1] +
                m1._data[2][2] * m2._data[1][2] +
                m1._data[3][2] * m2._data[1][3];
    m._data[1][3] = m1._data[0][3] * m2._data[1][0] +
                m1._data[1][3] * m2._data[1][1] +
                m1._data[2][3] * m2._data[1][2] +
                m1._data[3][3] * m2._data[1][3];
    m._data[2][0] = m1._data[0][0] * m2._data[2][0] +
                m1._data[1][0] * m2._data[2][1] +
                m1._data[2][0] * m2._data[2][2] +
                m1._data[3][0] * m2._data[2][3];
    m._data[2][1] = m1._data[0][1] * m2._data[2][0] +
                m1._data[1][1] * m2._data[2][1] +
                m1._data[2][1] * m2._data[2][2] +
                m1._data[3][1] * m2._data[2][3];
    m._data[2][2] = m1._data[0][2] * m2._data[2][0] +
                m1._data[1][2] * m2._data[2][1] +
                m1._data[2][2] * m2._data[2][2] +
                m1._data[3][2] * m2._data[2][3];
    m._data[2][3] = m1._data[0][3] * m2._data[2][0] +
                m1._data[1][3] * m2._data[2][1] +
                m1._data[2][3] * m2._data[2][2] +
                m1._data[3][3] * m2._data[2][3];
    m._data[3][0] = m1._data[0][0] * m2._data[3][0] +
                m1._data[1][0] * m2._data[3][1] +
                m1._data[2][0] * m2._data[3][2] +
                m1._data[3][0] * m2._data[3][3];
    m._data[3][1] = m1._data[0][1] * m2._data[3][0] +
                m1._data[1][1] * m2._data[3][1] +
                m1._data[2][1] * m2._data[3][2] +
                m1._data[3][1] * m2._data[3][3];
    m._data[3][2] = m1._data[0][2] * m2._data[3][0] +
                m1._data[1][2] * m2._data[3][1] +
                m1._data[2][2] * m2._data[3][2] +
                m1._data[3][2] * m2._data[3][3];
    m._data[3][3] = m1._data[0][3] * m2._data[3][0] +
                m1._data[1][3] * m2._data[3][1] +
                m1._data[2][3] * m2._data[3][2] +
                m1._data[3][3] * m2._data[3][3];
    return m;
}

inline vector3d operator*(const vector3d& vector, const matrix4x4& matrix)
{
    float x, y, z, w;
    x = vector.x() * matrix._data[0][0] +
        vector.y() * matrix._data[0][1] +
        vector.z() * matrix._data[0][2] +
        matrix._data[0][3];
    y = vector.x() * matrix._data[1][0] +
        vector.y() * matrix._data[1][1] +
        vector.z() * matrix._data[1][2] +
        matrix._data[1][3];
    z = vector.x() * matrix._data[2][0] +
        vector.y() * matrix._data[2][1] +
        vector.z() * matrix._data[2][2] +
        matrix._data[2][3];
    w = vector.x() * matrix._data[3][0] +
        vector.y() * matrix._data[3][1] +
        vector.z() * matrix._data[3][2] +
        matrix._data[3][3];
    if (w == 1.0f)
        return vector3d(x, y, z);
    else
        return vector3d(x / w, y / w, z / w);
}

inline vector3d operator*(const matrix4x4& matrix, const vector3d& vector)
{
    float x, y, z, w;
    if (matrix._flags == matrix4x4::Identity) {
        return vector;
    } else if (matrix._flags == matrix4x4::Translation) {
        return vector3d(vector.x() + matrix._data[3][0],
                         vector.y() + matrix._data[3][1],
                         vector.z() + matrix._data[3][2]);
    } else if (matrix._flags ==
                    (matrix4x4::Translation | matrix4x4::Scale)) {
        return vector3d(vector.x() * matrix._data[0][0] + matrix._data[3][0],
                         vector.y() * matrix._data[1][1] + matrix._data[3][1],
                         vector.z() * matrix._data[2][2] + matrix._data[3][2]);
    } else if (matrix._flags == matrix4x4::Scale) {
        return vector3d(vector.x() * matrix._data[0][0],
                         vector.y() * matrix._data[1][1],
                         vector.z() * matrix._data[2][2]);
    } else {
        x = vector.x() * matrix._data[0][0] +
            vector.y() * matrix._data[1][0] +
            vector.z() * matrix._data[2][0] +
            matrix._data[3][0];
        y = vector.x() * matrix._data[0][1] +
            vector.y() * matrix._data[1][1] +
            vector.z() * matrix._data[2][1] +
            matrix._data[3][1];
        z = vector.x() * matrix._data[0][2] +
            vector.y() * matrix._data[1][2] +
            vector.z() * matrix._data[2][2] +
            matrix._data[3][2];
        w = vector.x() * matrix._data[0][3] +
            vector.y() * matrix._data[1][3] +
            vector.z() * matrix._data[2][3] +
            matrix._data[3][3];
        if (w == 1.0f)
            return vector3d(x, y, z);
        else
            return vector3d(x / w, y / w, z / w);
    }
}

inline matrix4x4 operator-(const matrix4x4& matrix)
{
    matrix4x4 m((float*)(void*)1);
    m._data[0][0] = -matrix._data[0][0];
    m._data[0][1] = -matrix._data[0][1];
    m._data[0][2] = -matrix._data[0][2];
    m._data[0][3] = -matrix._data[0][3];
    m._data[1][0] = -matrix._data[1][0];
    m._data[1][1] = -matrix._data[1][1];
    m._data[1][2] = -matrix._data[1][2];
    m._data[1][3] = -matrix._data[1][3];
    m._data[2][0] = -matrix._data[2][0];
    m._data[2][1] = -matrix._data[2][1];
    m._data[2][2] = -matrix._data[2][2];
    m._data[2][3] = -matrix._data[2][3];
    m._data[3][0] = -matrix._data[3][0];
    m._data[3][1] = -matrix._data[3][1];
    m._data[3][2] = -matrix._data[3][2];
    m._data[3][3] = -matrix._data[3][3];
    return m;
}

inline matrix4x4 operator*(float factor, const matrix4x4& matrix)
{
    matrix4x4 m((float*)(void*)1);
    m._data[0][0] = matrix._data[0][0] * factor;
    m._data[0][1] = matrix._data[0][1] * factor;
    m._data[0][2] = matrix._data[0][2] * factor;
    m._data[0][3] = matrix._data[0][3] * factor;
    m._data[1][0] = matrix._data[1][0] * factor;
    m._data[1][1] = matrix._data[1][1] * factor;
    m._data[1][2] = matrix._data[1][2] * factor;
    m._data[1][3] = matrix._data[1][3] * factor;
    m._data[2][0] = matrix._data[2][0] * factor;
    m._data[2][1] = matrix._data[2][1] * factor;
    m._data[2][2] = matrix._data[2][2] * factor;
    m._data[2][3] = matrix._data[2][3] * factor;
    m._data[3][0] = matrix._data[3][0] * factor;
    m._data[3][1] = matrix._data[3][1] * factor;
    m._data[3][2] = matrix._data[3][2] * factor;
    m._data[3][3] = matrix._data[3][3] * factor;
    return m;
}

inline matrix4x4 operator*(const matrix4x4& matrix, float factor)
{
    matrix4x4 m((float*)(void*)1);
    m._data[0][0] = matrix._data[0][0] * factor;
    m._data[0][1] = matrix._data[0][1] * factor;
    m._data[0][2] = matrix._data[0][2] * factor;
    m._data[0][3] = matrix._data[0][3] * factor;
    m._data[1][0] = matrix._data[1][0] * factor;
    m._data[1][1] = matrix._data[1][1] * factor;
    m._data[1][2] = matrix._data[1][2] * factor;
    m._data[1][3] = matrix._data[1][3] * factor;
    m._data[2][0] = matrix._data[2][0] * factor;
    m._data[2][1] = matrix._data[2][1] * factor;
    m._data[2][2] = matrix._data[2][2] * factor;
    m._data[2][3] = matrix._data[2][3] * factor;
    m._data[3][0] = matrix._data[3][0] * factor;
    m._data[3][1] = matrix._data[3][1] * factor;
    m._data[3][2] = matrix._data[3][2] * factor;
    m._data[3][3] = matrix._data[3][3] * factor;
    return m;
}

}

std::ostream & operator<<(std::ostream & stream, const hsm::matrix4x4 & m);

#endif // MATRIX_H
