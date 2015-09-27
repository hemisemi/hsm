#pragma once

namespace hsm{

class paintengine;

class paintdevice{
public:
    paintdevice();
    virtual ~paintdevice();

    virtual paintengine *paint_engine() const = 0;

    virtual int width() const = 0;
    virtual int height() const = 0;
};

}
