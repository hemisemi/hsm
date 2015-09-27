#ifndef FONTLIBRARY_H
#define FONTLIBRARY_H

#include <map>
#include <list>
#include "font.h"

namespace hsm{

class rawfont;

class fontfamily{
public:
    fontfamily(const std::string & family);

    std::string family() const;

    rawfont *query(font::Style style);
    void append(rawfont *);
private:
    std::string _family;
    std::list<rawfont *> _raw_fonts;
};

class fontlibrary{
public:
    static void initialize();

    static rawfont *query(const std::string & family, font::Style style);
    static bool exists(const std::string & family);

    static void append(rawfont *rw, const std::string & family);
};

}

#endif // FONTLIBRARY_H
