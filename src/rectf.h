#ifndef SWAPI_RECTF_H
#define SWAPI_RECTF_H

namespace hsm{

class pointf;
class sizef;
class rect;

class rectf{
public:
    rectf();
    rectf(float x, float y, float width, float height);

    static rectf null();
    bool is_null() const;

    rectf united(const rectf & rect) const;
    bool intersects(const rectf & r) const;
    rectf intersected(const rectf & rect) const;

    bool include(const rectf & rect) const;

    float x() const;
    float y() const;
    float width() const;
    float height() const;

    float left() const;
    float top() const;
    float right() const;
    float bottom() const;

    pointf pos() const;
    sizef size() const;

    pointf top_left() const;
    pointf top_right() const;
    pointf bottom_left() const;
    pointf bottom_right() const;

    rect to_rect() const;

    void set_x(float x);
    void set_y(float y);
    void set_width(float width);
    void set_height(float height);
    void resize(float width, float height);
    void move(float x, float y);
    void move(const pointf & point);
    void translate(float x, float y);
    void translate(const pointf & point);

    void set(float x, float y, float width, float height);
    void set(const rectf &);

    bool contains(const pointf &point) const;
    bool contains(float x, float y) const;

    bool operator==(const rectf & rect) const;
    bool operator!=(const rectf & rect) const;

private:
    float _x;
    float _y;
    float _w;
    float _h;
};

}

//mol::TextStream & operator << (mol::TextStream & stream, const mol::Rect & value);

#endif // RECTF_H
