#pragma once

#include "uri.h"
#include "library.h"

namespace hsm{

template<typename base_t>
class basic_ref : public library<base_t>::reader{
public:
    ~basic_ref(){
        if(_entry != nullptr)
            _entry->release(this);
    }

    virtual base_t *basic_value() const{
        if(_entry != nullptr)
            return _entry->value();
        return nullptr;
    }

    virtual void free(){
        if(_entry != nullptr){
            _entry->release(this);
            delete _entry;
            _entry = nullptr;
        }
    }

    void resource_freed(typename library<base_t>::entry *){
        this->_entry = nullptr;
    }

protected:
    basic_ref(){
        _entry = nullptr;
    }

    basic_ref(const hsm::uri & uri, library<base_t> & lib){
        _entry = lib.get_entry(uri);
        if(_entry != nullptr)
            _entry->grab(this);
    }

    basic_ref(const basic_ref<base_t> & r){
        _entry = r._entry;
        if(_entry != nullptr)
            _entry->grab(this);
    }

    typename library<base_t>::entry *_entry;
};

template<typename data_t, typename base_t>
class ref : public basic_ref<base_t>{
public:
    ref(){
        _ptr = nullptr;
    }

    ref(data_t *ptr){
        _ptr = ptr;
    }

    ref(const hsm::uri & uri, library<base_t> & lib) : basic_ref<base_t>(uri){
        _ptr = nullptr;
    }

    ref(const ref<data_t, base_t> & r) : basic_ref<base_t>(r){
        _ptr = r._ptr;
    }

    ref(const basic_ref<base_t> & r) : basic_ref<base_t>(r){
        _ptr = dynamic_cast<data_t*>(r.basic_value());

        if(this->_entry != nullptr && dynamic_cast<data_t*>(this->_entry->value()) == nullptr){
            this->_entry->release(this);
            this->_entry = nullptr;
        }
    }

    ~ref(){
        //
    }

    base_t *basic_value() const{
        if(_ptr != nullptr)
            return (base_t*)_ptr;
        return basic_ref<base_t>::basic_value();
    }

    data_t *value() const{
        if(this->_entry != nullptr)
            return (data_t*)this->_entry->value();
        return _ptr;
    }

    data_t & operator*() const{
        return *value();
	}

    data_t *operator->() const{
        return value();
	}

    operator data_t*() const{
        return value();
	}

    bool operator==(data_t *ptr) const{
        return value() == ptr;
    }

    bool operator==(const basic_ref<base_t> & r) const{
        return basic_value() == r.basic_value();
    }

    bool operator!=(data_t *ptr) const{
        return value() != ptr;
    }

    bool operator!=(const basic_ref<base_t> & r) const{
        return basic_value() != r.basic_value();
    }

    operator bool() const{
        return !is_null();
    }

    bool is_null() const{
        return value() == nullptr;
    }

    void free(){
        if(_ptr != nullptr){
            delete _ptr;
        }
        basic_ref<base_t>::free();
    }

private:
    data_t *_ptr;
};

}
