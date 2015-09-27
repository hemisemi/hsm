#ifndef SWAPI_PEN_H
#define SWAPI_PEN_H

#include "color.h"

namespace hsm{

class pen{
public:
    pen();
    pen(const hsm::color & c);

    const hsm::color & color() const;
    void setColor(const hsm::color & c);

    bool isNull() const;

private:
    bool _null;
    hsm::color _color;
};

}

#endif // SWAPI_PEN_H
