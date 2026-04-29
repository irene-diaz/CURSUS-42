#include "ClapTrap.hpp"

int main()
{
    std::cout << "\n=== BASIC FIGHT ===\n";
    ClapTrap a("A");
    ClapTrap b("B");

    a.attack("B");
    b.takeDamage(0);

    std::cout << "\n=== REPAIR ===\n";
    a.beRepaired(5);

    std::cout << "\n=== ENERGY LIMIT ===\n";
    for (int i = 0; i < 11; i++)
        a.attack("B"); // should stop after 10 attacks, as energy points are depleted

    std::cout << "\n=== DEAD STATE ===\n";
    b.takeDamage(100); // dead
    b.attack("A");     // should not be able to attack
    b.beRepaired(5);   // should not be able to repair

    std::cout << "\n=== OVERKILL ===\n";
    ClapTrap c("C");
    c.takeDamage(1000); // should not cause underflow

    return 0;
}