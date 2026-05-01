#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main()
{
    const Animal* dog = new Dog();
    const Animal* cat = new Cat();

    Dog a;
    Dog b = a;

    a.makeSound();
    b.makeSound();

    a.getBrain()->setIdea(0, "Idea 1");
    a.getBrain()->setIdea(1, "Idea 2");
    a.getBrain()->getIdea(0);
    a.getBrain()->getIdea(1);

    delete dog; //should not create a leak
    delete cat; //should not create a leak
    
    return 0;
}