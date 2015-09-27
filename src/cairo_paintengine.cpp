#include "cairo_paintengine.h"
#include "cairo_compatible_paintdevice.h"
#include "point.h"
#include "pointf.h"
#include "rect.h"
#include "rectf.h"
#include <iostream>

namespace hsm{

cairo_paintengine::~cairo_paintengine(){
    end();
}

cairo_surface_t *cairo_paintengine::surface() const{
    if(!device())
        return 0;
    cairo_compatible_paintdevice *cdevice = dynamic_cast<cairo_compatible_paintdevice*>(device());
    if(!cdevice){
        std::cerr << "cairo_paintengine::surface() : Not a cairo compatible paint device." << std::endl;
        return 0;
    }
    return cdevice->cairo_surface();
}

void cairo_paintengine::begin(paintdevice *pdev){
    paintengine::begin(pdev);
    cairo_surface_t *s = surface();
    if(!s){
        paintengine::end();
        std::cerr << "cairo_paintengine::begin() : Cannot paint on this device." << std::endl;
        return;
    }
    _cr = cairo_create(s);
}

void cairo_paintengine::end(){
    cairo_destroy(_cr);
    _cr = 0;
}

void cairo_paintengine::clip(const hsm::rect &){
    //
}

void cairo_paintengine::set_pen_as_source(){
    cairo_set_source_rgba(_cr, pen().color().redf(), pen().color().greenf(), pen().color().bluef(), pen().color().alphaf());
}

void cairo_paintengine::set_brush_as_source(){
    cairo_set_source_rgba(_cr, brush().color().redf(), brush().color().greenf(), brush().color().bluef(), brush().color().alphaf());
}

void cairo_paintengine::matrix_changed(const hsm::matrix3x3 & m){
    if(!device())
        return;
    cairo_matrix_t cm = {m(0, 0), m(1, 0), m(0, 1), m(1, 1), m(0, 2), m(1, 2)};
    cairo_set_matrix(_cr, &cm);
}

void cairo_paintengine::draw_points(const hsm::point *point, int n){
    if(!device())
        return;
    set_brush_as_source();
    for(int i = 0; i < n; ++i){
        cairo_rectangle(_cr, (double)point->x(), (double)point->y(), 1.0, 1.0);
    }
    cairo_fill(_cr);
}

void cairo_paintengine::draw_points(const pointf *point, int n){
    if(!device())
        return;
    set_brush_as_source();
    for(int i = 0; i < n; ++i){
        cairo_rectangle(_cr, (double)point->x(), (double)point->y(), 1.0, 1.0);
    }
    cairo_fill(_cr);
}

void cairo_paintengine::draw_rects(const rectf *rect, int n){
    if(!device())
        return;
    set_brush_as_source();
    for(int i = 0; i < n; ++i){
        cairo_rectangle(_cr, (double)rect->x(), (double)rect->y(), (double)rect->width(), (double)rect->height());
    }
    cairo_fill(_cr);
}

void cairo_paintengine::draw_rects(const hsm::rect *rect, int n){
    if(!device())
        return;
    set_brush_as_source();
    for(int i = 0; i < n; ++i){
        cairo_rectangle(_cr, (double)rect->x(), (double)rect->y(), (double)rect->width(), (double)rect->height());
    }
    cairo_fill(_cr);
}

void cairo_paintengine::draw_bitmap(const rect &target, const bitmap &bitmap, const rect &source){
    if(!device())
        return;
}

}
