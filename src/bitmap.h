#pragma once

#include "paintdevice.h"
#include "types.h"
#include "graphiccontext.h"
#include "rect.h"
#include "color.h"

#include <map>

namespace hsm{

class bitmap : public paintdevice{
    friend class bitmap_paintengine;
public:
    enum class pixel_format{
        invalid,
        rgb,
        rgba,
        gray,
        gray_alpha
    };

    enum class transformation{
        fast,
        smooth
    };

    bitmap();
    bitmap(const bitmap & bitmap);
    bitmap(unsigned char *data, int width, int height, pixel_format format);
    bitmap(const std::string & filename);
    bitmap(int width, int height, pixel_format format = pixel_format::rgba);
    ~bitmap();

    bitmap & operator=(const bitmap & bmp);

    pixel_format format() const;
    void setFormat(pixel_format);
    void hueChange(int hue);

    bitmap scaled(int width, int height, bitmap::transformation t = transformation::fast) const;

    hsm::bitmap copy(const hsm::rect & rect = hsm::rect()) const;
    hsm::bitmap copy(int x, int y, int width, int height) const;

    int width() const;
    int height() const;
    hsm::rect rect() const;

    void clear();
    hsm::paintengine *paint_engine() const;

    color pixel(int x, int y) const;
    void setPixel(int x, int y, const color & color);

    void bind() const;
    void release() const;
    void dispose();

    const uint8 *data() const;

private:
    bitmap(uint8 *data, int width, int height, pixel_format, int internal_format);

    void refresh();

    pixel_format _format;
    char _internal_format;

    int _width;
    int _height;

    uint8 *_data;
    mutable std::map<GraphicContext *, uint> _map;
};

}
