#ifndef TASK3_RATIONAL_H
#define TASK3_RATIONAL_H

class rational
{
private:
    int n, d;
    void simplify(int &, int &);
public:
    rational(int);
    rational(int, int);
    int getNum() const;
    int getDenom() const;
    rational operator +(rational const &)const;
    rational operator -(rational const &)const;
    rational operator *(rational const &)const;
    rational operator /(rational const &)const;
};
