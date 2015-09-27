#ifndef SWAPI_POINT_H
#define SWAPI_POINT_H

namespace hsm{

class point{
public:
    point();
    point(int x, int y);

    int x() const;
    int y() const;
    void set_x(int x);
    void set_y(int y);
    void set(int x, int y);

    point operator+(const point & point) const;
    point operator-(const point & point) const;
    point operator-() const;
    point operator+() const;
    const point & operator+=(const point & point);
    const point & operator-=(const point & point);
    bool operator==(const point & point) const;
    bool operator!=(const point & point) const;

private:
    int _x;
    int _y;
};

}

#endif // POINT_H
