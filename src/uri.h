#pragma once

#include <string>
#include <list>
#include <ostream>

namespace hsm{

class uri{
public:
    uri();
    uri(const char* str);
    uri(const char* str, size_t len);
    uri(const std::string & uri);
    uri(const uri & uri);

    bool set(std::string uri);
    void clear();

    const std::string & sheme() const;
    const std::string & authority() const;
    const std::list<std::string> & path() const;
    std::string path_string() const;
    const std::list<std::string> &  query() const;
    std::string query_string() const;
    const std::string & fragment() const;

    std::string inspect() const;

    bool empty() const;
    bool is_absolute() const;
    void make_absolute(const uri & position);
    uri absolute(const uri & position) const;

    void set_sheme(const std::string & sheme);
    void set_authority(const std::string & authority);
    void set_path(const std::string & path);
    void set_path(const std::list<std::string> & path);
    void set_query(const std::string & query);
    void set_fragment(const std::string & fragment);

    uri & operator=(const uri & uri);
    bool operator ==(const std::string & str) const;
    bool operator ==(const uri & uri) const;
    bool operator !=(const std::string & str) const;
    bool operator !=(const uri & uri) const;
    uri operator+(const uri & uri) const;
    bool operator<(const uri & uri) const;
    bool operator<=(const uri & uri) const;
    bool operator>(const uri & uri) const;
    bool operator>=(const uri & uri) const;

    const std::string & to_string() const;

    bool cd_up();
    bool cd(const std::string & name);
    bool is_root() const;
private:
    bool _valid;

    std::string _sheme;
    std::string _authority;
    std::list<std::string> _path;
    std::list<std::string> _query;
    std::string _fragment;

    void generate_string();

    std::string _str;
};

std::ostream & operator<<(std::ostream & out, const hsm::uri & uri);

}

namespace std{

template<>
struct hash<hsm::uri>{
    std::size_t operator()(const hsm::uri & key) const{
        return hash<string>()(key.to_string());
    }
};

}
