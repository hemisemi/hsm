#ifndef FILE_H
#define FILE_H

#include <fstream>
#include "string.h"
#include "iodevice.h"
#include "uri.h"
#include "filesystementry.h"

namespace hsm{

class file_private;

class file : public iodevice, public fsentry{
public:
    file();
    ~file();
    file(const std::string &filename);
    file(const hsm::uri &uri);

    virtual void setUri(const hsm::uri &uri);

    bool isNull() const;
    bool exists() const;
    static bool exists(const std::string & filename);

    bool open(iodevice::OpenMode mode);
    void close();

    int64 pos() const;
    bool seek(int64 pos);

    int64 size() const;

    bool isFile() const;
    bool isDirectory() const;

private:
    file_private *p;

protected:
    uint64 _read(char *data, uint64 maxsize) const;
    uint64 _write(const char *data, uint64 maxsize);
};

}

#endif // FILE_H
