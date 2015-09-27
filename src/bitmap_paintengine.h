#ifndef BITMAP_PAINTENGINE_H
#define BITMAP_PAINTENGINE_H

#include <paintengine.h>

namespace hsm{

class pointf;
class rectf;

class bitmap_paintengine : public paintengine{
public:
    bitmap_paintengine();

    void begin(paintdevice *pdev);
    void end();

    void clip(const rect &);

    void blendPixel(int x, int y, const color & c);

    void draw_bitmap(const rect & target, const hsm::bitmap & bitmap, const rect & source);
    void draw_points(const point *points, int n);
    void draw_points(const pointf *points, int n);
    void draw_rects(const rectf *rects, int n);
    void draw_rects(const rect *rects, int n);

private:
    bitmap *_bmp;
};

}

#endif // BITMAP_PAINTENGINE_H
