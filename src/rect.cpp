#include "rect.h"
#include "point.h"
#include "size.h"
#include <algorithm>

namespace hsm{

rect::rect(){
    _x = _y = _w = _h = 0;
}

rect::rect(int x, int y, int width, int height){
    _x = x;
    _y = y;
    _w = 0;
    _h = 0;
    set_width(width);
    set_height(height);
}

rect rect::null(){
    return rect();
}

bool rect::is_null() const{
    return _w <= 0 || _h <= 0;
}

bool rect::operator ==(const hsm::rect & rect) const{
    return (_x == rect.x() && _y == rect.y() && _w == rect.width() && _h == rect.height());
}

bool rect::operator !=(const hsm::rect & rect) const{
    return !operator ==(rect);
}

rect rect::united(const hsm::rect &rect) const{
    int x = std::min<int>(this->x(), rect.x());
    int y = std::min<int>(this->y(), rect.y());
    int right = std::max<int>(this->right(), rect.right());
    int bottom = std::max<int>(this->bottom(), rect.bottom());
    return hsm::rect(x, y, x+right, y+bottom);
}

point rect::pos() const{
    return point(_x, _y);
}

size rect::size() const{
    return hsm::size(_w, _h);
}

int rect::x() const{
    return _x;
}

int rect::y() const{
    return _y;
}

int rect::width() const{
    return _w;
}

int rect::height() const{
    return _h;
}

int rect::left() const{
    return _x;
}

int rect::top() const{
    return _y;
}

int rect::right() const{
    return _x+_w;
}

int rect::bottom() const{
    return _y+_h;
}

point rect::top_left() const{
    return pos();
}

point rect::top_right() const{
    return point(_x+_w, _y);
}

point rect::bottom_left() const{
    return point(_x, _y+_h);
}

point rect::bottom_right() const{
    return point(_x+_w, _y+_h);
}

void rect::set_x(int x){
    _x = x;
}

void rect::set_y(int y){
    _y = y;
}

void rect::set_width(int width){
    _w = width < 0 ? 0 : width;
}

void rect::set_height(int height){
    _h = height < 0 ? 0 : height;
}

void rect::resize(int width, int height){
    set_width(width);
    set_height(height);
}

void rect::move(int x, int y){
    _x = x;
    _y = y;
}

void rect::move(const hsm::point &point){
    _x = point.x();
    _y = point.y();
}

void rect::translate(int x, int y){
    _x += x;
    _y += y;
}

void rect::translate(const hsm::point &point){
    _x += point.x();
    _y += point.y();
}

void rect::set(int x, int y, int width, int height){
    set_x(x);
    set_y(y);
    set_width(width);
    set_height(height);
}

void rect::set(const rect & r){
    set_x(r.x());
    set_y(r.y());
    set_width(r.width());
    set_height(r.height());
}

bool rect::contains(const hsm::point &point) const{
    return contains(point.x(), point.y());
}

bool rect::contains(int x, int y) const{
    return (x >= _x && y >= _y && x < _x+_w && y < _y+_h);
}

bool rect::intersects(const rect &r) const{
    return ((r.left() >= left() && r.left() < right()) || (left() >= r.left() && left() < r.right()))
            && ((r.top() >= top() && r.top() < bottom()) || (top() >= r.top() && top() < r.bottom()));
}

rect rect::intersected(const hsm::rect &rect) const{
    int x = std::max<int>(_x, rect.x());
    int y = std::max<int>(_y, rect.y());
    return hsm::rect(x, y,
                std::min<int>(right(), rect.right())-x,
                std::min<int>(bottom(), rect.bottom())-y);
}

bool rect::include(const hsm::rect &rect) const{
    return contains(rect.top_left()) && contains(rect.top_right()) && contains(rect.bottom_left()) && contains(rect.bottom_right());
}

}

/*swapi::TextStream & operator << (swapi::TextStream & stream, const swapi::Rect & value){
    return stream << "(" << value.x() << ", " << value.y() << ", " << value.width() << ", " << value.height() << ")";
}*/
