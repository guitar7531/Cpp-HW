#ifndef LAZYSTRING_LAZY_STRING_H
#define LAZYSTRING_LAZY_STRING_H

#include <string>
#include <memory>
#include <istream>
#include <ostream>
using namespace std;

class lazy_string{
public:
    lazy_string(string &);
    size_t size();
    size_t lenght();
    char at(size_t);
    char operator[](size_t);
    lazy_string substr(size_t, size_t);
    istream operator>>(istream &, lazy_string &);
    ostream operator<<(ostream &, lazy_string &);
private:
    size_t bg, sz;
    shared_ptr<string> r;
    lazy_string(shared_ptr, size_t, size_t);
};

#endif //LAZYSTRING_LAZY_STRING_H
