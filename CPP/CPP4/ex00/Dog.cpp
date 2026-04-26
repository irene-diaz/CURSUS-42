#include "Dog.hpp"

Dog::Dog() : Animal("Dog")
{
    std::cout << "Dog default constructor called" << std::endl;
}

Dog::Dog(const Dog &other) : Animal(other)
{
    std::cout << "Dog copy constructor called for " << _type << std::endl;
}

Dog &Dog::operator=(const Dog &other)
{
    if (this != &other)
    {
        Animal::operator=(other);
    }
    std::cout << "Dog copy assignment operator called for " << _type << std::endl;
    return *this;
}

Dog::~Dog()
{
    std::cout << "Dog destructor called for " << _type << std::endl;
}

void Dog::makeSound() const
{
    std::cout << "Woof!" << std::endl;
}