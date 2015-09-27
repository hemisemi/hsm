#ifndef FONTMETRICS_H
#define FONTMETRICS_H

#include "font.h"
#include "rectf.h"
#include "types.h"

namespace hsm{

struct glyphmetrics{
    float width;
    float height;
    float bearing_x;
    float bearing_y;
    float advance;
};

class fontmetrics{
public:
    fontmetrics();
    fontmetrics(const font & font);

    float width(uint32 charcode) const;
    float advance(uint32 charcode) const;
    float height() const;

    glyphmetrics glyphMetrics(uint32 charcode) const;

    float ascender() const;

    rectf box(const std::string & str, float width = 0.0f) const;

private:
    font _font;
};

}

#endif // FONTMETRICS_H
