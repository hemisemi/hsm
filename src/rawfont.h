#ifndef RAWFONT_H
#define RAWFONT_H

#include "font.h"
#include "fontmetrics.h"

namespace hsm{

class rawfont{
public:
    virtual ~rawfont() = 0;
    virtual bool matchStyle(font::Style) const = 0;

    virtual glyphmetrics metrics(int pixel_size, uint32 charcode) const = 0;
    virtual int height(int pixel_size) const = 0;
    virtual int ascender(int pixel_size) const = 0;
    virtual std::string family() const;
};

}

#endif // RAWFONT_H
