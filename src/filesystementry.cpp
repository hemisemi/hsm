#include "filesystementry.h"
#include "algorithm.h"

namespace hsm{

fsentry::fsentry(){
    //
}

fsentry::fsentry(const hsm::uri &uri){
    _uri = uri;
}

fsentry::fsentry(const std::string &uri){
    _uri = hsm::uri(uri);
}

const uri & fsentry::uri() const{
    return _uri;
}

std::string fsentry::baseName() const{
    return section(_uri.path().back(), '.', 0, 0);
}

std::string fsentry::completeBaseName() const{
    return section(_uri.path().back(), '.', 0, -2);
}

std::string fsentry::suffixe() const{
    return section(_uri.path().back(), '.', -1, -1);
}

std::string fsentry::completeSuffixe() const{
    return section(_uri.path().back(), '.', 1, -1);
}

void fsentry::setUri(const hsm::uri &uri){
    _uri = uri;
}

void fsentry::setFilename(const std::string &filename){
    setUri(hsm::uri(filename));
}

std::string fsentry::filename() const{
    return _uri.toString();
}

bool fsentry::isAbsolute() const{
    return _uri.isAbsolute();
}

std::string fsentry::absolutePath() const{
    return _uri.absolute(hsm::uri("")).toString();
    //return _uri.absolute(app->uri()).toString();
}

}
