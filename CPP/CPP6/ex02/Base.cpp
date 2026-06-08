#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <iostream>
#include <cstdlib>

Base::~Base()
{
}

Base *generate(void)
{
    int random = rand() % 3;

    switch (random)
    {
    case 0:
        return new A();
    case 1:
        return new B();
    case 2:
        return new C();
    default:
        return NULL;
    }
}

void identify(Base *p)
{
    if (dynamic_cast<A *>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B *>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C *>(p))
        std::cout << "C" << std::endl;
    else
        std::cout << "Unknown type" << std::endl;
}

void identify(Base &p)
{
    if (dynamic_cast<A *>(&p))
    {
        std::cout << "A" << std::endl;
        return;
    }
    if (dynamic_cast<B *>(&p))
    {
        std::cout << "B" << std::endl;
        return;
    }
    if (dynamic_cast<C *>(&p))
    {
        std::cout << "C" << std::endl;
        return;
    }

    std::cout << "Unknown" << std::endl;
}