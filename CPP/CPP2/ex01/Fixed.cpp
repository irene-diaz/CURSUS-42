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

Fixed::Fixed(const int value)
{
    std::cout << "Int constructor called" << std::endl;
    _value = value << _fractionalBits; // value << _fractionalBits =  value * 256 
}
Fixed::Fixed(const float value)
{
    std::cout << "Float constructor called" << std::endl;
    //must do with '1 << fractionalBits' because the result is a float value
    _value = roundf(value * (1 << _fractionalBits)); // multiply by 256 to store the float value in the fixed-point representation
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
    //std::cout << "getRawBits member function called" << std::endl;
    return _value;
}

void Fixed::setRawBits(int const raw)
{
    _value = raw;
}

float Fixed::toFloat(void) const
{
    return (float)_value / (1 << _fractionalBits); // divide by 256 to convert the fixed-point representation back to a float value
}

int Fixed::toInt(void) const
{
    return _value >> _fractionalBits; // value >> _fractionalBits = value / 256 to convert the fixed-point representation back to an integer value
}

//when you print a Fixed object, do this
/*std:: ostream is the type of std::cout and std::ostream &out is std::cout
operator<< is the function that overloads the << operator for the Fixed class
const Fixed &fixed is the object that we want to print
*/
std::ostream &operator<<(std::ostream &out, const Fixed &fixed)
{
    out << fixed.toFloat(); // print the float representation of the fixed-point number
    return out; // return the output stream to allow chaining of << operator
}