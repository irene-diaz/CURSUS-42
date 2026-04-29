#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main()
{
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    const Brain* brain = new Brain();

    brain->setIdea(0, "Idea 1");
    brain->setIdea(1, "Idea 2");
    brain->getIdea(0);
    brain->getIdea(1);

    delete j;//should not create a leak
    delete i;
    delete brain;
    
    return 0;
}