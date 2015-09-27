#ifndef SWAPI_POINTF_H
#define SWAPI_POINTF_H

namespace hsm{

class pointf{
public:
    pointf();
    pointf(float x, float y);

    float x() const;
    float y() const;
    void set_x(float x);
    void set_y(float y);
    void set(float x, float y);

    pointf operator+(const pointf & point) const;
    pointf operator-(const pointf & point) const;
    pointf operator-() const;
    pointf operator+() const;
    const pointf & operator+=(const pointf & point);
    const pointf & operator-=(const pointf & point);
    bool operator==(const pointf & point) const;
    bool operator!=(const pointf & point) const;

private:
    float _x;
    float _y;
};

}

#endif // POINTF_H
