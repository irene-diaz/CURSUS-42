#include "Dog.hpp"

Dog::Dog() : Animal("Dog")
{
    brain = new Brain();
    std::cout << "Dog default constructor called" << std::endl;
}

Dog::Dog(const Dog &other) : Animal(other)
{
    brain = new Brain(*other.brain);
    std::cout << "Dog copy constructor called for " << _type << std::endl;
}

Dog &Dog::operator=(const Dog &other)
{
    if (this != &other)
    {
        Animal::operator=(other); //copy the base class part first

        delete brain; // delete the existing brain to avoid memory leak
        brain = new Brain(*other.brain); // create a new brain by copying the other cat's brain(deep copy)
    }
    std::cout << "Dog copy assignment operator called for " << _type << std::endl;
    return *this;
}

Dog::~Dog()
{
    delete brain;
    std::cout << "Dog destructor called for " << _type << std::endl;
}

void Dog::makeSound() const
{
    std::cout << "Woof!" << std::endl;
}