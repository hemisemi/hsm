#include "datastream.h"
#include "iodevice.h"
#include <cstring>

namespace hsm{

bool hostByteOrder(){
    union{
        uint32 i;
        char c[4];
    }bint = {0x01020304};
    return (bint.c[0] == 1) ? datastream::BigEndian : datastream::LittleEndian;
}

datastream::datastream(){
    _bo = BigEndian;
    _device = 0;
}

datastream::datastream(iodevice *device) : datastream(){
    setDevice(device);
}

datastream::ByteOrder datastream::byteOrder() const{
    return _bo;
}

void datastream::setByteOrder(ByteOrder bo){
    _bo = bo;
}

iodevice *datastream::device() const{
    return _device;
}

void datastream::setDevice(iodevice *device){
    _device = device;
}

datastream & datastream::readBytes(char *&s, uint & len){
    uint32 len32 = 0;
    if(_device && readRawData((char *)&len32, 4) == 4){
        len = len32;
        s = new char[len];
        //readRawData(s, len);
        _device->read(s, len);
    }
    return *this;
}

datastream & datastream::writeBytes(const char *s, uint len){
    if(_device){
        uint32 len32 = len;
        if(writeRawData((char *)&len32, 4) == 4)
            _device->write((const char *)s, len);
    }
    return *this;
}

int datastream::readRawData(char *s, int len){
    if(_device){
        char *data = new char[len];
        uint64 rl = _device->read(data, len);
        if(_bo != hostByteOrder()){
            for(uint i = 0; i < rl; ++i){
                s[i] = data[rl-1-i];
            }
        }else{
            memcpy(s, data, len);
        }
        delete[] data;
        return rl;
    }
    return 0;
}

int datastream::writeRawData(const char *s, int len){
    if(_device){
        char *bi = 0;
        if(_bo != hostByteOrder()){
            bi = new char[len];
            for(int i = 0; i < len; ++i){
                bi[i] = s[len-1-i];
            }
        }
        uint64 wl = _device->write(s, len);
        if(bi){
            delete[] bi;
        }
        return wl;
    }
    return 0;
}

bool datastream::atEnd() const{
    if(_device)
        return _device->atEnd();
    return false;
}

}


hsm::datastream & operator <<(hsm::datastream & stream, hsm::uint8 data){
    stream.writeRawData((const char *)&data, 1);
    return stream;
}

hsm::datastream & operator <<(hsm::datastream & stream, hsm::uint16 data){
    stream.writeRawData((const char *)&data, 2);
    return stream;
}

hsm::datastream & operator <<(hsm::datastream & stream, hsm::uint32 data){
    stream.writeRawData((const char *)&data, 4);
    return stream;
}

hsm::datastream & operator <<(hsm::datastream & stream, hsm::uint64 data){
    stream.writeRawData((const char *)&data, 8);
    return stream;
}

hsm::datastream & operator <<(hsm::datastream & stream, hsm::int8 data){
    stream.writeRawData((const char *)&data, 1);
    return stream;
}

hsm::datastream & operator <<(hsm::datastream & stream, hsm::int16 data){
    stream.writeRawData((const char *)&data, 2);
    return stream;
}

hsm::datastream & operator <<(hsm::datastream & stream, hsm::int32 data){
    stream.writeRawData((const char *)&data, 4);
    return stream;
}

hsm::datastream & operator <<(hsm::datastream & stream, hsm::int64 data){
    stream.writeRawData((const char *)&data, 8);
    return stream;
}

hsm::datastream & operator >>(hsm::datastream & stream, hsm::uint8 & data){
    stream.readRawData((char *)&data, 1);
    return stream;
}

hsm::datastream & operator >>(hsm::datastream & stream, hsm::uint16 & data){
    stream.readRawData((char *)&data, 2);
    return stream;
}

hsm::datastream & operator >>(hsm::datastream & stream, hsm::uint32 & data){
    stream.readRawData((char *)&data, 4);
    return stream;
}

hsm::datastream & operator >>(hsm::datastream & stream, hsm::uint64 & data){
    stream.readRawData((char *)&data, 8);
    return stream;
}

hsm::datastream & operator >>(hsm::datastream & stream, hsm::int8 & data){
    stream.readRawData((char *)&data, 1);
    return stream;
}

hsm::datastream & operator >>(hsm::datastream & stream, hsm::int16 & data){
    stream.readRawData((char *)&data, 2);
    return stream;
}

hsm::datastream & operator >>(hsm::datastream & stream, hsm::int32 & data){
    stream.readRawData((char *)&data, 4);
    return stream;
}

hsm::datastream & operator >>(hsm::datastream & stream, hsm::int64 & data){
    stream.readRawData((char *)&data, 8);
    return stream;
}
