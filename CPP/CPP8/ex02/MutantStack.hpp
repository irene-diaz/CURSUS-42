#ifndef MUTANSTACK_HPP
#define MUTANSTACK_HPP

#include <stack>
#include <vector>

template <typename T>
class MutanStack : public std::stack<T>
{
public:
    MutanStack();
    MutanStack(const MutanStack &other);
    MutanStack &operator=(const MutanStack &other);
    ~MutanStack();

    void push(const T &value);
    void pop();
    T &top();
    const T &top() const;
    size_t size() const;
    bool empty() const;

private:
    std::vector<T> _container;
};

#endif 