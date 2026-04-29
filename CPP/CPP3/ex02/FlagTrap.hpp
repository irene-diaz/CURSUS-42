#ifndef FLAGTRAP_HPP
#define FLAGTRAP_HPP

#include "ClapTrap.hpp"

class FlagTrap : public ClapTrap
{
public:
    FlagTrap();
    FlagTrap(const std::string &name);
    FlagTrap(const FlagTrap &other);
    FlagTrap &operator=(const FlagTrap &other);
    ~FlagTrap();

    void attack(const std::string &target); // for FlagTrap, attack should cause 30 points of damage instead of 0
    void highFivesGuys();
};

#endif
