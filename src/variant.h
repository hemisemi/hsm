#pragma once

#include <stddef.h>
#include <string>

namespace hsm{

class variant{
public:
    enum type{
        type_null,

        type_bool,

        type_char,
        type_uchar,

        type_int,
        type_uint,
        type_long,
        type_ulong,
        type_longlong,
        type_ulonglong,

        type_float,
        type_double,

        //type_string,

        type_data
    };

    variant();
    variant(const variant & v);

    variant(bool val);
    variant(char val);
    variant(unsigned char val);
    variant(int val);
    variant(unsigned int val);
    variant(long val);
    variant(unsigned long val);
    variant(long long val);
    variant(unsigned long long val);

    variant(float val);
    variant(double val);

    variant(void *data);

    template<class T>
    variant(T *ptr){
        _data = ptr;
        _len = 0;
        _type = type_data;
    }

    ~variant();

    variant & operator=(const variant & v);

    template<class T>
    const T & value() const{
        return *(const T*)_data;
    }

    template<class T>
    T & value(){
        return *(T*)_data;
    }

    bool is_null() const;

private:
    void *_data;
    size_t _len;

    type _type;
};

}
