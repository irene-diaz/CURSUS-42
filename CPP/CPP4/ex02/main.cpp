#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
    std::cout << "\n=== ABSTRACT CLASS TEST ===\n";

    // Animal a; ❌ NO COMPILA (Animal es abstracta)

    const Animal* dog = new Dog();
    const Animal* cat = new Cat();

    std::cout << "\n=== MAKE SOUND TEST ===\n";
    dog->makeSound();
    cat->makeSound();

    std::cout << "\n=== TYPE TEST ===\n";
    std::cout << "Dog type: " << dog->getType() << std::endl;
    std::cout << "Cat type: " << cat->getType() << std::endl;

    std::cout << "\n=== POLYMORPHISM TEST ===\n";
    Animal* animals[4];

    for (int i = 0; i < 2; i++)
        animals[i] = new Dog();
    for (int i = 2; i < 4; i++)
        animals[i] = new Cat();

    for (int i = 0; i < 4; i++)
        animals[i]->makeSound();

    std::cout << "\n=== CLEANUP TEST ===\n";
    for (int i = 0; i < 4; i++)
        delete animals[i];

    delete dog;
    delete cat;

    return 0;
}