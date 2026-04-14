#include "Zombie.hpp"

// Function to create a new Zombie on the heap and return a pointer to it
Zombie* newZombie(std::string name) 
{
    Zombie* z = new Zombie(name);
    return z;
}