#include "HumanB.hpp"

HumanB::HumanB(std::string name)
{
    this->name = name;
    this->weapon = NULL;
}
/*HumanB::~HumanB()
{
    std::cout << this->name << " has been destroyed." << std::endl;
}*/

void HumanB::setWeapon(Weapon &weapon)
{
    this->weapon = &weapon;
}

void HumanB::attack()
{
    if (this->weapon)
        std::cout << this->name << " attacks with their " << this->weapon->getType() << std::endl;
    else
        std::cout << this->name << " has no weapon to attack with." << std::endl;
}