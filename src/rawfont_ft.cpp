#include "rawfont_ft.h"
#include "file.h"
#include <exception>
#include <iostream>

namespace hsm{

rawfont_ft::rawfont_ft(FT_Face face, const uint8 *data){
    _face = face;
    _data = data;
    _family = _face->family_name;
    _style = font::Normal;
    if(face->style_flags & FT_STYLE_FLAG_ITALIC)
        _style = (font::Style)(_style|font::Italic);
    if(face->style_flags & FT_STYLE_FLAG_BOLD)
        _style = (font::Style)(_style|font::Bold);
}

rawfont_ft::~rawfont_ft(){
    FT_Done_Face(_face);
    delete[] _data;
}

std::string rawfont_ft::family() const{
    return _family;
}

bool rawfont_ft::matchStyle(font::Style style) const{
    return _style == style;
}

glyphmetrics rawfont_ft::metrics(int pixel_size, uint32 charcode) const{
    const glyph *g = get_glyph(pixel_size, charcode);
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

int rawfont_ft::height(int pixel_size) const{
    FT_Set_Pixel_Sizes(_face, pixel_size, pixel_size);
    //std::cout << (_face->height>>6) << std::endl;
    return _face->height >> 6;
}

int rawfont_ft::ascender(int pixel_size) const{
    FT_Set_Pixel_Sizes(_face, pixel_size, pixel_size);
    //std::cout << _face->bbox.yMax << std::endl;
    return (_face->ascender >> 6);
}

const rawfont_ft::glyph *rawfont_ft::get_glyph(int pixel_size, uint32 charcode) const{
    auto it = _charmap.find(pixel_size);
    if(it == _charmap.end())
        _charmap[pixel_size] = std::map<uint32, glyph>();
    std::map<uint32, glyph> & map = _charmap[pixel_size];
    auto mit = map.find(charcode);
    if(mit == map.end()){
        FT_Set_Pixel_Sizes(_face, pixel_size, pixel_size);
        /* retrieve glyph index from character code */
        FT_UInt glyph_index = FT_Get_Char_Index(_face, charcode);
        glyph & g = map[charcode] = glyph();
        g.bitmap.data = 0;
        g.bitmap.width = 0;
        g.bitmap.height = 0;
        g.metrics.width = pixel_size >> 1;
        g.metrics.height = 0;
        g.metrics.bearing_x = 0;
        g.metrics.bearing_y = 0;
        g.metrics.advance = pixel_size >> 1;
        try{
            if(FT_Load_Glyph(_face, glyph_index, FT_LOAD_DEFAULT))
                return 0;
            if(FT_Render_Glyph(_face->glyph, FT_RENDER_MODE_NORMAL))
                return 0;
            FT_Bitmap bitmap = _face->glyph->bitmap;
            g.bitmap.width = bitmap.width;
            g.bitmap.height = bitmap.rows;
            g.bitmap.data = new uint8[g.bitmap.width*g.bitmap.height];
            memcpy(g.bitmap.data, bitmap.buffer, g.bitmap.width*g.bitmap.height);
            //
            FT_Glyph_Metrics metrics = _face->glyph->metrics;
            g.metrics.width = (float)metrics.width/64;
            g.metrics.height = (float)metrics.height/64;
            g.metrics.bearing_x = (float)metrics.horiBearingX/64;
            g.metrics.bearing_y = (float)metrics.horiBearingY/64;
            g.metrics.advance = (float)metrics.horiAdvance/64;
        }catch(std::exception & e){
            std::cout << "warning : FreeType library crash : " << e.what() << std::endl;
        }
        //
        return &g;
    }
    return &(*mit).second;
}

}
