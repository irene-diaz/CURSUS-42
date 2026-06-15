#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>
class vect2
{
public:
    vect2(int x = 0, int y = 0); // constructor
    vect2(const vect2 &other);   // constructor de copia

    vect2 &operator=(const vect2 &other); // operador =

    vect2 operator+(const vect2 &other) const; // operador +
    vect2 operator-(const vect2 &other) const; // operador -

    vect2 &operator+=(const vect2 &other); // operador +=
    vect2 &operator-=(const vect2 &other); // operador -=

    vect2 operator*(int n) const; // multiplicación por escalar
    vect2 &operator*=(int n);     // operador *=

    vect2 operator-() const; // operador signo negativo

    vect2 &operator++();   // preincremento
    vect2 operator++(int); // postincremento

    vect2 &operator--();   // predecremento
    vect2 operator--(int); // postdecremento

    //permite acceder a los elementos del vector como si fuera un array
    int &operator[](int i);             // operator[] modificable
    const int &operator[](int i) const; // operator[] no modificable

    bool operator==(const vect2 &other) const; // operador ==
    bool operator!=(const vect2 &other) const; // operador !=

private:
    int _x; // 1º numero del vector
    int _y; // 2º numero del vector
};

vect2 operator*(int n, const vect2 &v); // operador * con el escalar a la izquierda

std::ostream &operator<<(std::ostream &os, const vect2 &v); // operador << para imprimir vect2

#endif