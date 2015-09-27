#ifndef FILE_PRIVATE_H
#define FILE_PRIVATE_H

#include "../iodevice.h"
#include "../file.h"

namespace hsm{

class file_private{
public:
    file_private(const hsm::file & file);
    virtual ~file_private();

    static file_private *instance(const hsm::file & file);
    static bool exists(const hsm::uri & uri);
    const hsm::file & file() const;
    const hsm::uri & uri() const;

    virtual bool exists() const = 0;

    virtual bool open(iodevice::OpenMode mode) = 0;
    virtual void close() = 0;

    virtual int64 pos() const = 0;
    virtual bool seek(int64 pos) = 0;

    virtual int64 size() const = 0;

    virtual uint64 read(char *data, uint64 maxsize) const = 0;
    virtual uint64 write(const char *data, uint64 maxsize) = 0;

private:
    const hsm::file & _file;
};

}

#endif // FILE_PRIVATE_H
