#pragma once

#include "uri.h"
#include "library.h"

namespace hsm{

template<typename base_t>
class basic_ref : public library<base_t>::reader{
public:
    virtual base_t *basic_value() const = 0;

    const hsm::uri & uri() const{
        if(_entry != nullptr)
            return _entry->uri();
        return _uri;
    }

    typename library<base_t>::entry *entry() const{
        return _entry;
    }

protected:
    basic_ref(){
        //
    }

    basic_ref(const hsm::uri & uri) : _uri(uri){
        //
    }

    hsm::uri _uri;
    typename library<base_t>::entry *_entry;
};

template<typename data_t, typename base_t>
class ref : public basic_ref<base_t>{
public:
    ref(){
        this->_entry = nullptr;
        _ptr = nullptr;
    }

    /*ref(base_t *ptr){
        this->_entry = nullptr;
        _ptr = dynamic_cast<data_t*>(ptr);
    }*/

    ref(data_t *ptr){
        this->_entry = nullptr;
        _ptr = ptr;
    }

    ref(data_t *ptr, const hsm::uri & uri, library<data_t> & lib) : basic_ref<base_t>(uri){
        this->_entry = lib.set(this->_uri, (base_t*)ptr);
        _ptr = nullptr;

        if(this->_entry != nullptr){
            this->_entry->grab();
        }
    }

    ref(const hsm::uri & uri, library<base_t> & lib) : basic_ref<base_t>(uri){
        this->_entry = nullptr;
        _ptr = nullptr;

        resolve(lib);
    }

    ref(const ref<data_t, base_t> & r) : basic_ref<base_t>(r.uri()){
        _ptr = r._ptr;
        this->_entry = r.entry();
    }

    ref(const basic_ref<base_t> & r) : basic_ref<base_t>(r.uri()){
        _ptr = dynamic_cast<data_t*>(r.basic_value());
        this->_entry = r.entry();

        if(this->_entry != nullptr && dynamic_cast<data_t*>(this->_entry->value()) == nullptr){
            this->_entry = nullptr;
            this->_uri.clear();
        }
    }

    ~ref(){
        if(this->_entry != nullptr){
            this->_entry->release(this);
        }
    }

    base_t *basic_value() const{
        if(this->_entry != nullptr)
            return this->_entry->value();
        return (base_t*)_ptr;
    }

    data_t *value() const{
        if(this->_entry != nullptr)
            return (data_t*)this->_entry->value();
        return _ptr;
    }

    data_t & operator*() const{
        return *value();
	}

	data_t & operator*(){
        return *value();
	}

    data_t *operator->() const{
        return value();
	}

	data_t *operator->(){
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

    bool set_uri(const hsm::uri & uri){
        if(this->_entry == nullptr){
            return false;
        }
        if(this->_entry->lib().set_uri(this->_entry, uri)){
            this->_uri = uri;
            return true;
        }
        return false;
    }

    bool is_null() const{
        return this->_entry == nullptr && _ptr == nullptr;
    }

    bool resolved() const{
        return this->_entry != nullptr || this->_uri.empty();
    }

    bool resolve(library<data_t> & lib){
        if(!resolved()){
            this->_entry = lib.find(this->_uri);

            if(this->_entry != nullptr){
                if(dynamic_cast<data_t*>(this->_entry->value()) == nullptr){ // invalid type
                    this->_entry = nullptr;
                    return false;
                }else{
                    this->_entry->grab(this);
                    return true;
                }
            }

            return false;
        }

        return true;
    }

    void free(){
        if(this->_entry != nullptr){
            this->_entry->free();
        }else if(_ptr != nullptr){
            delete _ptr;
        }
    }

    void resource_freed(typename library<base_t>::entry *){
        _ptr = nullptr;
        this->_entry = nullptr;
        this->_uri.clear();
    }

    void resource_uri_changed(typename library<base_t>::entry *, const hsm::uri & new_uri){
        this->_uri = new_uri;
    }

private:
    data_t *_ptr;
};

}
