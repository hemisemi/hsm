#ifndef SWAPI_SIZEF_H
#define SWAPI_SIZEF_H

namespace hsm{

class sizef{
public:
    sizef(float width = 0, float height = 0);

    float width() const;
    float height() const;
    void set_width(float width);
    void set_height(float height);
    void set(float width, float height);

    float surface() const;

private:
    float _w;
    float _h;
};

}

#endif // SWAPI_SIZEF_H
