#include "Fixed.hpp"

int main()
{
    Fixed a;
    Fixed b(a); //create a new object 'b' as a copy of an existing object 'a' using the copy constructor
    Fixed c;

    c = b;  //use the copy assignment operator to copy the value of an existing object 'b' to another existing object 'c'

    std::cout << a.getRawBits() << std::endl;
    std::cout << b.getRawBits() << std::endl;
    std::cout << c.getRawBits() << std::endl;

    return 0;
}