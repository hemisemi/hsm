#include "file_default.h"
#include <iostream>

namespace hsm{

file_default::file_default(const hsm::file &file) : file_private(file){
    _size = -1;
}

bool file_default::exists() const{
    return exists(uri());
}

bool file_default::exists(const hsm::uri &uri){
    std::ifstream is(uri.toString().data());
    return is;
}

std::ios_base::openmode std_openmode(iodevice::OpenMode m){
    std::ios_base::openmode mode = (std::ios_base::openmode)0;
    if(m & iodevice::ReadOnly)
        mode |= std::ios_base::in;
    if(m & iodevice::WriteOnly)
        mode |= std::ios_base::out;
    if(m & iodevice::Append)
        mode |= std::ios_base::app;
    if(m & iodevice::Truncate)
        mode |= std::ios_base::trunc;
    if(!(m & iodevice::Text))
        mode |= std::ios_base::binary;
    return mode;
}

bool file_default::open(iodevice::OpenMode mode){
    if(mode == iodevice::NotOpen){
        close();
        return true;
    }
    if(file().isOpen()){
        std::cerr << "File already opened." << std::endl;
        return false;
    }
    _size = -1;
    _fs.open(uri().toString().data(), std_openmode(mode));
    return _fs.is_open();
}

void file_default::close(){
    if(file().isOpen()){
        _fs.close();
    }
}

int64 file_default::pos() const{
    if(file().isOpen()){
        if(file().isReadable()){
            return _fs.tellg();
        }
        if(file().isWritable()){
            return _fs.tellp();
        }
    }
    return 0;
}

bool file_default::seek(int64 pos){
    if(file().isOpen()){
        if(file().isReadable()){
            _fs.seekg(pos);
            return (_fs.rdstate() & std::fstream::goodbit);
        }
        if(file().isWritable()){
            _fs.seekp(pos);
            return (_fs.rdstate() & std::fstream::goodbit);
        }
    }
    return false;
}

uint64 file_default::read(char *data, uint64 maxsize) const{
    if(file().isReadable()){
        uint64 size = _fs.readsome(data, maxsize);
        return size;
    }else
        std::cerr << "File not opened for reading" << std::endl;
    return 0;
}

uint64 file_default::write(const char *data, uint64 maxsize){
    if(file().isWritable()){
        _size = -1;
        _fs.write(data, maxsize);
        return maxsize;
    }else
        std::cerr << "File not opened for writing" << std::endl;
    return 0;
}

int64 file_default::size() const{
    if(!file().isOpen())
        return 0;
    if(_size < 0){
        std::ifstream in(uri().toString().data(), std::ifstream::in | std::ifstream::binary);
        in.seekg(0, std::ifstream::end);
        _size = (int64)in.tellg();
    }
    return _size;
}

}
