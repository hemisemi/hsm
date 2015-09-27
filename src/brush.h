#ifndef BRUSH_H
#define BRUSH_H

#include "color.h"

namespace hsm{

class brush{
public:
    brush();
    brush(const hsm::color & color);

    const hsm::color & color() const;
    void setColot(const hsm::color & color);

    bool isNull() const;

private:
    hsm::color _color;
    bool _null;
};

}

#endif // BRUSH_H
