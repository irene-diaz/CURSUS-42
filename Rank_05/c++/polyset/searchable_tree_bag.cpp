#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag()
{
}

searchable_tree_bag::searchable_tree_bag(
    const searchable_tree_bag &other)
    : tree_bag(other)
{
}

searchable_tree_bag &
searchable_tree_bag::operator=(
    const searchable_tree_bag &other)
{
    tree_bag::operator=(other);
    return *this;
}

searchable_tree_bag::~searchable_tree_bag()
{
}

bool searchable_tree_bag::search(node *root,
                                 int n) const
{
    if (!root)
        return false;

    if (root->value == n)
        return true;

    if (n < root->value)
        return search(root->l, n);

    return search(root->r, n);
}

bool searchable_tree_bag::has(int n) const
{
    return search(tree, n);
}