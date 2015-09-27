#include "uri.h"
#include "algorithm.h"

namespace hsm{

uri::uri(ReadMode rm){
    _rm = rm;
    _absolute_path = false;
}

uri::uri(const std::string & uri){
    _rm = Normal;
    setUri(uri);
}

uri::uri(const std::string & uri, ReadMode rm){
    _rm = rm;
    setUri(uri);
}

uri::uri(const hsm::uri &uri){
    _rm = uri._rm;
    _sheme = uri._sheme;
    _authority = uri._authority;
    _path = uri._path;
    _query = uri._query;
    _fragment = uri._fragment;
    _absolute_path = uri._absolute_path;
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

const std::list<std::string> & uri::query() const{
    return _query;
}

const std::string & uri::fragment() const{
    return _fragment;
}

std::string uri::inspect() const{
    return "("+sheme()+")("+authority()+")("+join(path(), '/')+")("+join(query(), '&')+")("+fragment()+")";
}

bool uri::isAbsolute() const{
    return _absolute_path;
}

void uri::makeAbsolute(const uri &position){
    if(!isAbsolute())
        setPath(position.path()+_path);
}

uri uri::absolute(const uri &position) const{
    if(isAbsolute())
        return *this;
    uri copy(*this);
    copy.makeAbsolute(position);
    return copy;
}

void uri::clear(){
    _sheme.clear();
    _authority.clear();
    _path.clear();
    _query.clear();
    _fragment.clear();
    _absolute_path = false;
}

void uri::setSheme(const std::string &sheme){
    _sheme = sheme;
}

void uri::setAuthority(const std::string &authority){
    _authority = authority;
}

void uri::setPath(const std::list<std::string> &path){
    _path = path;
    _absolute_path = (!_path.empty() && _path.front().empty());
}

void uri::setPath(const std::string &path){
    _path = split(path, '/');
    _absolute_path = (!_path.empty() && _path.front().empty());
}

void uri::setQuery(const std::string &query){
    if(!query.empty())
        _query = split(query, '&');
    else
        _query.clear();
}

void uri::setFragment(const std::string &fragment){
    if(!fragment.empty())
        _fragment = fragment;
    else
        _fragment.clear();
}

std::string uri::toString() const{
    std::string str = "";
    if(!_sheme.empty())
        str += _sheme+':';
    if(!_authority.empty())
        str = str+"//"+_authority+"/";
    if(!_path.empty())
        str += join(_path, '/');
    if(!_query.empty())
        str = str+'?'+join(_query, '&');
    if(!_fragment.empty())
        str = str+"#"+_fragment;
    return str;
}

static std::string findSheme(std::string & uri){
    std::string sheme = "";
    int index = 0;
    if((index = indexOf(uri, ':')) >= 0){
        std::string tmp = section(uri, 0, index);
        bool ok = true;
        std::string::iterator it = tmp.begin();
        while(ok && it != tmp.end()){
            char c = *it;
            if(it == tmp.begin()){
                ok = isalpha(c);
            }else{
                ok = (isalpha(c) || isdigit(c) || c == '+' || c == '-' || c == '.');
            }
            ++it;
        }
        if(ok){
            sheme = tmp;
            uri.erase(0, tmp.size()+1);
            tmp.clear();
        }
    }
    return sheme;
}

static std::string findAuthority(std::string & uri){
    std::string authority = "";
    if(indexOf(uri, "//") == 0){
        uri.erase(0, 2);
        std::string::iterator it = uri.begin();
        while(it != uri.end() && *it != '/' && *it != '#' && *it != '?'){
            authority += *it;
            ++it;
        }
        uri.erase(0, authority.size()+1);
    }
    return authority;
}

static std::string findFragment(std::string & uri, char _c_){
    std::string fragment;
    if(!uri.empty()){
        std::string::iterator it = uri.end();
        int index = uri.size();
        do{
            --it;
            char c = *it;
            if(c == _c_){
                fragment = section(uri, index, uri.size()-index);
                --index;
                uri.erase(index, uri.size()-index);
                break;
            }
            --index;
        }while(it != uri.begin());
    }
    return fragment;
}

void uri::setUri(std::string uri){
    if(_rm & Sheme)
        setSheme(findSheme(uri));
    if(_rm & Authority)
        setAuthority(findAuthority(uri));
    if(_rm & Fragment)
        setFragment(findFragment(uri, '#'));
    if(_rm & Query)
        setQuery(findFragment(uri, '?'));
    setPath(uri);
}

bool uri::operator ==(const std::string & str) const{
    return toString() == str;
}

bool uri::operator ==(const hsm::uri & uri) const{
    return (_absolute_path == uri._absolute_path
            && _authority == uri._authority
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

bool uri::cdUp(){
    if(_path.empty())
        return false;
    _path.pop_back();
    return true;
}

bool uri::cd(const std::string &name){
    if(name == ".")
        return true;
    if(name == ".."){
        return cdUp();
    }
    _path.push_back(name);
    return true;
}

bool uri::isRoot() const{
    return _path.empty();
}

}
