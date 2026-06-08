#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    // Seed the random number generator
    std::srand(std::time(NULL));

    std::cout << "=== GENERATE ===" << std::endl;
    Base *obj = generate();

    std::cout << "=== IDENTIFY POINTER ===" << std::endl;
    identify(obj);

    std::cout << "=== IDENTIFY REFERENCE ===" << std::endl;
    identify(*obj);

    delete obj;

    return 0;
}