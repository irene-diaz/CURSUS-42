#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
    std::cout << "\n=== CORRECT ANIMALS ===\n";

    const Animal* meta = new Animal();
    const Animal* dog = new Dog();
    const Animal* cat = new Cat();

    std::cout << dog->getType() << std::endl;
    std::cout << cat->getType() << std::endl;

    cat->makeSound(); // Meow ✔
    dog->makeSound(); // Woof ✔
    meta->makeSound(); // Animal sound ✔

    delete meta;
    delete dog;
    delete cat;

    std::cout << "\n=== WRONG ANIMALS ===\n";

    const WrongAnimal* wrongMeta = new WrongAnimal();
    const WrongAnimal* wrongCat = new WrongCat();

    std::cout << wrongCat->getType() << std::endl;

    wrongCat->makeSound(); // ❌ WrongAnimal sound

    delete wrongMeta;
    delete wrongCat;

    return 0;
}