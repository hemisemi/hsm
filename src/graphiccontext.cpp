#include "graphiccontext.h"

namespace hsm{

GraphicContext *GraphicContext::_current = 0;

GraphicContext::~GraphicContext(){
    //
}

GraphicContext *GraphicContext::current(){
    return _current;
}

void GraphicContext::make_current(){
    _current = this;
}

void GraphicContext::release(){
    if(_current == this)
        _current = 0;
}

}
