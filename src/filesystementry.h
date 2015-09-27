#ifndef SWAPI_FILESYSTEMENTRY_H
#define SWAPI_FILESYSTEMENTRY_H

#include "uri.h"
#include "string.h"

namespace hsm{

class fsentry{
public:
    fsentry();
    fsentry(const std::string & uri);
    fsentry(const hsm::uri & uri);

    virtual void setUri(const hsm::uri & uri);
    const hsm::uri &uri() const;
    void setFilename(const std::string &filename);
    std::string filename() const;

    std::string baseName() const;
    std::string completeBaseName() const;
    std::string suffixe() const;
    std::string completeSuffixe() const;

    bool isAbsolute() const;
    std::string absolutePath() const;

    virtual bool isDirectory() const = 0;
    virtual bool isFile() const = 0;

private:
    hsm::uri _uri;
};

}

#endif // FILESYSTEMENTRY_H
