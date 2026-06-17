#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>
class vect2
{
public:
    vect2(int x = 0, int y = 0);
    vect2(const vect2 &other);
    vect2 &operator=(const vect2 &other);

    vect2 operator+(const vect2 &other) const;
    vect2 operator-(const vect2 &other) const;

    vect2 &operator+=(const vect2 &other);
    vect2 &operator-=(const vect2 &other);

    vect2 operator-() const;

    vect2 operator*(int n) const;
    vect2 &operator*=(int n);

    vect2 &operator++();
    vect2 operator++(int);
    vect2 &operator--();
    vect2 operator--(int);

    vect2 &operator[](int i);
    vect2 &operator[](int i) const;

    bool operator==(const vect2 &other) const;
    bool operator!=(const vect2 &other) const;

private:
    int _x;
    int _y;
};

vect2 operator*(int n, const vect2 &v);
std::ostream &operator<<(std::ostream &os, const vect2 v);
#endif