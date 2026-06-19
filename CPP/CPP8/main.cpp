#include "easyfind.hpp"

#include <iostream>
#include <vector>
#include <list>
#include <deque>

int main()
{
    std::vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    std::list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    std::deque<int> d;
    d.push_back(100);
    d.push_back(200);
    d.push_back(300);

    try
    {
        std::vector<int>::iterator it = easyfind(v, 20);
        std::cout << "Found in vector: " << *it << std::endl;

        std::list<int>::iterator it2 = easyfind(l, 2);
        std::cout << "Found in list: " << *it2 << std::endl;

        std::deque<int>::iterator it3 = easyfind(d, 200);
        std::cout << "Found in deque: " << *it3 << std::endl;

        easyfind(v, 42);
    }
    catch (std::exception &e)
    {
        std::cout << "Value not found" << std::endl;
    }

    return 0;
}
