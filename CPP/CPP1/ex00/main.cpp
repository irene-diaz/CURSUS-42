#include "Zombie.hpp"

int main() 
{
    Zombie* z1 = newZombie("HeapZombie");
    z1->announce();
    delete z1;
    randomChump("StackZombie");
    return 0;
}