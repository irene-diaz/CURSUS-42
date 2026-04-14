#include "Zombie.hpp"

// Function to create a new Zombie on the stack(destroy automatically) and announce it
void randomChump(std::string name) 
{
    Zombie z(name);
    z.announce();
}