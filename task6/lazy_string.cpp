#include <iostream>
#include "lazy_string.h"

using namespace std;

lazy_string::operator string() {
    return r->substr(bg, sz);
};


lazy_string::lazy_string(const string &s) {
    r = make_shared<string>(s);
    sz = s.size();
    bg = 0;
}

lazy_string::lazy_string(shared_ptr<string> p, size_t cnt, size_t b) {
    r = p;
    bg = b;
    sz = cnt;
}

char lazy_string::at(size_t pos) const{
    return (*r)[pos + bg];
}

char lazy_string::operator[](size_t pos) const{
    return (*r)[pos + bg];
}

size_t lazy_string::size() const{
    return sz;
}

size_t lazy_string::lenght() const{
    return sz;
}

lazy_string lazy_string::substr(size_t pos, size_t cnt) {
    return lazy_string(r, cnt, pos);
}

istream &operator>>(istream &in, lazy_string &s) {
    auto nr = make_shared<string>();
    in >> *nr;
    s.r = nr;
    s.bg = 0;
    s.sz = nr->size();
    return in;
}

ostream &operator<<(ostream &out,lazy_string &s) {
    for (int i = 0; i < s.sz; i++)
        out << (*s.r)[i + s.bg];
    return out;
}
