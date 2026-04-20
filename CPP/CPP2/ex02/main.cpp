#include "Fixed.hpp"

int main()
{
    Fixed a;
    Fixed const b(Fixed(5.05f) * Fixed(2));
    Fixed c = 5;

    /* TESTING OPERATORS */
    //---------------------------------------------
    // Operator >
    std::cout << "Operator >: " << std::endl;
    std::cout << (a > b) << std::endl; //0
    // Operator <
    std::cout << "Operator <: " << std::endl;
    std::cout << (a < b) << std::endl; //1
    // Operator >=
    std::cout << "Operator >=: " << std::endl;
    std::cout << (a >= b) << std::endl; //0
    // Operator <=
    std::cout << "Operator <=: " << std::endl;
    std::cout << (a <= b) << std::endl; //1
    // Operator ==
    std::cout << "Operator ==: " << std::endl;
    std::cout << (a == b) << std::endl; //0
    // Operator !=
    std::cout << "Operator !=: " << std::endl;
    std::cout << (a != b) << std::endl; //1
    //----------------------------------------------
    // Addition operator
    std::cout << "Operator +: " << std::endl;
    std::cout << (c + b) << std::endl; //15.1016
    // Subtraction operator
    std::cout << "Operator -: " << std::endl;
    std::cout << (b - c) << std::endl; //5.1016
    // Multiplication operator
    std::cout << "Operator *: " << std::endl;
    std::cout << (c * b) << std::endl; //50.5078
    // Division operator
    std::cout << "Operator /: " << std::endl;
    std::cout << (b / c) << std::endl; //2.01953
    //----------------------------------------------
    // Increment operators (post and pre)
    std::cout << "Operator ++: " << std::endl;
    std::cout << a << std::endl; //0
    std::cout << ++a << std::endl; //0.00390625
    std::cout << a << std::endl; //0.00390625
    std::cout << a++ << std::endl; //0.00390625
    std::cout << a << std::endl; //0.0078125
    // Decrement operators (post and pre)
    std::cout << "Operator --: " << std::endl;
    std::cout << a << std::endl; //0.0078125
    std::cout << --a << std::endl; //0.00390625
    std::cout << a << std::endl; //0.00390625
    std::cout << a-- << std::endl; //0.00390625
    std::cout << a << std::endl; //0
    //----------------------------------------------
    // Max operator
    std::cout << a << std::endl; //0
    std::cout << b << std::endl; //10.1016
    std::cout << "Operator max: " << std::endl;
    std::cout << Fixed::max(a, b) << std::endl; //10.1016
    // Min operator
    std::cout << "Operator min: " << std::endl;
    std::cout << Fixed::min(a, b) << std::endl; //0

    return 0;
}