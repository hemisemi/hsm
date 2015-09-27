#ifndef FONT_H
#define FONT_H

#include <string>

namespace hsm{

class rawfont;
class color;
class fontmetrics;

class font{
public:
    enum Style{
        Normal = 0,
        Bold = 1,
        Italic = 2
    };

    font(const std::string & family = "", int pixel_size = 24, font::Style style = Normal);

    rawfont *raw() const;
    fontmetrics metrics() const;

    const std::string & family() const;
    void setFamily(const std::string & str);

    int pixelSize() const;
    void setPixelSize(int size);

    font::Style style() const;
    void setStyle(font::Style style);

    static bool exists(const std::string & family);

private:
    std::string _family;
    Style _style;
    int _pixel_size;

    void _update();
    mutable rawfont *_raw;
};

}

#endif // FONT_H
