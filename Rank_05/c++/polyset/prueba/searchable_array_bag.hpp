#ifndef SEARCHABLE_ARRAY_BAG_HPP
#define SEARCHABLE_ARRAY_BAG_HPP
#include "array_bag.hpp"
#include "searchable_bag.hpp"

class searchable_array_bag : array_bag, searchable_bag
{
    searchable_array_bag();
    searchable_array_bag(const searchable_array_bag &other);
    searchable_array_bag &operator=(const searchable_array_bag &other);
    ~searchable_array_bag();

    bool has(int n) const;
};
#endif