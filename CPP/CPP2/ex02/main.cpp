#include "Fixed.hpp"

int main()
{
    Fixed a;
    Fixed const b(Fixed(5.05f) * Fixed(2));

    /*PUEBAS OPERADORES*/
    //---------------------------------------------
    // Operador >
    std::cout << (a > b) << std::endl; //0
    // Operador <
    std::cout << (a < b) << std::endl; //1
    // Operador >=
    std::cout << (a >= b) << std::endl; //0
    // Operador <=
    std::cout << (a <= b) << std::endl; //1
    // Operador ==
    std::cout << (a == b) << std::endl; //0
    // Operador !=
    std::cout << (a != b) << std::endl; //1
    //----------------------------------------------
    // Operador de suma
    std::cout << (a + b) << std::endl; //10.1055
    // Operador de resta
    std::cout << (b - a) << std::endl; //10.0973
    // Operador de multiplicación
    std::cout << (a * b) << std::endl; //0.03125
    // Operador de división
    std::cout << (b / a) << std::endl; //259.2
    //----------------------------------------------
    // Operadores de incremento (pos y pre)
    std::cout << a << std::endl; //0
    std::cout << ++a << std::endl; //0.00390625
    std::cout << a << std::endl; //0.00390625
    std::cout << a++ << std::endl; //0.00390625
    std::cout << a << std::endl; //0.0078125
    // Operadores de decremento (pos y pre)
    std::cout << a << std::endl; //0.0078125
    std::cout << --a << std::endl; //0.00390625
    std::cout << a << std::endl; //0.00390625
    std::cout << a-- << std::endl; //0.00390625
    std::cout << a << std::endl; //0
    //----------------------------------------------
    // Operador de max
    std::cout << b << std::endl; //10.1016
    std::cout << Fixed::max(a, b) << std::endl; //10.1016
    // Operador de min
    std::cout << Fixed::min(a, b) << std::endl; //0

    return 0;
}