#include "iodevice.h"

namespace hsm{

iodevice::iodevice(){
    _mode = NotOpen;
}

bool iodevice::open(OpenMode mode){
    _mode = mode;
    return true;
}

void iodevice::close(){
    _mode = NotOpen;
}

iodevice::OpenMode iodevice::openMode() const{
    return _mode;
}

bool iodevice::isOpen() const{
    return (_mode != NotOpen);
}

bool iodevice::isReadable() const{
    return (_mode & ReadOnly);
}

bool iodevice::isWritable() const{
    return (_mode & WriteOnly);
}

bool iodevice::atEnd() const{
    return pos() >= size();
}

uint64 iodevice::read(char *data, uint64 maxsize) const{
    return _read(data, maxsize);
}

bytearray iodevice::read(uint64 maxsize) const{
    char *data = new char[maxsize];
    std::fill(data, data+maxsize, 0);
    uint64 size = read(data, maxsize);
    bytearray ary = bytearray(data, size);
    delete[] data;
    return ary;
}

bytearray iodevice::readAll() const{
    return read(size());
}

uint64 iodevice::write(const char *data, uint64 maxsize){
    return _write(data, maxsize);
}

}
