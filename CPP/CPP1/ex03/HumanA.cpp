#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &weapon) : name(name), _weapon(weapon)
{
	this->name = name;
	this->_weapon = weapon;
}
/*HumanA::~HumanA()
{
	std::cout << this->_name << " has been destroyed." << std::endl;
}*/
void HumanA::attack()
{
	std::cout << this->name << " attacks with their " << this->_weapon.getType() << std::endl;
}
