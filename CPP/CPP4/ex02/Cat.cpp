#include "Cat.hpp"

Cat::Cat()
{
    this->_type = "Cat";
    brain = new Brain();
    std::cout << "Cat default constructor called" << std::endl;
}

Cat::Cat(const Cat &other) : Animal(other)
{
    brain = new Brain(*other.brain);
    std::cout << "Cat copy constructor called for " << _type << std::endl;
}

Cat &Cat::operator=(const Cat &other)
{
    if (this != &other)
    {
        Animal::operator=(other); //copy the base class part first

        Brain* newBrain = new Brain(*other.brain); // create a new brain by copying the other cat's brain(deep copy)
        delete brain; // delete the existing brain to avoid memory leak
        brain = newBrain; // point to the new brain
    }
    std::cout << "Cat copy assignment operator called for " << _type << std::endl;
    return *this;
}

Cat::~Cat()
{
    delete brain;
    std::cout << "Cat destructor called for " << _type << std::endl;
}

void Cat::makeSound() const
{
    std::cout << "Meow!" << std::endl;
}

Brain* Cat::getBrain() const
{
    return brain;
}
