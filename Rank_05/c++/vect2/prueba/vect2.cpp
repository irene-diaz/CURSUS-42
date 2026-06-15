#include "vect2.hpp"

vect2 ::vect2(int x, int y) : _x(x), _y(y)
{
}

vect2 ::vect2(const vect2 &other) : _x(other._x), _y(other._y)
{
}

vect2 &vect2::operator=(const vect2 &other)
{
    if (this != &other)
    {
        _x = other._x;
        _y = other._y;
    }
    return *this;
}

vect2 vect2 ::operator+(const vect2 &other) const
{
    return (_x + other._x, _y + other._y);
}

vect2 vect2 ::operator-(const vect2 &other) const
{
    return (_x + other._x, _y + other._y);
}

vect2 vect2 ::operator-() const
{
    return vect2(-(_x), -(_y));
}

vect2 &vect2 ::operator+=(const vect2 &other)
{
    _x += other._x;
    _y += other._y;
    return *this;
}

vect2 &vect2 ::operator-=(const vect2 &other)
{
    _x -= other._x;
    _y -= other._y;
    return *this;
}

vect2 &vect2 ::operator++()
{
    ++_x;
    ++_y;

    return *this;
}

vect2 vect2::operator++(int)
{
    vect2 tmp(*this);
    ++(*this);
    return tmp;
}

vect2 &vect2 ::operator--()
{
    --_x;
    --_y;

    return *this;
}

vect2 vect2::operator--(int)
{
    vect2 tmp(*this);
    --(*this);
    return tmp;
}

vect2 vect2 ::operator*(int n) const
{
    return vect2(_x * n, _y * n);
}

vect2 &vect2 ::operator*=(int n)
{
    _x *= n;
    _y *= n;
    return *this;
}

int &vect2 ::operator[](int i)
{
    if (i == 0)
        return _x;
    return _y;
}

const int &vect2 ::operator[](int i) const
{
    if (i == 0)
        return _x;
    return _y;
}

bool vect2 ::operator==(const vect2 &other) const
{
    return (_x == other._x && _y == other._y);
}

bool vect2 ::operator!=(const vect2 &other) const
{
    return !(*this == other);
}

vect2 operator*(int n, const vect2 &v)
{
    return n * v;
}

std::ostream &operator<<(std::ostream &os, const vect2 &v)
{
    os << "{"
       << v[0]
       << ", "
       << v[1]
       << "}";

    return os;
}