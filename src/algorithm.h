#pragma once

#include <string>
#include <list>

namespace hsm{

inline double abs(double d){
    if(d < 0.0)
        return -d;
    return d;
}

inline bool fuzzy_is_null(double d){
    return abs(d) <= 0.000000000001;
}

template<typename T>
inline T join(const std::list<T> & list){
    T r;
    for(const T & t : list){
        r = r+t;
    }
    return r;
}

inline std::string join(const std::list<std::string> &list, const std::string & sep){
    std::string str;
    for(const std::string & t : list){
        if(!str.empty())
            str += sep;
        str += t;
    }
    return str;
}

inline std::string join(const std::list<std::string> &list, char sep){
    std::string str;
    for(const std::string & t : list){
        if(!str.empty())
            str += sep;
        str += t;
    }
    return str;
}

inline std::list<std::string> split(const std::string & str, char c){
    std::list<std::string> list;
    size_t pos = 0;
    size_t p = 0;
    while(p != str.size()){
        p = str.find(c, pos);
        if(p == std::string::npos)
            p = str.size();
        list.push_back(str.substr(pos, p-pos));
        pos = p+1;
    }
    return list;
}

inline std::list<std::string> split(const std::string &str, const std::string & sep){
    std::list<std::string> list;
    size_t pos = 0;
    size_t p = 0;
    while(p != str.size()){
        p = str.find(sep, pos);
        if(p == std::string::npos)
            p = str.size();
        list.push_back(str.substr(pos, p-pos));
        pos = p+sep.size();
    }
    return list;
}

inline size_t indexOf(const std::string & str, char c){
    return str.find(c);
}

inline size_t indexOf(const std::string &str, const std::string & pattern){
    return str.find(pattern);
}

template<typename T>
inline typename std::list<T>::const_iterator find(const std::list<T> & list, const T & value){
    for(auto it = list.begin(); it != list.end(); ++it){
        if(*it == value)
            return it;
    }
    return list.end();
}

template<typename T>
inline typename std::list<T>::iterator find(std::list<T> & list, const T & value){
    for(auto it = list.begin(); it != list.end(); ++it){
        if(*it == value)
            return it;
    }
    return list.end();
}

template<typename T>
inline const T & reach(const std::list<T> & list, size_t i){
    auto it = list.begin();
    while(i > 0){
        ++it;
        --i;
    }
    return *it;
}

template<typename T>
inline bool contains(const std::list<T> & list, const T & value){
    return find(list, value) != list.end();
}

inline std::string section(const std::string & str, int begin, int n){
    return std::string(str.data()+begin, n);
}

inline size_t findn(const std::string & str, int n, char c, size_t pos = 0){
    while(n > 0){
        pos = str.find(c, pos);
        if(pos == std::string::npos)
            return std::string::npos;
        ++pos;
        --n;
    }
    while(n < -1){
        pos = str.rfind(c, --pos);
        if(pos == std::string::npos)
            return std::string::npos;
        ++n;
    }
    return pos;
}

inline size_t findn(const std::string & str, int n, const std::string & c, size_t pos = 0){
    while(n > 0){
        pos = str.find(c, pos);
        if(pos == std::string::npos)
            return std::string::npos;
        pos += c.size();
        --n;
    }
    while(n < -1){
        pos -= c.size();
        pos = str.rfind(c, pos);
        if(pos == std::string::npos)
            return std::string::npos;
        ++n;
    }
    return pos;
}

inline std::string section(const std::string & str, char sep, int begin, int end){
    size_t a = 0;
    size_t b = 0;
    if(begin > 0){
        a = findn(str, begin, sep, 0);
        if(a == std::string::npos)
            a = str.size();
        if(end >= 0){
            if(end < begin || a == str.size())
                return "";
            b = findn(str, end-begin+1, sep, a+1);
            if(b == std::string::npos)
                b = str.size();
            else
                --b;
        }
    }
    if(end < 0){
        b = findn(str, end, sep, str.size());
        if(b == std::string::npos)
            b = 0;
        if(begin < 0){
            if(begin > end || b == 0)
                return "";
            a = findn(str, begin-end-2, sep, b);
            if(a == std::string::npos)
                a = 0;
            else
                ++a;
        }
    }
    if(begin < 0 && end >= 0){
        a = findn(str, begin-1, sep, str.size()-1);
        if(a == std::string::npos)
            a = 0;
        else
            ++a;
    }
    if(end >= 0 && begin <= 0){
        b = findn(str, end+1, sep, 0);
        if(b == std::string::npos)
            b = str.size();
        else
            --b;
    }
    if(b < a)
        return "";
    return str.substr(a, b-a);
}

inline std::string section(const std::string & str, const std::string &sep, int begin, int end){
    size_t a = 0;
    size_t b = 0;
    if(begin > 0){
        a = findn(str, begin, sep, 0);
        if(a == std::string::npos)
            a = str.size();
        if(end >= 0){
            if(end < begin || a == str.size())
                return "";
            b = findn(str, end-begin+1, sep, a+sep.size());
            if(b == std::string::npos)
                b = str.size();
            else
                b -= sep.size();
        }
    }
    if(end < 0){
        b = findn(str, end, sep, str.size());
        if(b == std::string::npos)
            b = 0;
        if(begin < 0){
            if(begin > end || b == 0)
                return "";
            a = findn(str, begin-end-2, sep, b);
            if(a == std::string::npos)
                a = 0;
            else
                a += sep.size();
        }
    }
    if(begin < 0 && end >= 0){
        a = findn(str, begin-1, sep, str.size()-1);
        if(a == std::string::npos)
            a = 0;
        else
            a += sep.size();
    }
    if(end >= 0 && begin <= 0){
        b = findn(str, end+1, sep, 0);
        if(b == std::string::npos)
            b = str.size();
        else
            b -= sep.size();
    }
    if(b < a)
        return "";
    return str.substr(a, b-a);
}

template<class T>
std::list<T> operator+(const std::list<T> & list, T item){
    std::list<T> rlist = list;
    rlist.push_back(item);
    return rlist;
}

template<class T>
std::list<T> operator+(const std::list<T> & list, const std::list<T> blist){
    std::list<T> rlist = list;
    for(const T & t : blist){
        rlist.push_back(t);
    }
    return rlist;
}

}
