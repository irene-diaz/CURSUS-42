#include "Animal.hpp"

Animal::Animal() : _type("Animal")
{
    std::cout << "Animal default constructor called" << std::endl;
}

Animal::Animal(const std::string &type) : _type(type)
{
    std::cout << "Animal parameterized constructor called for " << _type << std::endl;
}

Animal::Animal(const Animal &other) : _type(other._type)
{
    std::cout << "Animal copy constructor called for " << _type << std::endl;
}

Animal &Animal::operator=(const Animal &other)
{
    if (this != &other)
    {
        _type = other._type;
    }
    std::cout << "Animal copy assignment operator called for " << _type << std::endl;
    return *this;
}

Animal::~Animal()
{
    std::cout << "Animal destructor called for " << _type << std::endl;
}

std::string Animal::getType() const
{
    return _type;
}

void Animal::makeSound() const
{
    std::cout << "Animal " << _type << " makes a sound!" << std::endl;
}