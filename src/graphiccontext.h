#ifndef SWAPI_GRAPHICCONTEXT_H
#define SWAPI_GRAPHICCONTEXT_H

#include "types.h"

namespace hsm{

class GraphicContext{
public:
    virtual ~GraphicContext();

    virtual uint getTextureId(const uint8 *data, char internal_format, int width, int height) = 0;
    virtual void bindTexture(uint id) = 0;
    virtual void releaseTexture() = 0;
    virtual void refreshTexture(uint id, const uint8 *data, char internal_format, int width, int height) = 0;
    virtual void destroyTexture(uint id) = 0;

    virtual void make_current();
    virtual void release();

    static GraphicContext *current();

protected:
    static GraphicContext *_current;
};

}

#endif // SWAPI_GRAPHICCONTEXT_H
