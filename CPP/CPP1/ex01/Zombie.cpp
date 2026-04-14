#include "Zombie.hpp"

Zombie::Zombie() 
{
    this->name = "Unnamed Zombie";
}

Zombie::Zombie(std::string name) 
{
    this->name = name;
}

Zombie::~Zombie() 
{
    std::cout << "Zombie " << this->name << " has been destroyed." << std::endl;
}

void Zombie::announce() 
{
    std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::setName(std::string name) 
{
    this->name = name;
}