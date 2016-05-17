#include "rational.h"


rational::rational(int x){
    n = x;
    d = 1;
}

rational::rational(int x, int y){
    n = x;
    d = y;
    simplify(n, d);
}

int rational::getNum() const{
    return n;
}

int rational::getDenom() const{
    return d;
}

int gcd(int a, int b){
    for (;;)
    {
        if (a == 0) return b;
        b %= a;
        if (b == 0) return a;
        a %= b;
    }
}

int lcm(int a, int b){
    int temp = gcd(a, b);

    return temp ? (a / temp * b) : 0;
}

rational rational::operator +(rational const &x) const {
    int denom = lcm(d, x.d);
    int num = (n * (denom / d)) + (x.n * (denom / x.d));
    return rational(num, denom);
}

rational rational::operator -(rational const &x) const {
    int denom = lcm(d, x.d);
    int num = (n * (denom / d)) - (x.n * (denom / x.d));
    return rational(num, denom);
}

rational rational::operator *(rational const &x) const {
    return rational(n * x.n, d * x.d);
}

rational rational::operator /(rational const &x) const {
    return rational(n * x.d, d * x.n);
}

void rational::simplify(int &a, int &b){
    int c = gcd(a, b);
    a /= c;
    b /= c;
}