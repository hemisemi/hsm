#include "color.h"

namespace hsm{

color::color(int r, int g, int b, int a){
    _r = r;
    _g = g;
    _b = b;
    _a = a;
}

color::color(const DefaultColor & n){
    switch(n){
    case hsm::transparent:
        set(0, 0, 0, 0);
        break;
    case hsm::white:
        set(255, 255, 255);
        break;
    case hsm::black:
        set(0, 0, 0);
        break;
    case hsm::red:
        set(255, 0, 0);
        break;
    case hsm::green:
        set(0, 255, 0);
        break;
    case hsm::blue:
        set(0, 0, 255);
        break;
    default:
        break;
    }
}

color::color(){
    _r = 0;
    _g = 0;
    _b = 0;
    _a = 255;
}

bool color::operator ==(const color & c) const{
    return _r == c.red() && _g == c.green() && _b == c.blue() && _a == c.alpha();
}

bool color::operator !=(const color & c) const{
    return !operator==(c);
}

void color::set(int r, int g, int b, int a){
    _r = r;
    _g = g;
    _b = b;
    _a = a;
}

bool color::transparent() const{
    return _a == 0;
}

int color::red() const{
    return _r;
}

int color::green() const{
    return _g;
}

int color::blue() const{
    return _b;
}

int color::alpha() const{
    return _a;
}

void color::set_red(int r){
    _r = r;
}

void color::set_green(int g){
    _g = g;
}

void color::set_blue(int b){
    _b = b;
}

void color::set_alpha(int a){
    _a = a;
}

#define MIN3(x,y,z)  ((y) <= (z) ? \
                         ((x) <= (y) ? (x) : (y)) \
                     : \
                         ((x) <= (z) ? (x) : (z)))

#define MAX3(x,y,z)  ((y) >= (z) ? \
                         ((x) >= (y) ? (x) : (y)) \
                     : \
                         ((x) >= (z) ? (x) : (z)))

color::HSV::HSV(int hue, unsigned char sat, unsigned char value, unsigned char alpha){
    this->hue = hue;
    this->saturation = sat;
    this->value = value;
    this->alpha = alpha;
}

color::HSV color::toHSV() const{
    HSV hsv(0, 0, 0, _a);
    unsigned char rgb_max = MAX3(_r, _g, _b);
    unsigned char rgb_min = MIN3(_r, _g, _b);
    int dif = (rgb_max - rgb_min);
    hsv.value = rgb_max;
    if(hsv.value == 0)
        return hsv;
    hsv.saturation = 255*dif/hsv.value;
    if(hsv.saturation == 0)
        return hsv;
    if(rgb_max == _r){
        hsv.hue = (60*(_g-_b)/dif);
    }else if(rgb_max == _g){
        hsv.hue = (120+60*(_b-_r)/dif);
    }else{
        hsv.hue = (240+60*(_r-_g)/dif);
    }
    while(hsv.hue < 0)
        hsv.hue += 360;
    while(hsv.hue >= 360)
        hsv.hue -= 360;
    return hsv;
}

color color::fromHSV(HSV hsv){
    color c;
    while(hsv.hue < 0)
        hsv.hue += 360;
    while(hsv.hue >= 360)
        hsv.hue -= 360;
    int d = ((hsv.hue%60)*255)/59;
    c._r = c._g = c._b = 0;
    c._a = hsv.alpha;
    //std::cout << (hsv.hue*6)/360 << std::endl;
    unsigned char rgb_max = hsv.value;
    if(rgb_max == 0)
        return c;
    switch((hsv.hue*6)/360){
    case 0:
        c._r = 255;
        c._g = d;
        break;
    case 1:
        c._g = 255;
        c._r = 255-d;
        break;
    case 2:
        c._g = 255;
        c._b = d;
        break;
    case 3:
        c._b = 255;
        c._g = 255-d;
        break;
    case 4:
        c._b = 255;
        c._r = d;
        break;
    default:
        c._r = 255;
        c._b = 255-d;
        break;
    }
    int max = MAX3(c._r, c._g, c._b);
    int dif = (hsv.saturation*rgb_max)/255;
    unsigned char rgb_min = rgb_max-dif;
    /*std::cout << (int)rgb_max << std::endl;
    std::cout << (int)rgb_min << std::endl;
    std::cout << dif << std::endl;*/
    c._r = ((c._r*dif)/max)+rgb_min;
    c._g = ((c._g*dif)/max)+rgb_min;
    c._b = ((c._b*dif)/max)+rgb_min;
    //unsigned char rgb_min = MIN3(_r, _g, _b);
    return c;
}

float color::redf() const{
    return (float)_r/255.0;
}

float color::greenf() const{
    return (float)_g/255.0;
}

float color::bluef() const{
    return (float)_b/255.0;
}

float color::alphaf() const{
    return (float)_a/255.0;
}

}
