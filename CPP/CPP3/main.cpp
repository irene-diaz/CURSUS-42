#include "ClapTrap.hpp"

int main()
{
    std::cout << "\n=== BASIC TEST ===\n";
    ClapTrap a("A");
    ClapTrap b("B");

    a.attack("B");
    b.takeDamage(0);

    std::cout << "\n=== REPAIR TEST ===\n";
    a.beRepaired(5);

    std::cout << "\n=== ENERGY TEST ===\n";
    for (int i = 0; i < 11; i++)
        a.attack("B");

    std::cout << "\n=== DEAD TEST ===\n";
    b.takeDamage(100);
    b.attack("A");
    b.beRepaired(5);

    std::cout << "\n=== OVERKILL TEST ===\n";
    ClapTrap c("C");
    c.takeDamage(1000);

    std::cout << "\n=== COPY TEST ===\n";
    ClapTrap d(a);
    d.attack("B");

    std::cout << "\n=== ASSIGNMENT TEST ===\n";
    ClapTrap e("E");
    e = a;
    e.attack("B");

    std::cout << "\n=== ZERO ENERGY TEST ===\n";
    ClapTrap f("F");
    for (int i = 0; i < 10; i++)
        f.attack("B");
    f.beRepaired(5);

    std::cout << "\n=== ZERO HP TEST ===\n";
    ClapTrap g("G");
    g.takeDamage(10);
    g.beRepaired(5);

    return 0;
}