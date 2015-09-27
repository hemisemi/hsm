#ifndef SWAPI_IODEVICE_H
#define SWAPI_IODEVICE_H

#include "types.h"
#include "bytearray.h"

namespace hsm{

class iodevice{
public:
    enum OpenMode{
        NotOpen = 0x0000,
        ReadOnly = 0x0001,
        WriteOnly = 0x0002,
        ReadWrite = ReadOnly | WriteOnly,
        Append = 0x0004,
        Truncate = 0x0008,
        Text = 0x0010
    };

    iodevice();

    virtual bool open(OpenMode mode);
    virtual void close() = 0;

    OpenMode openMode() const;

    virtual int64 pos() const = 0;

    bool isNull() const;
    bool isOpen() const;
    bool isReadable() const;
    bool isWritable() const;

    virtual bool seek(int64 pos) = 0;

    virtual bool atEnd() const;

    uint64 read(char *data, uint64 maxsize) const;
    bytearray read(uint64 maxsize) const;
    bytearray readAll() const;

    uint64 write(const char *data, uint64 maxsize);

    virtual int64 size() const = 0;

private:
    OpenMode _mode;

protected:
    virtual uint64 _read(char *data, uint64 maxsize) const = 0;
    virtual uint64 _write(const char *data, uint64 maxsize) = 0;
};

}

#endif // SWAPI_IODEVICE_H
