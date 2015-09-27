#include "rawfont_fnt.h"
#include "bitmap.h"

namespace hsm{

rawfont_fnt::rawfont_fnt(hsm::bitmap *bmp, std::map<uint32, glyph> glyphs){
    _bmp = bmp;
    _map = glyphs;
    _height = 0;
    auto it = glyphs.begin();
    if(it != glyphs.end())
        _height = (*it).second.metrics.height;
}

rawfont_fnt::~rawfont_fnt(){
    delete _bmp;
}

bool rawfont_fnt::matchStyle(font::Style) const{
    return true;
}

glyphmetrics rawfont_fnt::metrics(int, uint32 charcode) const{
    const glyph *g = get_glyph(charcode);
    if(g)
        return g->metrics;
    glyphmetrics metrics;
    metrics.advance = 0;
    metrics.bearing_x = 0;
    metrics.bearing_y = 0;
    metrics.height = 0;
    metrics.width = 0;
    return metrics;
}

int rawfont_fnt::height(int) const{
    return _height;
}

int rawfont_fnt::ascender(int) const{
    return 0;
}

const rawfont_fnt::glyph *rawfont_fnt::get_glyph(uint32 charcode) const{
    auto it = _map.find(charcode);
    if(it == _map.end())
        return 0;
    const glyph & g = _map[charcode];
    return &g;
}

bitmap *rawfont_fnt::bitmap() const{
    return _bmp;
}

rawfont_fnt *rawfont_fnt::fromBitmap(hsm::bitmap *bmp, int cw, int ch){
    std::map<uint32, glyph> glyphs;
    int c = 0x20;
    for(int y = 0; y < 14; ++y){
        for(int x = 0; x < 16; ++x){
            glyph g;
            g.metrics.bearing_x = 0.0;
            g.metrics.bearing_y = 0.0;
            if(c == 0x20)
                g.metrics.width = g.metrics.advance = cw*0.33;
            else{
                g.metrics.width = 0;
                for(int i = 0; i < cw; ++i){
                    for(int j = 0; j < ch; ++j){
                        if(bmp->pixel((x*cw)+i, (y*ch)+j).alpha() > 0){
                            ++g.metrics.width;
                            break;
                        }
                    }
                }
            }
            g.metrics.height = ch;
            g.metrics.advance = g.metrics.width+1;
            g.rect.set(x*cw, (13-y)*ch, cw, ch);
            glyphs[c] = g;
            ++c;
        }
    }
    return new rawfont_fnt(bmp, glyphs);
}

}
