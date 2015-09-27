#ifndef SWAPI_RECT_H
#define SWAPI_RECT_H

namespace hsm{

class point;
class size;

class rect{
public:
    rect();
    rect(int x, int y, int width, int height);

    static rect null();
    bool is_null() const;

    rect united(const hsm::rect & rect) const;
    bool intersects(const rect & r) const;
    rect intersected(const hsm::rect & rect) const;

    bool include(const hsm::rect & rect) const;

    int x() const;
    int y() const;
    int width() const;
    int height() const;

    int left() const;
    int top() const;
    int right() const;
    int bottom() const;

    point pos() const;
    hsm::size size() const;

    point top_left() const;
    point top_right() const;
    point bottom_left() const;
    point bottom_right() const;

    void set_x(int x);
    void set_y(int y);
    void set_width(int width);
    void set_height(int height);
    void resize(int width, int height);
    void move(int x, int y);
    void move(const point & point);
    void translate(int x, int y);
    void translate(const point & point);

    void set(int x, int y, int width, int height);
    void set(const rect &);

    bool contains(const point &point) const;
    bool contains(int x, int y) const;

    bool operator==(const rect & rect) const;
    bool operator!=(const rect & rect) const;

private:
    int _x;
    int _y;
    int _w;
    int _h;
};

}

#endif // RECT_H
