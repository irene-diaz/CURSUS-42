#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FlagTrap.hpp"

int main()
{
    std::cout << "\n=== CLAPTRAP ===\n";
    ClapTrap a("A");
    a.attack("enemy");

    std::cout << "\n=== SCAVTRAP ===\n";
    ScavTrap s("Scavvy");
    s.attack("enemy");
    s.guardGate();

    std::cout << "\n=== FLAGTRAP ===\n";
    FlagTrap fl("Flaggy");
    fl.attack("enemy");
    fl.highFivesGuys();

    std::cout << "\n=== COMBAT TEST ===\n";
    fl.takeDamage(50);
    fl.beRepaired(20);

    std::cout << "\n=== ENERGY TEST ===\n";
    for (int i = 0; i < 101; i++)
        fl.attack("enemy"); // should run out of energy after 100 attacks

    return 0;
}