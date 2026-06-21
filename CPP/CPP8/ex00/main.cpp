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
    l.push_front(0);

    std::deque<int> d;
    d.push_back(100);
    d.push_back(200);
    d.push_back(300);
    d.push_front(50);

    std::cout << "===== VECTOR =====" << std::endl;
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "===== LIST =====" << std::endl;
    for (std::list<int>::iterator it = l.begin(); it != l.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "===== DEQUE =====" << std::endl;
    for (std::deque<int>::iterator it = d.begin(); it != d.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    try
    {
        std::cout << "\nSearching in vector..." << std::endl;
        std::vector<int>::iterator it1 = easyfind(v, 20);
        std::cout << "Found: " << *it1 << std::endl;

        std::cout << "\nSearching in list..." << std::endl;
        std::list<int>::iterator it2 = easyfind(l, 2);
        std::cout << "Found: " << *it2 << std::endl;

        std::cout << "\nSearching in deque..." << std::endl;
        std::deque<int>::iterator it3 = easyfind(d, 200);
        std::cout << "Found: " << *it3 << std::endl;

        std::cout << "\nSearching for 42..." << std::endl;
        easyfind(v, 42);
    }
    catch (std::exception &e)
    {
        std::cout << "Value not found" << std::endl;
    }

    return 0;
}