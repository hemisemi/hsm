#ifndef MATRIX_H
#define MATRIX_H

#include "pointf.h"
#include "types.h"
#include "algorithm.h"
#include <ostream>

namespace hsm{

class matrix3x3{
public:
    enum Format{
        RowMajorFormat,
        ColumnMajorFormat
    };

    matrix3x3();
    matrix3x3(const matrix3x3 &);
    matrix3x3(float *data, Format format = RowMajorFormat); // row-major
    matrix3x3(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33);

    void set(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33);
    void optimize();

    int type() const;
    bool invertible() const;
    bool scaling() const;
    bool rotating() const;
    bool translating() const;
    bool affine() const;

    void set_to_identity();
    bool identity() const;

    float determinant() const;

    void invert(bool *invertible = 0);
    void transpose();
    void translate(const pointf &);
    void translate(float x, float y, float z);
    void scale(const pointf &);
    void scale(float x, float y, float z);
    void scale(float factor);
    void rotate(float angle, const pointf &);
    void rotate(float angle, float x, float y, float z = 0.0f);

    matrix3x3 inverted(bool *invertible = 0) const;
    matrix3x3 transposed() const;
    matrix3x3 translated(const pointf &) const;
    matrix3x3 translated(float x, float y, float z) const;
    matrix3x3 scaled(const pointf &) const;
    matrix3x3 scaled(float x, float y, float z) const;
    matrix3x3 scaled(float factor) const;
    matrix3x3 rotated(float angle, const pointf &) const;
    matrix3x3 rotated(float angle, float x, float y, float z) const;

    void lookAt(const pointf & eye, const pointf & center, const pointf & up);
    pointf position() const;
    pointf rotation() const;
    pointf scale() const; // TODO

    float at(int row, int column) const;
    pointf map(const pointf &) const;

    const float & operator()(int row, int column) const;
    float & operator()(int row, int column);

    inline matrix3x3& operator +=(const matrix3x3 &);
    inline matrix3x3& operator -=(const matrix3x3 &);
    inline matrix3x3& operator *=(const matrix3x3 &);
    inline matrix3x3& operator *=(float);
    inline bool operator ==(const matrix3x3 &) const;
    inline bool operator !=(const matrix3x3 &) const;

    friend matrix3x3 operator+(const matrix3x3& m1, const matrix3x3& m2);
    friend matrix3x3 operator-(const matrix3x3& m1, const matrix3x3& m2);
    friend matrix3x3 operator*(const matrix3x3& m1, const matrix3x3& m2);
    friend pointf operator*(const matrix3x3& m, const pointf& v);
    friend pointf operator*(const pointf& v, const matrix3x3& m);
    friend matrix3x3 operator-(const matrix3x3& m);
    friend matrix3x3 operator*(float, const matrix3x3& m);
    friend matrix3x3 operator*(const matrix3x3& m, float);

    const float *data() const; // column-major

private:
    enum MatrixFlags{
        Any = 0,
        Identity = 1,
        Translation = 2,
        Rotation = 4,
        Scale = 8,
        Projection = 16
    };

    float _data[4][4]; // column-major
    mutable int _flags;
};

inline matrix3x3& matrix3x3::operator+=(const matrix3x3& other)
{
    _data[0][0] += other._data[0][0];
    _data[0][1] += other._data[0][1];
    _data[0][2] += other._data[0][2];
    _data[1][0] += other._data[1][0];
    _data[1][1] += other._data[1][1];
    _data[1][2] += other._data[1][2];
    _data[2][0] += other._data[2][0];
    _data[2][1] += other._data[2][1];
    _data[2][2] += other._data[2][2];
    _flags = Any;
    return *this;
}

inline matrix3x3& matrix3x3::operator-=(const matrix3x3& other)
{
    _data[0][0] -= other._data[0][0];
    _data[0][1] -= other._data[0][1];
    _data[0][2] -= other._data[0][2];
    _data[1][0] -= other._data[1][0];
    _data[1][1] -= other._data[1][1];
    _data[1][2] -= other._data[1][2];
    _data[2][0] -= other._data[2][0];
    _data[2][1] -= other._data[2][1];
    _data[2][2] -= other._data[2][2];
    _flags = Any;
    return *this;
}

inline matrix3x3& matrix3x3::operator*=(const matrix3x3& other)
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

inline matrix3x3& matrix3x3::operator*=(float factor)
{
    _data[0][0] *= factor;
    _data[0][1] *= factor;
    _data[0][2] *= factor;
    _data[1][0] *= factor;
    _data[1][1] *= factor;
    _data[1][2] *= factor;
    _data[2][0] *= factor;
    _data[2][1] *= factor;
    _data[2][2] *= factor;
    _flags = Any;
    return *this;
}

inline bool matrix3x3::operator==(const matrix3x3& other) const
{
    return _data[0][0] == other._data[0][0] &&
           _data[0][1] == other._data[0][1] &&
           _data[0][2] == other._data[0][2] &&
           _data[1][0] == other._data[1][0] &&
           _data[1][1] == other._data[1][1] &&
           _data[1][2] == other._data[1][2] &&
           _data[2][0] == other._data[2][0] &&
           _data[2][1] == other._data[2][1] &&
           _data[2][2] == other._data[2][2];
}

inline bool matrix3x3::operator!=(const matrix3x3& other) const
{
    return _data[0][0] != other._data[0][0] ||
           _data[0][1] != other._data[0][1] ||
           _data[0][2] != other._data[0][2] ||
           _data[1][0] != other._data[1][0] ||
           _data[1][1] != other._data[1][1] ||
           _data[1][2] != other._data[1][2] ||
           _data[2][0] != other._data[2][0] ||
           _data[2][1] != other._data[2][1] ||
           _data[2][2] != other._data[2][2];
}

inline matrix3x3 operator+(const matrix3x3& m1, const matrix3x3& m2)
{
    matrix3x3 m((float*)(void*)1);
    m._data[0][0] = m1._data[0][0] + m2._data[0][0];
    m._data[0][1] = m1._data[0][1] + m2._data[0][1];
    m._data[0][2] = m1._data[0][2] + m2._data[0][2];
    m._data[1][0] = m1._data[1][0] + m2._data[1][0];
    m._data[1][1] = m1._data[1][1] + m2._data[1][1];
    m._data[1][2] = m1._data[1][2] + m2._data[1][2];
    m._data[2][0] = m1._data[2][0] + m2._data[2][0];
    m._data[2][1] = m1._data[2][1] + m2._data[2][1];
    m._data[2][2] = m1._data[2][2] + m2._data[2][2];
    return m;
}

inline matrix3x3 operator-(const matrix3x3& m1, const matrix3x3& m2)
{
    matrix3x3 m((float*)(void*)1);
    m._data[0][0] = m1._data[0][0] - m2._data[0][0];
    m._data[0][1] = m1._data[0][1] - m2._data[0][1];
    m._data[0][2] = m1._data[0][2] - m2._data[0][2];
    m._data[1][0] = m1._data[1][0] - m2._data[1][0];
    m._data[1][1] = m1._data[1][1] - m2._data[1][1];
    m._data[1][2] = m1._data[1][2] - m2._data[1][2];
    m._data[2][0] = m1._data[2][0] - m2._data[2][0];
    m._data[2][1] = m1._data[2][1] - m2._data[2][1];
    m._data[2][2] = m1._data[2][2] - m2._data[2][2];
    return m;
}

inline matrix3x3 operator*(const matrix3x3& m1, const matrix3x3& m2)
{
    if (m1._flags == matrix3x3::Identity)
        return m2;
    else if (m2._flags == matrix3x3::Identity)
        return m1;

    matrix3x3 m((float*)(void*)1);
    m._data[0][0] = m1._data[0][0] * m2._data[0][0] +
                m1._data[1][0] * m2._data[0][1] +
                m1._data[2][0] * m2._data[0][2];
    m._data[0][1] = m1._data[0][1] * m2._data[0][0] +
                m1._data[1][1] * m2._data[0][1] +
                m1._data[2][1] * m2._data[0][2];
    m._data[0][2] = m1._data[0][2] * m2._data[0][0] +
                m1._data[1][2] * m2._data[0][1] +
                m1._data[2][2] * m2._data[0][2];
    m._data[1][0] = m1._data[0][0] * m2._data[1][0] +
                m1._data[1][0] * m2._data[1][1] +
                m1._data[2][0] * m2._data[1][2];
    m._data[1][1] = m1._data[0][1] * m2._data[1][0] +
                m1._data[1][1] * m2._data[1][1] +
                m1._data[2][1] * m2._data[1][2];
    m._data[1][2] = m1._data[0][2] * m2._data[1][0] +
                m1._data[1][2] * m2._data[1][1] +
                m1._data[2][2] * m2._data[1][2];
    m._data[2][0] = m1._data[0][0] * m2._data[2][0] +
                m1._data[1][0] * m2._data[2][1] +
                m1._data[2][0] * m2._data[2][2];
    m._data[2][1] = m1._data[0][1] * m2._data[2][0] +
                m1._data[1][1] * m2._data[2][1] +
                m1._data[2][1] * m2._data[2][2];
    m._data[2][2] = m1._data[0][2] * m2._data[2][0] +
                m1._data[1][2] * m2._data[2][1] +
                m1._data[2][2] * m2._data[2][2];
    return m;
}

inline pointf operator*(const pointf& vector, const matrix3x3& matrix)
{
    float x, y, w;
    x = vector.x() * matrix._data[0][0] +
        vector.y() * matrix._data[0][1] +
        matrix._data[0][2];
    y = vector.x() * matrix._data[1][0] +
        vector.y() * matrix._data[1][1] +
        matrix._data[1][2];
    w = vector.x() * matrix._data[2][0] +
        vector.y() * matrix._data[2][1] +
        matrix._data[2][2];
    if (w == 1.0f)
        return pointf(x, y);
    else
        return pointf(x / w, y / w);
}

inline pointf operator*(const matrix3x3& matrix, const pointf& vector)
{
    float x, y, w;
    if (matrix._flags == matrix3x3::Identity) {
        return vector;
    } else if (matrix._flags == matrix3x3::Translation) {
        return pointf(vector.x() + matrix._data[2][0],
                         vector.y() + matrix._data[2][1]);
    } else if (matrix._flags ==
                    (matrix3x3::Translation | matrix3x3::Scale)) {
        return pointf(vector.x() * matrix._data[0][0] + matrix._data[2][0],
                         vector.y() * matrix._data[1][1] + matrix._data[2][1]);
    } else if (matrix._flags == matrix3x3::Scale) {
        return pointf(vector.x() * matrix._data[0][0],
                         vector.y() * matrix._data[1][1]);
    } else {
        x = vector.x() * matrix._data[0][0] +
            vector.y() * matrix._data[1][0] +
            matrix._data[2][0];
        y = vector.x() * matrix._data[0][1] +
            vector.y() * matrix._data[1][1] +
            matrix._data[2][1];
        w = vector.x() * matrix._data[0][2] +
            vector.y() * matrix._data[1][2] +
            matrix._data[2][2];
        if (w == 1.0f)
            return pointf(x, y);
        else
            return pointf(x / w, y / w);
    }
}

inline matrix3x3 operator-(const matrix3x3& matrix)
{
    matrix3x3 m((float*)(void*)1);
    m._data[0][0] = -matrix._data[0][0];
    m._data[0][1] = -matrix._data[0][1];
    m._data[0][2] = -matrix._data[0][2];
    m._data[1][0] = -matrix._data[1][0];
    m._data[1][1] = -matrix._data[1][1];
    m._data[1][2] = -matrix._data[1][2];
    m._data[2][0] = -matrix._data[2][0];
    m._data[2][1] = -matrix._data[2][1];
    m._data[2][2] = -matrix._data[2][2];
    return m;
}

inline matrix3x3 operator*(float factor, const matrix3x3& matrix)
{
    matrix3x3 m((float*)(void*)1);
    m._data[0][0] = matrix._data[0][0] * factor;
    m._data[0][1] = matrix._data[0][1] * factor;
    m._data[0][2] = matrix._data[0][2] * factor;
    m._data[1][0] = matrix._data[1][0] * factor;
    m._data[1][1] = matrix._data[1][1] * factor;
    m._data[1][2] = matrix._data[1][2] * factor;
    m._data[2][0] = matrix._data[2][0] * factor;
    m._data[2][1] = matrix._data[2][1] * factor;
    m._data[2][2] = matrix._data[2][2] * factor;
    return m;
}

inline matrix3x3 operator*(const matrix3x3& matrix, float factor)
{
    matrix3x3 m((float*)(void*)1);
    m._data[0][0] = matrix._data[0][0] * factor;
    m._data[0][1] = matrix._data[0][1] * factor;
    m._data[0][2] = matrix._data[0][2] * factor;
    m._data[1][0] = matrix._data[1][0] * factor;
    m._data[1][1] = matrix._data[1][1] * factor;
    m._data[1][2] = matrix._data[1][2] * factor;
    m._data[2][0] = matrix._data[2][0] * factor;
    m._data[2][1] = matrix._data[2][1] * factor;
    m._data[2][2] = matrix._data[2][2] * factor;
    return m;
}

}

std::ostream & operator<<(std::ostream & stream, const hsm::matrix3x3 & m);

#endif // MATRIX_H
