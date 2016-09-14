#pragma once

#include <map>
#include <set>
#include "uri.h"

namespace hsm{

template<typename data_t>
class library{
public:
    library();

    class entry;

    class reader{
    public:
        virtual void resource_freed(entry *e) = 0;

        virtual void resource_uri_changed(entry *e, const hsm::uri & new_uri) = 0;
    };

    class entry{
    public:
        entry(library<data_t> & lib, const hsm::uri & uri, data_t *ptr) : _lib(lib), _uri(uri){
            _ptr = ptr;
            _ref_count = 0;
        }

        ~entry(){
			for(reader *r : _readers)
				r->resource_freed(this);
        }

        void free(){
            delete _ptr;
        }

        void grab(reader *g = nullptr){
            if(g != nullptr)
                _readers.insert(g);
            ++_ref_count;
        }

        void release(reader *g = nullptr){
            if(_ref_count > 0){
                --_ref_count;
                if(g != nullptr)
                    _readers.erase(g);
                if(_ref_count == 0)
                    _lib.remove(this);
            }
        }

        size_t ref_count() const{
            return _ref_count;
        }

        hsm::uri & uri() const{
            return _uri;
        }

		/*bool set_uri(const hsm::uri & uri){
            if(_lib.change_uri(this, uri)){
                _uri = uri;
                return true;
            }
            return false;
		}*/

		void set_uri(const hsm::uri & uri){
			for(reader *r : _readers)
				r->resource_uri_changed(this, uri);
			_uri = uri;
		}

        data_t *value() const{
            return _ptr;
        }

        const library<data_t> & lib() const{
            return _lib;
        }

		library<data_t> & lib(){
			return _lib;
		}

    private:
        library<data_t> & _lib;
        hsm::uri _uri;
        data_t *_ptr;
        size_t _ref_count;

        std::set<reader *> _readers;
    };

	bool set_uri(entry *e, const hsm::uri & new_uri){
        if(e != nullptr){
            if(new_uri.empty()){
                return remove(e);
            }

            auto it1 = _map.find(e->uri());
            if(it1 != _map.end()){
                if(it1->second != e)
                    return false;
            }

            auto it2 = _map.find(new_uri);
            if(it2 != _map.end())
                return false;

            _map.erase(it1);

			e->set_uri(new_uri);
            _map.insert(std::make_pair(new_uri, e));
            return true;
        }

        return false;
    }

    entry *set(const hsm::uri & uri, data_t *value, data_t **previous_value = nullptr){
        entry *new_entry = new entry(*this, uri, value);

        auto it = _map.find(uri);
        if(it == _map.end()){
            _map.insert(it, std::make_pair(uri, new_entry));
            return nullptr;
        }else{
            entry *previous = it->second;
            if(previous_value != nullptr)
                *previous_value = previous->value();
			previous->set_uri(hsm::uri());
            _map.insert(std::make_pair(uri, new_entry));
        }

        return new_entry;
    }

    data_t *find(const hsm::uri & uri) const{
        //
    }

    bool remove(entry *e){
        if(e != nullptr){
            auto it = _map.find(e->uri());
            if(it != _map.end()){
                _map.erase(e->uri());
                e->set_uri(hsm::uri());

                return true;
            }
        }

        return false;
    }

    bool contains(const hsm::uri & uri) const;

    bool resolve_all(){
		// TODO
		return true;
    }

private:
    std::map<hsm::uri, entry*> _map;
};

}
