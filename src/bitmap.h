#pragma once

//#include "paintdevice.h"
#include <hsm/types.h>
//#include "graphiccontext.h"
#include <hsm/rect.h>
#include <hsm/color.h>

#include <map>

namespace hsm{

class bitmap{
public:
    enum class pixel_format{
        invalid,
        rgb,
        argb,
        gray,
        gray_alpha
    };

    enum class transformation{
        fast,
        smooth
    };

    bitmap();
    bitmap(const bitmap & bitmap);
    bitmap(uint8_t *data, size_t width, size_t height, pixel_format format, bool copy = true);
    bitmap(uint8_t *data, size_t width, size_t height, pixel_format format, size_t stride, bool copy = true);
    bitmap(size_t width, size_t height, pixel_format format = pixel_format::argb);
    bitmap(size_t width, size_t height, pixel_format format, size_t stride);
    ~bitmap();

    bitmap & operator=(const bitmap & bmp);

    pixel_format format() const;
    void setFormat(pixel_format);

    bitmap scaled(int width, int height, bitmap::transformation t = transformation::fast) const;

    hsm::bitmap copy(const hsm::rect & rect = hsm::rect()) const;
    hsm::bitmap copy(int x, int y, int width, int height) const;

    size_t width() const;
    size_t height() const;
    size_t depth() const;
    size_t stride() const;
    static size_t depth(pixel_format format);
    hsm::rect rect() const;

    void clear();

    color pixel(int x, int y) const;
    void setPixel(int x, int y, const color & color);

    const uint8_t *data() const;
    size_t length() const;

    void refresh();

protected:
    pixel_format _format;

    size_t _width;
    size_t _height;
    size_t _depth;
    size_t _stride;

    uint8_t *_data;
};

}
