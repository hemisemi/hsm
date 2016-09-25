#pragma once

#include <unordered_map>
#include <unordered_set>
#include "uri.h"

namespace hsm{

template<typename data_t>
class library{
public:
	library(){
		//
	}

    class entry;

    class reader{
    public:
        virtual ~reader(){
            //
        }

        virtual void resource_freed(entry *e){
            //
        }
    };

    class entry{
    public:
        entry(data_t *v){
            _value = nullptr;
            set_value(v);
        }

        ~entry(){
            for(reader *r : _readers)
                r->resource_freed(this);
        }

        data_t *value() const{
            return _value;
        }

        void set_value(data_t *v){
            _value = v;
            update();
        }

        void grab(reader *r){
            _readers.insert(r);
        }

        void release(reader *r){
            _readers.erase(r);
            update();
        }

        void update(){
            if(_value == nullptr && _readers.empty())
                delete this;
        }

    private:
        data_t *_value;
        size_t _ref_count;
        std::unordered_set<reader *> _readers;
    };

    virtual entry *get_entry(const hsm::uri & uri) const = 0;
};

}
