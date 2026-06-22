#ifndef MUTANSTACK_HPP
#define MUTANSTACK_HPP

#include <stack>
#include <vector>

template <typename T>
// MutantStack inherits from std::stack and provides iterator access to the underlying container.
class MutantStack : public std::stack<T>
{
public:
    MutantStack() {}
    MutantStack(const MutantStack &other) : std::stack<T>(other) {}
    MutantStack &operator=(const MutantStack &other)
    {
        std::stack<T>::operator=(other);
        return *this;
    }
    ~MutantStack() {}

    // container_type is a typedef for the underlying container type used by std::stack (by default, std::deque).
    typedef typename std::stack<T>::container_type::iterator iterator;

    iterator begin()
    {
        return this->c.begin();
    }

    iterator end()
    {
        return this->c.end();
    }
};

#endif