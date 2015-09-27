#include "file.h"
#include "private/file_private.h"

namespace hsm{

file::file(){
    p = 0;
}

file::~file(){
    if(p)
        delete p;
}

file::file(const std::string &filename) : file(){
    setFilename(filename);
}

file::file(const hsm::uri &uri) : file(){
    setUri(uri);
}

void file::setUri(const hsm::uri &uri){
    if(uri != this->uri()){
        close();
        fsentry::setUri(uri);
        if(p)
            delete p;
        p = file_private::instance(*this);
    }
}

bool file::isNull() const{
    return p;
}

bool file::exists() const{
    return (p && p->exists());
}

bool file::exists(const std::string &filename){
    return file_private::exists(filename);
}

bool file::open(iodevice::OpenMode mode){
    bool ok = (p && p->open(mode));
    iodevice::open(ok ? mode : iodevice::NotOpen);
    return ok;
}

void file::close(){
    if(p)
        p->close();
}

int64 file::pos() const{
    return (p ? p->pos() : 0);
}

bool file::seek(int64 pos){
    return (p && p->seek(pos));
}

uint64 file::_read(char *data, uint64 maxsize) const{
    return (p ? p->read(data, maxsize) : 0);
}

uint64 file::_write(const char *data, uint64 maxsize){
    return (p ? p->write(data, maxsize) : 0);
}

int64 file::size() const{
    return (p ? p->size() : 0);
}

bool file::isFile() const{
    return true;
}

bool file::isDirectory() const{
    return false;
}

}
