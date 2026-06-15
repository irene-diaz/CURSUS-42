#include "vect2.hpp"

// constructor
vect2::vect2(int x, int y) : _x(x), _y(y)
{
}

// constructor de copia
vect2::vect2(const vect2 &other) : _x(other._x), _y(other._y)
{
}

// operador =
vect2 &vect2::operator=(const vect2 &other)
{
    if (this != &other)
    {
        _x = other._x;
        _y = other._y;
    }
    return *this;
}

// operador +
vect2 vect2::operator+(const vect2 &other) const
{
    return vect2(_x + other._x, _y + other._y);
}

// operador -
vect2 vect2::operator-(const vect2 &other) const
{
    return vect2(_x - other._x, _y - other._y);
}

// operador +=
vect2 &vect2::operator+=(const vect2 &other)
{
    _x += other._x;
    _y += other._y;

    return *this;
}

// operador -=
vect2 &vect2::operator-=(const vect2 &other)
{
    _x -= other._x;
    _y -= other._y;

    return *this;
}

// multiplicación por escalar
vect2 vect2::operator*(int n) const
{
    return vect2(_x * n, _y * n);
}

// operador *=
vect2 &vect2::operator*=(int n)
{
    _x *= n;
    _y *= n;

    return *this;
}

// signo negativo
vect2 vect2::operator-() const
{
    return vect2(-_x, -_y);
}

// preincremento
vect2 &vect2::operator++()
{
    ++_x;
    ++_y;

    return *this;
}

// postincremento
vect2 vect2::operator++(int)
{
    vect2 tmp(*this);

    ++(*this);

    return tmp;
}

// predecremento
vect2 &vect2::operator--()
{
    --_x;
    --_y;

    return *this;
}

// postdecremento
vect2 vect2::operator--(int)
{
    vect2 tmp(*this);

    --(*this);

    return tmp;
}

// operator[] modificable
int &vect2::operator[](int i)
{
    if (i == 0)
        return _x;

    return _y;
}

// operator[] const
const int &vect2::operator[](int i) const
{
    if (i == 0)
        return _x;

    return _y;
}

// ==
bool vect2::operator==(const vect2 &other) const
{
    return (_x == other._x && _y == other._y);
}

// !=
bool vect2::operator!=(const vect2 &other) const
{
    return !(*this == other);
}

// permite hacer 3 * v
vect2 operator*(int n, const vect2 &v)
{
    return v * n;
}

// impresión
std::ostream &operator<<(std::ostream &os, const vect2 &v)
{
    os << "{"
       << v[0]
       << ", "
       << v[1]
       << "}";

    return os;
}