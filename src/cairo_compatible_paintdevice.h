#ifndef CAIRO_COMPATIBLE_PAINTDEVICE_H
#define CAIRO_COMPATIBLE_PAINTDEVICE_H

#include "paintdevice.h"
#include <cairo/cairo.h>

namespace hsm{

class cairo_compatible_paintdevice : public virtual paintdevice{
public:
    virtual cairo_surface_t *cairo_surface() const = 0;
};

}

#endif // CAIRO_COMPATIBLE_PAINTDEVICE_H
