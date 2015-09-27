#include "bitmap_paintengine.h"
#include "rawfont_ft.h"
#include "rawfont_fnt.h"
#include "bitmap.h"

namespace hsm{

bitmap_paintengine::bitmap_paintengine(){
    _bmp = 0;
}

void bitmap_paintengine::begin(paintdevice *pdev){
    _bmp = dynamic_cast<bitmap *>(pdev);
}

void bitmap_paintengine::end(){
    if(_bmp){
        _bmp->refresh();
        //_bmp->soe_unlock();
    }
}

void bitmap_paintengine::clip(const rect &){
    //
}

void bitmap_paintengine::blendPixel(int x, int y, const color & c){
    /*float a = c.alphaf()*_opacity;
    color ac = _bmp->pixel(x, y);
    //dst[0]*(1.0-(o*((float)*src/255.0)))+(*src)*red;
    int red = (ac.red()*(1.0-a))+(a*c.red());
    int green = (ac.green()*(1.0-a))+(a*c.green());
    int blue = (ac.blue()*(1.0-a))+(a*c.blue());
    int alpha = (ac.alpha()*(1.0-a))+(a*c.alpha());
    _bmp->setPixel(x, y, color(red, green, blue, alpha));*/
}

void bitmap_paintengine::draw_bitmap(const rect &target, const hsm::bitmap &bitmap, const rect &source){
    /*hsm::bitmap bmp = bitmap.copy(source).scaled(target.width(), target.height());
    rect r = _bmp->rect().intersected(target);
    if(!r.isNull()){
        int sox = r.x()-target.x();
        int soy = r.y()-target.y();
        for(int y = 0; y < r.height(); ++y){
            for(int x = 0; x < r.width(); ++x){
                //_bmp->setPixel(r.x()+x, r.y()+y, bmp.pixel(sox+x, soy+y));
                blendPixel(r.x()+x, r.y()+y, bmp.pixel(sox+x, soy+y));
            }
        }
    }*/
}

void bitmap_paintengine::draw_points(const point *, int){
    //
}

void bitmap_paintengine::draw_points(const pointf *, int){
    //
}

/*int bitmap_paint_engine::draw_char(int x, int y, uint32 unicode, const rect *clip){
    rawfont *raw = t.font.raw();
    rawfont_ft *ft = dynamic_cast<rawfont_ft*>(raw);
    //t.pen.setColor(Color(255, 100, 100));
    if(ft){
        const color & c = t.pen.color();
        const rawfont_ft::glyph *g = ft->get_glyph(t.font.pixelSize(), unicode);
        if(g){
            y -= g->metrics.bearing_y;
            x += g->metrics.bearing_x;
            rect r(x, y, g->bitmap.width, g->bitmap.height);
            if(clip)
                r = clip->intersected(r);
            if(!r.isNull()){
                int sox = x-r.x();
                int soy = y-r.y();
                for(int sy = soy; sy < soy+r.height(); ++sy){
                    for(int sx = sox; sx < sox+r.width(); ++sx){
                        blendPixel(x+sx, y+sy, color(c.red(), c.green(), c.blue(), c.alphaF()*g->bitmap.data[sy*g->bitmap.width+sx]));
                    }
                }
            }
            return g->metrics.advance;
        }
    }
    rawfont_fnt *fnt = dynamic_cast<rawfont_fnt*>(raw);
    if(fnt){
        const rawfont_fnt::glyph *g = fnt->get_glyph(unicode);
        if(g){
            y -= g->metrics.bearing_y;
            x += g->metrics.bearing_x;
            //std::cout << "> " << x << ", " << y << ", " << g->rect.width() << std::endl;
            draw_bitmap(rect(x, y, g->rect.width(), g->rect.height()), *fnt->bitmap(), g->rect);
            return g->metrics.advance;
        }
    }
    return 0;
}*/

void bitmap_paintengine::draw_rects(const rectf *rect, int n){
    //
}

void bitmap_paintengine::draw_rects(const rect *rect, int n){
    /*uint8 pixel[_bmp->_internal_format];
    for(int j = 0; j < _bmp->_internal_format; ++j){
        switch(j){
        case 0:
            pixel[j] = t.brush.color().red();
        case 1:
            pixel[j] = t.brush.color().green();
        case 2:
            pixel[j] = t.brush.color().blue();
        default:
            pixel[j] = t.brush.color().alpha();
        }
    }*/
    /*const color & c = t.brush.color();
    float o = c.alphaf();
    int red = o*c.red();
    int green = o*c.green();
    int blue = o*c.blue();
    int alpha = o*c.alpha();
    for(int i = 0; i < n; ++i){
        hsm::rect r = _bmp->rect().intersected(rect[i]);
        if(!r.isNull()){
            //std::cout << "rect : " << r.x() << ", " << r.y() << ", " << r.width() << ", " << r.height() << std::endl;
            //int llen = r.width()*_bmp->_internal_format;
            //uint8 line[llen];
            //for(int p = 0; p < llen; p += _bmp->_internal_format)
            //    memcpy(line+p, pixel, _bmp->_internal_format);
            //for(int p = r.y(); p < r.height()+r.y(); ++p){
            //    memcpy(_bmp->_data+p*_bmp->width()*_bmp->_internal_format+r.x()*_bmp->_internal_format, line, llen);
            //}
            //
            int offsx = r.x()*_bmp->_internal_format;
            int llen = (_bmp->width()-r.width())*_bmp->_internal_format;
            size_t size = r.width()*r.height();
            uint8 *dst = _bmp->_data+r.y()*_bmp->width()*_bmp->_internal_format+offsx;
            int col = 0;
            for(size_t i = 0; i < size; ++i){
                switch(_bmp->_internal_format){
                case 1:
                    dst[0] = dst[0]*(1.0-o)+red;
                    break;
                case 2:
                    dst[0] = dst[0]*(1.0-o)+red;
                    dst[1] = dst[1]*(1.0-o)+green;
                    break;
                case 3:
                    dst[0] = dst[0]*(1.0-o)+red;
                    dst[1] = dst[1]*(1.0-o)+green;
                    dst[2] = dst[2]*(1.0-o)+blue;
                case 4:
                    dst[0] = dst[0]*(1.0-o)+red;
                    dst[1] = dst[1]*(1.0-o)+green;
                    dst[2] = dst[2]*(1.0-o)+blue;
                    dst[3] = dst[3]*(1.0-o)+alpha;
                    break;
                default:
                    break;
                }
                 ++col;
                dst += _bmp->_internal_format;
                if(col >= r.width()){
                    col = 0;
                    dst += llen;
                }
            }
        }
    }*/
}

}
