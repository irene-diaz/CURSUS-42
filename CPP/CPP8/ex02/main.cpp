#include "MutantStack.hpp"
#include <iostream>
#include <stack>
int main()
{
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    std::cout << mstack.top() << std::endl; // Output: 17
    mstack.pop();
    std::cout << mstack.size() << std::endl; // Output: 1
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    /*std::cout << *mstack.begin() << std::endl; // Output: 737
    std::cout << *mstack.end() << std::endl;   // Output: 0*/

    // Increment and decrement the iterator to test its functionality
    ++it;
    --it;

    while (it != ite)
    {
        std::cout << *it << std::endl; // Output: 5, 3, 5, 737, 0
        ++it;
    }

    std::stack<int> s(mstack); // Copy constructor from MutanStack to std::stack

    return 0;
}