#include "rectf.h"
#include "pointf.h"
#include "sizef.h"
#include "rect.h"
#include <algorithm>

namespace hsm{

rectf::rectf(){
    _x = _y = _w = _h = 0;
}

rectf::rectf(float x, float y, float width, float height){
    _x = x;
    _y = y;
    _w = 0;
    _h = 0;
    set_width(width);
    set_height(height);
}

rectf rectf::null(){
    return rectf();
}

bool rectf::is_null() const{
    return _w <= 0 || _h <= 0;
}

bool rectf::operator ==(const rectf & rect) const{
    return (_x == rect.x() && _y == rect.y() && _w == rect.width() && _h == rect.height());
}

bool rectf::operator !=(const rectf & rect) const{
    return !operator ==(rect);
}

rectf rectf::united(const rectf &rect) const{
    float x = std::min<float>(this->x(), rect.x());
    float y = std::min<float>(this->y(), rect.y());
    float right = std::max<float>(this->right(), rect.right());
    float bottom = std::max<float>(this->bottom(), rect.bottom());
    return rectf(x, y, x+right, y+bottom);
}

pointf rectf::pos() const{
    return pointf(_x, _y);
}

sizef rectf::size() const{
    return sizef(_w, _h);
}

rect rectf::to_rect() const{
    return rect((int)_x, (int)_y, (int)_w, (int)_h);
}

float rectf::x() const{
    return _x;
}

float rectf::y() const{
    return _y;
}

float rectf::width() const{
    return _w;
}

float rectf::height() const{
    return _h;
}

float rectf::left() const{
    return _x;
}

float rectf::top() const{
    return _y;
}

float rectf::right() const{
    return _x+_w;
}

float rectf::bottom() const{
    return _y+_h;
}

pointf rectf::top_left() const{
    return pos();
}

pointf rectf::top_right() const{
    return pointf(_x+_w, _y);
}

pointf rectf::bottom_left() const{
    return pointf(_x, _y+_h);
}

pointf rectf::bottom_right() const{
    return pointf(_x+_w, _y+_h);
}

void rectf::set_x(float x){
    _x = x;
}

void rectf::set_y(float y){
    _y = y;
}

void rectf::set_width(float width){
    _w = width < 0 ? 0 : width;
}

void rectf::set_height(float height){
    _h = height < 0 ? 0 : height;
}

void rectf::resize(float width, float height){
    set_width(width);
    set_height(height);
}

void rectf::move(float x, float y){
    _x = x;
    _y = y;
}

void rectf::move(const pointf &point){
    _x = point.x();
    _y = point.y();
}

void rectf::translate(float x, float y){
    _x += x;
    _y += y;
}

void rectf::translate(const pointf &point){
    _x += point.x();
    _y += point.y();
}

void rectf::set(float x, float y, float width, float height){
    set_x(x);
    set_y(y);
    set_width(width);
    set_height(height);
}

void rectf::set(const rectf & r){
    set_x(r.x());
    set_y(r.y());
    set_width(r.width());
    set_height(r.height());
}

bool rectf::contains(const pointf &point) const{
    return contains(point.x(), point.y());
}

bool rectf::contains(float x, float y) const{
    return (x >= _x && y >= _y && x < _x+_w && y < _y+_h);
}

bool rectf::intersects(const rectf &r) const{
    return ((r.left() >= left() && r.left() < right()) || (left() >= r.left() && left() < r.right()))
            && ((r.top() >= top() && r.top() < bottom()) || (top() >= r.top() && top() < r.bottom()));
}

rectf rectf::intersected(const rectf &rect) const{
    float x = std::max<float>(_x, rect.x());
    float y = std::max<float>(_y, rect.y());
    return rectf(x, y,
                std::min<float>(right(), rect.right())-x,
                std::min<float>(bottom(), rect.bottom())-y);
}

bool rectf::include(const rectf &rect) const{
    return contains(rect.top_left()) && contains(rect.top_right()) && contains(rect.bottom_left()) && contains(rect.bottom_right());
}

}

/*swapi::TextStream & operator << (swapi::TextStream & stream, const swapi::rectf & value){
    return stream << "(" << value.x() << ", " << value.y() << ", " << value.width() << ", " << value.height() << ")";
}*/
