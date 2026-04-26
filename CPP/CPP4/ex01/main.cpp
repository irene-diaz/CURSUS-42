#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main()
{
    const Animal* dog = new Dog();
    const Animal* cat = new Cat();
    const Brain* brain = new Brain();

    Dog a;
    Dog b = a;

    a.makeSound();
    b.makeSound();

    brain = new Brain(*other.brain);

    brain->setIdea(0, "Idea 1");
    brain->setIdea(1, "Idea 2");
    brain->getIdea(0);
    brain->getIdea(1);

    delete dog; //should not create a leak
    delete cat; //should not create a leak
    delete brain;
    
    return 0;
}