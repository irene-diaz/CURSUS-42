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

    void highFivesGuys();
};

#endif
