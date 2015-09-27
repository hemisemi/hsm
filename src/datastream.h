#ifndef DATASTREAM_H
#define DATASTREAM_H

#include "types.h"

namespace hsm{

class iodevice;

class datastream{
public:
    enum ByteOrder{
        BigEndian,
        LittleEndian
    };

    datastream();
    datastream(iodevice *device);

    ByteOrder byteOrder() const;
    void setByteOrder(ByteOrder bo);

    datastream & readBytes(char *&s, uint & len);
    int readRawData(char *s, int len);

    datastream & writeBytes(const char *s, uint len);
    int writeRawData(const char *s, int len);

    iodevice *device() const;
    void setDevice(iodevice *);

    bool atEnd() const;

private:
    ByteOrder _bo;
    iodevice *_device;
};

}

hsm::datastream & operator<<(hsm::datastream &, hsm::uint8);
hsm::datastream & operator<<(hsm::datastream &, hsm::uint16);
hsm::datastream & operator<<(hsm::datastream &, hsm::uint32);
hsm::datastream & operator<<(hsm::datastream &, hsm::uint64);
hsm::datastream & operator<<(hsm::datastream &, hsm::int8);
hsm::datastream & operator<<(hsm::datastream &, hsm::int16);
hsm::datastream & operator<<(hsm::datastream &, hsm::int32);
hsm::datastream & operator<<(hsm::datastream &, hsm::int64);
hsm::datastream & operator>>(hsm::datastream &, hsm::uint8 &);
hsm::datastream & operator>>(hsm::datastream &, hsm::uint16 &);
hsm::datastream & operator>>(hsm::datastream &, hsm::uint32 &);
hsm::datastream & operator>>(hsm::datastream &, hsm::uint64 &);
hsm::datastream & operator>>(hsm::datastream &, hsm::int8 &);
hsm::datastream & operator>>(hsm::datastream &, hsm::int16 &);
hsm::datastream & operator>>(hsm::datastream &, hsm::int32 &);
hsm::datastream & operator>>(hsm::datastream &, hsm::int64 &);

#endif // DATASTREAM_H
