#include "paintengine.h"

namespace hsm{

paintengine::paintengine(){
    _opacity = 1.0;
}

paintengine::~paintengine(){
    //
}

void paintengine::begin(paintdevice *pdev){
    _device = pdev;
}

void paintengine::end(){
    //
}

paintdevice *paintengine::device() const{
    return _device;
}

void paintengine::set_opacity(float o){
    _opacity = o;
    opacity_changed(_opacity);
}

void paintengine::set_pen(const hsm::pen &pen){
    _pen = pen;
    pen_changed(_pen);
}

void paintengine::set_brush(const hsm::brush &brush){
    _brush = brush;
    brush_changed(_brush);
}

void paintengine::set_matrix(const matrix3x3 &matrix){
    _matrix = matrix;
    matrix_changed(matrix);
}

const pen &paintengine::pen() const{
    return _pen;
}

const brush &paintengine::brush() const{
    return _brush;
}

float paintengine::opacity() const{
    return _opacity;
}

const hsm::matrix3x3 & paintengine::matrix() const{
    return _matrix;
}

void paintengine::opacity_changed(float){
    //
}

void paintengine::matrix_changed(const matrix3x3 &){
    //
}

void paintengine::pen_changed(const hsm::pen &){
    //
}

void paintengine::brush_changed(const hsm::brush &){
    //
}

}
