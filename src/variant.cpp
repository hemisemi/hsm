#include "variant.h"
#include <cstring>

namespace hsm{

variant::variant(){
    _data = nullptr;
    _type = type_null;
}

variant::variant(const variant &v){
    _type = v._type;
    _data = nullptr;
    _len = 0;
    if(_type != type_null){
        if(_type == type_data){
            _data = v._data;
        }else{
            _len = v._len;
            _data = malloc(_len);
            std::memcpy(_data, v._data, _len);
        }
    }
}

variant::variant(bool val){
    _data = std::malloc(_len = sizeof(bool));
    std::memcpy(_data, &val, _len);
    _type = type_bool;
}

variant::variant(char val){
    _data = std::malloc(_len = sizeof(char));
    std::memcpy(_data, &val, sizeof(char));
    _type = type_char;
}

variant::variant(unsigned char val){
    _data = std::malloc(_len = sizeof(unsigned char));
    std::memcpy(_data, &val, sizeof(unsigned char));
    _type = type_uchar;
}

variant::variant(int val){
    _data = std::malloc(_len = sizeof(int));
    std::memcpy(_data, &val, sizeof(int));
    _type = type_int;
}

variant::variant(unsigned int val){
    _data = std::malloc(_len = sizeof(unsigned int));
    std::memcpy(_data, &val, sizeof(unsigned int));
    _type = type_uint;
}

variant::variant(long val){
    _data = std::malloc(_len = sizeof(long));
    std::memcpy(_data, &val, sizeof(long));
    _type = type_long;
}

variant::variant(unsigned long val){
    _data = std::malloc(_len = sizeof(unsigned long));
    std::memcpy(_data, &val, sizeof(unsigned long));
    _type = type_ulong;
}

variant::variant(long long val){
    _data = std::malloc(_len = sizeof(long long));
    std::memcpy(_data, &val, sizeof(long long));
    _type = type_longlong;
}

variant::variant(unsigned long long val){
    _data = std::malloc(_len = sizeof(unsigned long long));
    std::memcpy(_data, &val, sizeof(unsigned long long));
    _type = type_ulonglong;
}

variant::variant(float val){
    _data = std::malloc(_len = sizeof(float));
    std::memcpy(_data, &val, sizeof(float));
    _type = type_float;
}

variant::variant(double val){
    _data = std::malloc(_len = sizeof(double));
    std::memcpy(_data, &val, sizeof(double));
    _type = type_double;
}

variant::variant(void *data){
    _data = data;
    _type = type_data;
    _len = 0;
}

variant::~variant(){
    if(_type != type_data && _data != nullptr)
        std::free(_data);
}

variant & variant::operator =(const variant & v){
    if(_type != type_data && _data != nullptr)
        std::free(_data);

    _type = v._type;
    _data = nullptr;
    _len = 0;
    if(_type != type_null){
        if(_type == type_data){
            _data = v._data;
        }else{
            _len = v._len;
            _data = malloc(_len);
            std::memcpy(_data, v._data, _len);
        }
    }

    return *this;
}

bool variant::is_null() const{
    return _type == type_null;
}

}
