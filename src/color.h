#ifndef SWAPI_COLOR_H
#define SWAPI_COLOR_H

#include "enum.h"

namespace hsm{

class color{
public:
    color();
    color(int r, int g, int b, int a = 255);
    color(const DefaultColor &);

    void set(int r, int g, int b, int a = 255);

    int red() const;
    int green() const;
    int blue() const;
    int alpha() const;
    void set_red(int);
    void set_green(int);
    void set_blue(int);
    void set_alpha(int);

    float redf() const;
    float greenf() const;
    float bluef() const;
    float alphaf() const;

    bool transparent() const;

    struct HSV{
        HSV(int hue, unsigned char sat, unsigned char value, unsigned char alpha);
        int hue = 0;
        unsigned char saturation = 0;
        unsigned char value = 0;
        unsigned char alpha;
    };

    HSV toHSV() const;
    static color fromHSV(HSV);

    bool operator==(const color &) const;
    bool operator!=(const color &) const;

private:
    unsigned char _r;
    unsigned char _g;
    unsigned char _b;
    unsigned char _a;
};

}

#endif // SWAPI_COLOR_H
