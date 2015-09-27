#ifndef SWAPI_URI_H
#define SWAPI_URI_H

#include <string>
#include <list>

namespace hsm{

class uri{
public:
    enum ReadMode{
        PathOnly = 0,
        Query = 2,
        Fragment = 1,
        Sheme = 8,
        Authority = 4,
        Normal = 15
    };

    uri(ReadMode = Normal);
    uri(const std::string & uri);
    uri(const std::string & uri, ReadMode rm);
    uri(const uri & uri);

    void setUri(std::string uri);
    void clear();

    const std::string & sheme() const;
    const std::string & authority() const;
    const std::list<std::string> & path() const;
    const std::list<std::string> &  query() const;
    const std::string & fragment() const;

    std::string inspect() const;

    bool isAbsolute() const;
    void makeAbsolute(const uri & position);
    uri absolute(const uri & position) const;

    void setSheme(const std::string & sheme);
    void setAuthority(const std::string & authority);
    void setPath(const std::string & path);
    void setPath(const std::list<std::string> & path);
    void setQuery(const std::string & query);
    void setFragment(const std::string & fragment);

    bool operator ==(const std::string & str) const;
    bool operator ==(const uri & uri) const;
    bool operator !=(const std::string & str) const;
    bool operator !=(const uri & uri) const;
    uri operator+(const uri & uri) const;

    std::string toString() const;

    bool cdUp();
    bool cd(const std::string & name);
    bool isRoot() const;
private:
    std::string _sheme;
    std::string _authority;
    std::list<std::string> _path;
    std::list<std::string> _query;
    std::string _fragment;

    bool _absolute_path;
    ReadMode _rm;
};

}

#endif // SWAPI_URI_H
