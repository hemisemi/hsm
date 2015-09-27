#include "file_private.h"
#include "file_default.h"

namespace hsm{

file_private::file_private(const hsm::file &file) : _file(file){
    //
}

file_private::~file_private(){
    //
}

file_private *file_private::instance(const hsm::file &file){
    if(file.isNull())
        return 0;
    const std::string & sheme = file.uri().sheme();
    if(sheme.empty() || sheme == "file")
        return new file_default(file);
    return 0;
}

bool file_private::exists(const hsm::uri &uri){
    const std::string & sheme = uri.sheme();
    if(sheme.empty() || sheme == "file")
        return file_default::exists(uri);
    return false;
}

const file & file_private::file() const{
    return _file;
}

const uri & file_private::uri() const{
    return _file.uri();
}

}
