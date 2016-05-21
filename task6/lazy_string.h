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

    //Constructor of new lazy_string from std::string
    lazy_string(const string &);
    
    //Returns the number of characters in the lazy_string
    size_t size() const;
    
    //Returns the number of characters in the lazy_string
    size_t lenght() const;
    
    //Returns the referens to the character which is located on the position "pos"
    char at(size_t) const;
    
    //Returns the referens to the character which is located on the position "pos"
    chr operator[](size_t);
    char operator[](size_t) const;
    
    //Receivs position of first symbol and the number of characters and
    //returns a substring which is int the interval [position, position+number)
    lazy_string substr(size_t, size_t);
    
    //Reads a string from the input stream 
    friend istream &operator>>(istream &, lazy_string &);
    
    //Writes a string in the output stream
    friend ostream &operator<<(ostream &, lazy_string &);
    
private:
    size_t bg, sz;
    shared_ptr<string> r;
    lazy_string(shared_ptr<string>, size_t, size_t);
};

#endif //LAZYSTRING_LAZY_STRING_H
