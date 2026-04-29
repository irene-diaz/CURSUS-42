#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main()
{
    std::cout << "\n=== CLAPTRAP TEST ===\n";
    ClapTrap a("A");
    ClapTrap b("B");

    a.attack("B");
    b.takeDamage(0);

    a.beRepaired(5);

    for (int i = 0; i < 11; i++)
        a.attack("B"); // without energy, should not attack
    b.takeDamage(100); // dead
    b.attack("A");
    b.beRepaired(5);

    std::cout << "\n=== SCAVTRAP TEST ===\n";
    ScavTrap s("Scavvy");

    s.attack("enemy"); // override (different damage and message)
    s.takeDamage(30);
    s.beRepaired(10);

    std::cout << "\n=== GUARD MODE ===\n";
    s.guardGate();

    std::cout << "\n=== SCAV ENERGY TEST ===\n";
    for (int i = 0; i < 51; i++)
        s.attack("enemy"); // should be able to support more (50 energy)

    std::cout << "\n=== SCAV DEAD TEST ===\n";
    s.takeDamage(200); // dead (has 100 HP)
    s.attack("enemy");
    s.beRepaired(10);

    return 0;
}