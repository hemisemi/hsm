#pragma once

#include "uri.h"
#include "library.h"

namespace hsm{

template<class data_t>
class ref : public library::reader<data_t>{
public:
    ref(){
        _entry = nullptr;
        _ptr = nullptr;
    }

    ref(data_t *ptr){
        _entry = nullptr;
        _ptr = ptr;
    }

    ref(data_t *ptr, const hsm::uri & uri, library<data_t> & lib) : _uri(uri){
        _entry = lib.set(_uri, ptr);
        _ptr = nullptr;

        if(_entry != nullptr){
            _entry->grab();
        }
    }

    ref(const hsm::uri & uri, library<data_t> & lib) : _uri(uri){
        _entry = lib.find(_uri);
        _ptr = nullptr;

        if(_entry != nullptr){
            _entry->grab();
        }
    }

    ~ref(){
        if(_entry != nullptr){
            _entry->release();
        }
    }

    bool set_uri(const hsm::uri & uri){
        if(_entry == nullptr){
            return false;
        }
        if(_entry->set_uri(uri)){
            _uri = uri;
            return true;
        }
        return false;
    }

    const hsm::uri & uri() const{
        if(_entry != nullptr)
            return _entry->uri();
        return _uri;
    }

    bool is_null() const{
        return _entry == nullptr && _ptr == nullptr;
    }

    bool resolved() const{
        return _entry != nullptr || _uri->empty();
    }

    bool resolve(library<data_t> & lib){
        if(!resolved()){
            _entry = lib.find(_uri);

            if(_entry != nullptr){
                _entry->grab();
                return true;
            }

            return false;
        }

        return true;
    }

    void free(){
        if(_entry != nullptr){
            _entry->free();
        }else if(_ptr != nullptr){
            delete _ptr;
        }
    }

    void resource_freed(library<data_t>::entry *){
        _ptr = nullptr;
        _entry = nullptr;
        _uri->clear();
    }

    void resource_uri_changed(library<data_t>::entry *, const hsm::uri & new_uri){
        _uri = new_uri;
    }

private:
    hsm::uri *_uri;
    data_t *_ptr;

    library::entry *_entry;
};

}
