#ifndef SWAPI_PAINTER_H
#define SWAPI_PAINTER_H

#include "font.h"
#include "pen.h"
#include "brush.h"
#include "rect.h"

namespace hsm{

class paintdevice;
class paintengine;
class point;
class bitmap;
class region;

class painter{
public:
    painter();
    painter(paintdevice *device);

    void draw_bitmap(int x, int y, const bitmap & bitmap, const rect & source = rect::null());
    void draw_bitmap(int x, int y, int width, int height, const bitmap & bitmap, const rect & source = rect::null());
    void draw_bitmap(const rect & target, const bitmap & bitmap, const rect & source = rect::null());
    void draw_point(const point & point);
    void draw_rect(const rect & rect);
    void draw_text(int x, int y, const std::string & str);
    void draw_text(int x, int y, int width, int height, const std::string & str, int flags = hsm::AlignHCenter | hsm::AlignVCenter);
    void draw_text(const rect & rect, const std::string & str, int flags = hsm::AlignHCenter | hsm::AlignVCenter);

    void set_font(const hsm::font & font);
    void set_pen(const hsm::pen & pen);
    void set_brush(const hsm::brush & brush);
    void set_opacity(float opa);

    void clip(const rect & region);

    const hsm::font & font() const;
    const hsm::brush & brush() const;
    const hsm::pen & pen() const;
    float opacity() const;

    void begin(paintdevice *device);
    void end();
    paintengine *engine() const;

private:
    paintdevice *_device;
    paintengine *_engine;
    hsm::font _font;
    hsm::pen _pen;
    hsm::brush _brush;
    float _opacity;
};

}

#endif // SWAPI_PAINTER_H
