#ifndef SWAPI_PAINTENGINE_H
#define SWAPI_PAINTENGINE_H

#include "font.h"
#include "pen.h"
#include "brush.h"
#include "types.h"
#include "matrix3x3.h"

namespace hsm{

class point;
class pointf;
class rect;
class rectf;
class bitmap;
class paintdevice;
class region;

class paintengine{
public:
    paintengine();
    virtual ~paintengine();

    virtual void draw_bitmap(const rect & target, const hsm::bitmap & bitmap, const rect & source) = 0;
    virtual void draw_points(const point *points, int n) = 0;
    virtual void draw_points(const pointf *points, int n) = 0;
    virtual void draw_rects(const rectf *rects, int n) = 0;
    virtual void draw_rects(const rect *rects, int n) = 0;

    virtual void clip(const rect & region) = 0;

    paintdevice *device() const;

    virtual void begin(paintdevice *pdev);
    virtual void end();

    void set_pen(const pen & pen);
    void set_brush(const brush & brush);
    void set_opacity(float);
    void set_matrix(const hsm::matrix3x3 & matrix);

    const hsm::pen & pen() const;
    const hsm::brush & brush() const;
    float opacity() const;
    const hsm::matrix3x3 & matrix() const;

protected:
    virtual void pen_changed(const hsm::pen & pen);
    virtual void brush_changed(const hsm::brush & brush);
    virtual void opacity_changed(float opacity);
    virtual void matrix_changed(const hsm::matrix3x3 & matrix);

protected:
    hsm::pen _pen;
    hsm::brush _brush;
    hsm::matrix3x3 _matrix;
    float _opacity;

    paintdevice *_device;
};

}

#endif // SWAPI_PAINTENGINE_H
