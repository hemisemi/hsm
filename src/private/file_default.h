#ifndef FILE_DEFAULT_H
#define FILE_DEFAULT_H

#include "file_private.h"

namespace hsm{

class file_default : public file_private{
public:
    file_default(const hsm::file & file);

    virtual bool exists() const;
    static bool exists(const hsm::uri & uri);

    virtual bool open(iodevice::OpenMode mode);
    virtual void close();

    virtual int64 pos() const;
    virtual bool seek(int64 pos);

    virtual int64 size() const;

    virtual uint64 read(char *data, uint64 maxsize) const;
    virtual uint64 write(const char *data, uint64 maxsize);

private:
    mutable std::fstream _fs;
    mutable int64 _size;
};

}

#endif // FILE_DEFAULT_H
