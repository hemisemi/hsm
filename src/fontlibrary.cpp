#include "fontlibrary.h"
#include "file.h"
#include "rawfont_ft.h"
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace hsm{

FT_Library ft_lib;
std::map<std::string, fontfamily *> _families;

void fontlibrary::initialize(){
    if(FT_Init_FreeType(&ft_lib)){
        std::cerr << "cannot initialize FreeType font library" << std::endl;
    }
}

rawfont *fromFT(uint8 *data, int size, bool *ok){
    *ok = false;
    FT_Face face;
    if(FT_New_Memory_Face(ft_lib, (const FT_Byte *)data, size, 0, &face)){
        return 0;
    }
    *ok = true;
    return new rawfont_ft(face, data);
}

rawfont *fromFNT(uint8 *data, int size, bool *ok){
    (void)data;
    (void)size;
    *ok = false;
    return 0;
}

bool fontlibrary::exists(const std::string & family){
    if(family.empty())
        return false;
    auto it = _families.find(family);
    if(it != _families.end())
        return true;
    if(file::exists(family))
        return true;
    return false;
}

void fontlibrary::append(rawfont *rw, const std::string & family){
    if(!rw || family.empty())
        return;
    fontfamily *f = 0;
    auto it = _families.find(family);
    if(it != _families.end()){
        f = it->second;
    }else{
        f = new fontfamily(family);
        _families[f->family()] = f;
    }
    f->append(rw);
}

rawfont *fontlibrary::query(const std::string & family, font::Style style){
    if(family.empty())
        return 0;
    std::map<std::string, fontfamily*>::const_iterator it = _families.find(family);
    fontfamily *f = 0;
    if(it != _families.end()){
        f = it->second;
        rawfont *raw = f->query(style);
        if(raw)
            return raw;
    }
    if(file::exists(family)){
        file file(family);
        if(!file.open(iodevice::ReadOnly)){
            std::cerr << "cannot open file `" << family.data() << "'" << std::endl;
            return 0;
        }
        bytearray data = file.readAll();
        uint8 *mem = new uint8[data.size()];
        memcpy(mem, data.data(), data.size());
        file.close();
        rawfont *raw = 0;
        bool ok = false;
        raw = fromFT(mem, data.size(), &ok);
        if(!ok)
            raw = fromFNT(mem, data.size(), &ok);
        if(!ok){
            std::cerr << "unknown font type" << std::endl;
            return 0;
        }
        if(ok && raw){
            if(!f && !raw->family().empty()){
                f = new fontfamily(raw->family());
                _families[raw->family()] = f;
            }
            if(f)
                f->append(raw);
        }
        return raw;
    }else{
        std::cerr << "unknown font family : `" << family.data() << "'" << std::endl;
    }
    return 0;
}

fontfamily::fontfamily(const std::string &family){
    _family = family;
}

std::string fontfamily::family() const{
    return _family;
}

void fontfamily::append(rawfont *raw){
    _raw_fonts.push_back(raw);
}

rawfont *fontfamily::query(font::Style style){
    for(rawfont *raw : _raw_fonts){
        if(raw->matchStyle(style))
            return raw;
    }
    return 0;
}

}
