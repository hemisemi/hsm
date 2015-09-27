#ifndef SWAPI_SIZE_H
#define SWAPI_SIZE_H

namespace hsm{

class size{
public:
    size(int width = 0, int height = 0);

    int width() const;
    int height() const;
    void set_width(int width);
    void set_height(int height);
    void set(int width, int height);

    int surface() const;

private:
    int _w;
    int _h;
};

}

#endif // SWAPI_SIZE_H
