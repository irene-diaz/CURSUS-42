#ifndef SET_HPP
#define SET_HPP

#include "searchable_bag.hpp"
class set
{
private:
    searchable_bag &bag;
    set();
    set(const set &source);
    set &operator=(const set &source);

public:
    set(searchable_bag &s_bag);
    bool has(int) const;
    void insert(int);
    void insert(int *, int);
    void clear();
    void print() const;

    const searchable_bag &get_bag() const;
    ~set();
};
#endif