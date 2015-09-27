#include "painter.h"
#include "paintdevice.h"
#include "paintengine.h"
#include "string.h"
#include "font.h"
#include "rect.h"
#include "bitmap.h"
#include "fontmetrics.h"
#include <iostream>

namespace hsm{

painter::painter(){
    _device = 0;
    _engine = 0;
    _opacity = 1.0;
}

painter::painter(paintdevice *device) : painter(){
    begin(device);
    //_font = 0;
}

void painter::begin(paintdevice *device){
    end();
    _device = device;
    _engine = 0;
    if(_device){
        _engine = device->paint_engine();
        if(_engine)
            _engine->begin(device);
    }
}

void painter::end(){
    if(_engine){
        _engine->end();
        delete _engine;
    }
    _device = 0;
    _engine = 0;
}

void painter::draw_bitmap(int x, int y, const hsm::bitmap &bitmap, const rect & source){
    draw_bitmap(rect(x, y, source.width(), source.height()), bitmap, source);
}

void painter::draw_bitmap(int x, int y, int width, int height, const hsm::bitmap &bitmap, const rect & source){
    draw_bitmap(rect(x, y, width, height), bitmap, source);
}

void painter::draw_bitmap(const rect &target, const hsm::bitmap &bitmap, const rect &source){
    if(_engine)
        _engine->draw_bitmap(target.is_null() ? bitmap.rect() : target, bitmap, source.is_null() ? bitmap.rect() : source);
    else
        std::cerr << "No paint engine" << std::endl;
}

void painter::draw_point(const hsm::point &point){
    if(_engine)
        _engine->draw_points(&point, 1);
    else
        std::cerr << "No paint engine" << std::endl;
}

void painter::draw_rect(const hsm::rect &rect){
    if(_engine)
        _engine->draw_rects(&rect, 1);
    else
        std::cerr << "No paint engine" << std::endl;
}

void painter::draw_text(int x, int y, const std::string & str){
    (void)x;
    (void)y;
    (void)str;
    /*if(!_engine)
        std::cerr << "No paint engine" << std::endl;
    //if(!_font)
    //    cerr << "No font" << endl;
    for(int i = 0; i < str.size(); i++){
        x += _engine->drawChar(x, y, str[i].unicode(), 0);
        //x += 20;
        //x += _font.metrics().width(str[i]);
    }*/
}

void painter::draw_text(const rect &rect, const std::string &str, int flags){
    draw_text(rect.x(), rect.y(), rect.width(), rect.height(), str, flags);
}

void painter::draw_text(int x, int y, int width, int height, const std::string & str, int flags){
    (void)x;
    (void)y;
    (void)width;
    (void)height;
    (void)str;
    (void)flags;
    /*FontMetrics m = _font.metrics();
    RectF box = m.box(str, width);
    RectF r(x, y, width, height);
    y += m.ascender();
    int hflag = flags & hsm::AlignHorizontal_Flag;
    if(hflag == hsm::AlignHCenter){
        x = x+(width-box.width())/2;
    }
    if(hflag == hsm::AlignRight){
        x = x+width-box.width();
    }
    int vflag = flags & hsm::AlignVertical_Flag;
    if(vflag == hsm::AlignVCenter){
        //y = y+(height-box.height())/2;
        y += (height-box.height())/2;
    }
    if(vflag == hsm::AlignBottom){
        //y = y+height-box.height();
        y += height-box.height();
    }
    int rx = x;
    uint32 surrogate;
    for(const Char & c : str){
        if(c == '\n'){
            x = rx;
            y += m.height();
        }else if(c.isHighSurrogate()){
            surrogate = c.unicode() << 4;
        }else{
            uint32 unicode = c.unicode();
            if(c.isLowSurrogate())
                unicode |= surrogate;
            int cw = m.width(unicode);
            if(width > 0 && x+cw > rx+width){
                x = rx;
                y += m.height();
            }
            rect rect = r.toRect();
            x += _engine->drawChar((int)x, (int)y, unicode, &rect);
            //x += _font.metrics().width(c);
        }
    }*/
}

void painter::set_opacity(float o){
    if(o > 1.0)
        o = 1.0;
    if(o < 0.0)
        o = 0.0;
    _opacity = o;
    if(_engine)
        _engine->set_opacity(o);
}

float painter::opacity() const{
    return _opacity;
}

void painter::set_font(const hsm::font &font){
    _font = font;
    /*if(_engine)
        _engine->setFont(_font);*/
}

void painter::set_pen(const hsm::pen &pen){
    _pen = pen;
    if(_engine)
        _engine->set_pen(_pen);
}

void painter::set_brush(const hsm::brush &brush){
    _brush = brush;
    if(_engine)
        _engine->set_brush(_brush);
}

void painter::clip(const hsm::rect &region){
    if(_engine)
        _engine->clip(region);
}

const font & painter::font() const{
    return _font;
}

const brush & painter::brush() const{
    return _brush;
}

const pen & painter::pen() const{
    return _pen;
}

paintengine *painter::engine() const{
    return _engine;
}

}
