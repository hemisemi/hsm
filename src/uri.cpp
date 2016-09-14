#include "uri.h"
#include "algorithm.h"

namespace hsm{

uri::uri(){
    //
}

uri::uri(const char *str){
    set(std::string(str));
}

uri::uri(const char *str, size_t len){
    set(std::string(str, len));
}

uri::uri(const std::string & uri){
    set(uri);
}

uri::uri(const hsm::uri &uri){
    _sheme = uri._sheme;
    _authority = uri._authority;
    _path = uri._path;
    _query = uri._query;
    _fragment = uri._fragment;
}

const std::string & uri::sheme() const{
    return _sheme;
}

const std::string & uri::authority() const{
    return _authority;
}

const std::list<std::string> & uri::path() const{
    return _path;
}

std::string uri::path_string() const{
    return join(path(), '/');
}

const std::list<std::string> & uri::query() const{
    return _query;
}

std::string uri::query_string() const{
    return join(query(), '&');
}

const std::string & uri::fragment() const{
    return _fragment;
}

std::string uri::inspect() const{
    return "("+sheme()+")("+authority()+")("+path_string()+")("+query_string()+")("+fragment()+")";
}

bool uri::empty() const{
    return _sheme.empty() && _authority.empty() && _path.empty() && _query.empty() && _fragment.empty();
}

bool uri::is_absolute() const{
    return (_path.empty() || _path.front().empty());
}

void uri::make_absolute(const uri &position){
    if(!is_absolute())
        set_path(position.path()+_path);
}

uri uri::absolute(const uri &position) const{
    if(is_absolute())
        return *this;
    uri copy(*this);
    copy.make_absolute(position);
    return copy;
}

void uri::clear(){
    _sheme.clear();
    _authority.clear();
    _path.clear();
    _query.clear();
    _fragment.clear();
}

void uri::set_sheme(const std::string &sheme){
    _sheme = sheme;
}

void uri::set_authority(const std::string &authority){
    _authority = authority;
}

void uri::set_path(const std::list<std::string> &path){
    _path = path;
}

void uri::set_path(const std::string &path){
    _path = split(path, '/');
}

void uri::set_query(const std::string &query){
    if(!query.empty())
        _query = split(query, '&');
    else
        _query.clear();
}

void uri::set_fragment(const std::string &fragment){
    if(!fragment.empty())
        _fragment = fragment;
    else
        _fragment.clear();
}

std::string uri::to_string() const{
    std::string str = "";
    if(!_sheme.empty())
        str += _sheme+':';
    if(!_authority.empty())
        str = str+"//"+_authority+"/";
    if(!_path.empty())
        str += path_string();
    if(!_query.empty())
        str = str+'?'+query_string();
    if(!_fragment.empty())
        str = str+"#"+_fragment;
    return str;
}

bool uri::set(std::string uri){
    _valid = true;

    enum state_id{
        sheme,
        authority,
        path,
        query,
        fragment
    }state = sheme;

    std::string tmp;
    _sheme.clear();
    _authority.clear();
    _path.clear();
    _query.clear();
    _fragment.clear();

    for(size_t i = 0; i < uri.size(); ++i){
        char c = uri[i];
        switch(state){
        case sheme:
            switch(c){
            case ':':
                set_sheme(tmp);
                tmp.clear();
                if(i+2 < uri.size() && uri[i+1] == '/' && uri[i+2] == '/'){
                    i += 2;
                    state = authority;
                }else{
                    state = path;
                }
                break;
            case '/':
                if(i+1 < uri.size() && uri[i+1] == '/'){
                    if(tmp.empty()){
                        ++i;
                        state = authority;
                    }else{
                        _path.push_back(tmp);
                        state = path;
                    }
                }else{
                    _path.push_back(tmp);
                    state = path;
                }
                tmp.clear();
                break;
            case '?':
                _path.push_back(tmp);
                tmp.clear();
                state = query;
            case '#':
                _path.push_back(tmp);
                tmp.clear();
                state = fragment;
            default:
                tmp.push_back(c);
            }
            break;
        case authority:
            if(c == '/'){
                set_authority(tmp);
                tmp.clear();
                _path.push_back(tmp);
                state = path;
            }else{
                tmp.push_back(c);
            }
            break;
        case path:
            switch(c){
            case '/':
                if(!tmp.empty())
                    _path.push_back(tmp);
                tmp.clear();
                break;
            case '?':
                if(!tmp.empty())
                    _path.push_back(tmp);
                tmp.clear();
                state = query;
                break;
            case '#':
                if(!tmp.empty())
                    _path.push_back(tmp);
                tmp.clear();
                state = fragment;
                break;
            default:
                tmp.push_back(c);
                break;
            }
            break;
        case query:
            switch(c){
            case '&':
                if(!tmp.empty())
                    _query.push_back(tmp);
                tmp.clear();
                break;
            case '#':
                if(!tmp.empty())
                    _query.push_back(tmp);
                tmp.clear();
                state = fragment;
                break;
            default:
                tmp.push_back(c);
                break;
            }
            break;
        case fragment:
            tmp.push_back(c);
            break;
        }
    }

    if(!tmp.empty()){
        switch(state){
        case sheme:
            _path.push_back(tmp);
            break;
        case authority:
            goto malformed_uri;
        case path:
            _path.push_back(tmp);
            break;
        case query:
            _query.push_back(tmp);
            break;
        case fragment:
            _fragment = tmp;
            break;
        }
    }

    return true;

malformed_uri:
    _valid = false;
    return false;
}

uri & uri::operator=(const hsm::uri & uri){
    _sheme = uri._sheme;
    _authority = uri._authority;
    _path = uri._path;
    _query = uri._query;
    _fragment = uri._fragment;

    return *this;
}

bool uri::operator ==(const std::string & str) const{
    return to_string() == str;
}

bool uri::operator ==(const hsm::uri & uri) const{
    return (_authority == uri._authority
            && _fragment == uri._fragment
            && _path == uri._path
            && _query == uri._query
            && _sheme == uri._sheme);
}

bool uri::operator !=(const std::string & str) const{
    return !operator ==(str);
}

bool uri::operator !=(const hsm::uri & uri) const{
    return !operator ==(uri);
}

uri uri::operator +(const hsm::uri & uri) const{
    hsm::uri r(*this);
    r._path = r._path+uri._path;
    return r;
}

bool uri::cd_up(){
    if(_path.empty())
        return false;
    _path.pop_back();
    return true;
}

bool uri::cd(const std::string &name){
    if(name == ".")
        return true;
    if(name == ".."){
        return cd_up();
    }
    _path.push_back(name);
    return true;
}

bool uri::is_root() const{
    return _path.empty();
}

std::ostream & operator<<(std::ostream & out, const hsm::uri & uri){
    return out << uri.to_string();
}

}
