#ifndef LAZYSTRING_LAZY_STRING_H
#define LAZYSTRING_LAZY_STRING_H

#include <string>
#include <memory>
#include <istream>
#include <ostream>
using namespace std;

class lazy_string{
    struct chr{
    friend class lazy_string;
        chr &operator=(char);
    private:
        chr(lazy_string *, size_t);
        size_t i;
        lazy_string *s;
    };
public:
    lazy_string(const string &);
    size_t size() const;
    size_t lenght() const;
    char at(size_t) const;
    char operator[](size_t) const;
    lazy_string substr(size_t, size_t);
    friend istream &operator>>(istream &, lazy_string &);
    friend ostream &operator<<(ostream &, lazy_string &);
    chr operator[](size_t);
private:
    size_t bg, sz;
    shared_ptr<string> r;
    lazy_string(shared_ptr<string>, size_t, size_t);
};

#endif //LAZYSTRING_LAZY_STRING_H
