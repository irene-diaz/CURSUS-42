#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
    const Animal *meta = new Animal();
    const Animal *dog = new Dog();
    const Animal *cat = new Cat();
    std::cout << dog->getType() << " " << std::endl;
    std::cout << cat->getType() << " " << std::endl;
    cat->makeSound(); // will output the cat sound!
    dog->makeSound();
    meta->makeSound();

    delete meta;
    delete dog;
    delete cat;
    return 0;
}