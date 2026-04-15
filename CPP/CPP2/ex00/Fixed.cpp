#include "Fixed.hpp"

Fixed::Fixed()
{
    _value = 0; //_value is the same as this->_value
    std::cout << "Default constructor called" << std::endl;
}
//Copy constructor create a new object as a copy of an existing object
Fixed::Fixed(const Fixed &other)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = other; // same as this->_value = other._value
}

//Copy assignment operator is used to copy the value of an existing object to another existing object
Fixed &Fixed::operator=(const Fixed &other)
{
    std::cout << "Copy assignment operator called" << std::endl;
    //only copy the value if the two objects are not the same
    if (this != &other)
        this->_value = other.getRawBits();
    return *this;
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const
{
    std::cout << "getRawBits member function called" << std::endl;
    return _value;
}

void Fixed::setRawBits(int const raw)
{
    _value = raw;
}