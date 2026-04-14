#include "Weapon.hpp"
#include "HumanA.hpp"
#include "HumanB.hpp"

/*Bob: reference to club
Jim: pointer to club*/
int main()
{
    Weapon club = Weapon("crude spiked club");

    HumanA bob("Bob", club);
    bob.attack();
    club.setType("some other type of club");
    bob.attack();

    Weapon* club2 = new Weapon("crude spiked club");

    HumanB jim("Jim");
    jim.setWeapon(*club2);
    jim.attack();
    club2->setType("some other type of club");
    jim.attack();

    delete club2;

    return 0;
}