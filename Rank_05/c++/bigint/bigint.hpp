#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

/*Si devolvemso con & creamos un objeto nuevo, sino no lo creamos*/
class bigint
{
public:
    bigint();                    // constructor por defecto
    bigint(unsigned int n);      // constructor a partir de un entero sin signo
    bigint(const bigint &other); // constructor de copia

    bigint &operator=(const bigint &other);      // operador de asignación
    bigint operator+(const bigint &other) const; // operador de suma
    bigint &operator+=(const bigint &other);     // operador de suma y asignación
    bigint &operator++();                        // operador de pre-incremento
    bigint operator++(int);                      // operador de post-incremento

    bigint operator<<(const bigint &shift) const; // operador de desplazamiento a la izquierda
    bigint operator>>(const bigint &shift) const; // operador de desplazamiento a la derecha

    bigint &operator<<=(const bigint &shift); // operador de desplazamiento a la izquierda y asignación
    bigint &operator>>=(const bigint &shift); // operador de desplazamiento a la derecha y asignación

    bool operator<(const bigint &other) const;  // operador de comparación menor que
    bool operator<=(const bigint &other) const; // operador de comparación menor o igual que
    bool operator>(const bigint &other) const;  // operador de comparación mayor que
    bool operator>=(const bigint &other) const; // operador de comparación mayor o igual que
    bool operator==(const bigint &other) const; // operador de comparación de igualdad
    bool operator!=(const bigint &other) const; // operador de comparación de desigualdad

private:
    std::string _value; // representación interna del número como una cadena de dígitos

    void normalize(); // función para eliminar ceros a la izquierda y mantener la representación canónica

    friend std::ostream &operator<<(std::ostream &os,
                                    const bigint &n); // operador de inserción para imprimir el número
};

std::ostream &operator<<(std::ostream &os, const bigint &n); // declaración del operador de inserción para imprimir el número

#endif