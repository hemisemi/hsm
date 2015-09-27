#ifndef VECTOR_H
#define VECTOR_H

#include <ostream>

namespace hsm{

class vector3d{
public:
    vector3d();
    vector3d(const vector3d &);
    vector3d(float x, float y, float z);
    vector3d(float *data);

    float distance(const vector3d &) const;

    bool isNull() const;
    float length() const;

    float x() const;
    float y() const;
    float z() const;
    void setX(float);
    void setY(float);
    void setZ(float);
    void set(float x, float y, float z);

    void normalize();
    vector3d normalized() const;

    void operator+=(const vector3d &);
    void operator-=(const vector3d &);
    void operator*=(float factor);
    void operator/=(float factor);
    vector3d operator+(const vector3d &) const;
    vector3d operator-(const vector3d &) const;
    vector3d operator*(float factor) const;
    vector3d operator/(float factor) const;
    vector3d operator-() const;

    static vector3d crossProduct(const vector3d & a, const vector3d & b);
    static float dotProduct(const vector3d & a, const vector3d & b);

    const float *data() const;

private:
    float _data[3];
};

}

std::ostream & operator<<(std::ostream &, const hsm::vector3d & v);

#endif // VECTOR_H
