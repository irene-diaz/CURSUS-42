#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP
#include <iostream>

class ClapTrap
{
private:
    std::string _name;
    unsigned int _hitPoints;    // health points (how much damage it can take before dying)
    unsigned int _energyPoints; // how many actions it can perform (attack, repair, etc.) before running out of energy
    unsigned int _attackDamage; // how much damage it can inflict on others when it attacks

public:
    ClapTrap();
    ClapTrap(const std::string &name);
    ClapTrap(const ClapTrap &other);
    ClapTrap &operator=(const ClapTrap &other);
    ~ClapTrap();

    void attack(const std::string &target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);
};

#endif