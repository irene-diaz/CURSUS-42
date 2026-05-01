#include "Cat.hpp"

Cat::Cat()
{
    this->_type = "Cat";
    std::cout << "Cat default constructor called" << std::endl;
}

Cat::Cat(const Cat &other) : Animal(other)
{
    std::cout << "Cat copy constructor called for " << _type << std::endl;
}

Cat &Cat::operator=(const Cat &other)
{
    if (this != &other)
    {
        Animal::operator=(other);
    }
    std::cout << "Cat copy assignment operator called for " << _type << std::endl;
    return *this;
}

Cat::~Cat()
{
    std::cout << "Cat destructor called for " << _type << std::endl;
}

void Cat::makeSound() const
{
    std::cout << "Meow!" << std::endl;
}