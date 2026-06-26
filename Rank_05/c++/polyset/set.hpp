#ifndef SET_HPP
#define SET_HPP
#include "searchable_bag.hpp"

// set no almacena datos; simplemente utiliza un searchable_bag y evita insertar elementos duplicados.
class set
{
    /*ALL OF THE FOLLOWING ARE PRIVATE MEMBERS OF THE CLASS BECAUSE THEY ARE
    NOT INTENDED TO BE USED BY THE CLIENT CODE*/
private:
    // keep a reference to the bag that is being wrapped
    searchable_bag &bag;
    // disabled (C++98 equivalent of = delete)
    set();
    set(const set &source);
    set &operator=(const set &source);

public:
    set(searchable_bag &s_bag); // constructor that takes a reference to a searchable_bag
    bool has(int n) const;      // returns true if the value is in the set, false otherwise
    void insert(int);           // inserts the value into the set if it is not already present
    void insert(int *, int);    // inserts the values from the array into the set if they are not already present
    void print() const;         // prints the values in the set to the console
    void clear();               // removes all values from the set

    const searchable_bag &get_bag() const; // returns a reference to the underlying bag

    ~set();
};
#endif
