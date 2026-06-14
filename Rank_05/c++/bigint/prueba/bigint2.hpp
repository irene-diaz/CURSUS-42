#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>
#include <sstream>
#include <cstdlib>
class bigint
{
public:
    bigint();
    bigint(unsigned int n);
    bigint(const bigint &other);

    bigint &operator=(const bigint &other);
    bigint operator+(const bigint &other) const;
    bigint &operator+=(const bigint &other);

    bigint &operator++();
    bigint operator++(int);

    bigint operator<<(const bigint &shift) const;
    bigint operator>>(const bigint &shift) const;
    bigint &operator<<=(const bigint &shift);
    bigint &operator>>=(const bigint &shift);

    bool operator<(const bigint &other) const;
    bool operator>(const bigint &other) const;
    bool operator<=(const bigint &other) const;
    bool operator>=(const bigint &other) const;
    bool operator==(const bigint &other) const;
    bool operator!=(const bigint &other) const;

private:
    std::string _value;
    void normalize();
    friend std::ostream &operator<< (std::ostream &os, const bigint &n);
};
std::ostream &operator<< (std::ostream &os, const bigint &n);
#endif