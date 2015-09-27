#include "fontmetrics.h"
#include "rawfont.h"

namespace hsm{

fontmetrics::fontmetrics(){
    //
}

fontmetrics::fontmetrics(const hsm::font &font){
    _font = font;
}

glyphmetrics fontmetrics::glyphMetrics(uint32 charcode) const{
    if(!_font.raw())
        return glyphmetrics();
    return _font.raw()->metrics(_font.pixelSize(), charcode);
}

float fontmetrics::width(uint32 charcode) const{
    if(!_font.raw())
        return 0.0f;
    return _font.raw()->metrics(_font.pixelSize(), charcode).width;
}

float fontmetrics::advance(uint32 charcode) const{
    if(!_font.raw())
        return 0.0f;
    return _font.raw()->metrics(_font.pixelSize(), charcode).advance;
}

float fontmetrics::height() const{
    if(!_font.raw())
        return 0.0f;
    return _font.raw()->height(_font.pixelSize());
}

float fontmetrics::ascender() const{
    if(!_font.raw())
        return 0.0f;
    return _font.raw()->ascender(_font.pixelSize());
}

rectf fontmetrics::box(const std::string &str, float width) const{
    (void)str;
    (void)width;
    /*uint32 surrogate;
    float w = 0.0f;
    float max_w = 0.0f;
    float lh = height();
    float h = lh;
    for(const Char c : str){
        if(c == '\n'){
            h += lh;
            w = 0.0f;
        }else if(c.isHighSurrogate()){
            surrogate = c.unicode() << 4;
        }else{
            uint32 unicode = c.unicode();
            if(c.isLowSurrogate())
                unicode |= surrogate;
            glyphmetrics gm = glyphMetrics(unicode);
            if(width > 0.0f && w+gm.advance > width){
                h += lh;
                if(w+gm.width > width)
                    w = 0.0f;
                else
                    w = -gm.advance;
            }
            w += gm.advance;
            if(w > max_w)
                max_w = w;
        }
    }
    return RectF(0.0f, 0.0f, max_w, h);*/
    return rectf();
}

}
