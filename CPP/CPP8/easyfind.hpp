#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <stdexcept>

template<typename T, typename U>
typename std::vector<T>::iterator easyfind(std::vector<T> &container, U value)
{
    typename std::vector<T>::iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end())
        throw std::runtime_error("Value not found");
    return it;
}

#endif
