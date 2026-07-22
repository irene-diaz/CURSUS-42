#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>
#include <sstream>
#include <climits>
#include <algorithm>

class PmergeMe
{
private:
    static bool comparePairs(const std::pair<int, int> &a, const std::pair<int, int> &b);
    std::vector<int> _vector;
    std::deque<int> _deque;

    std::vector<std::pair<int, int> > _pairsVector;
    std::vector<int> _mainChainVector;
    std::vector<int> _pendingChainVector;

    std::deque<std::pair<int, int> > _pairsDeque;
    std::deque<int> _mainChainDeque;
    std::deque<int> _pendingChainDeque;

    std::vector<size_t> _jacobsthalOrder;

    bool _hasStraggler;
    int _straggler;

    // vector
    void sortPairsVector();
    void buildChainsVector();
    void insertFirstPendingVector();
    void insertPendingVector();
    void insertStragglerVector();
    void sortElementsInPairsVector();
    void makePairsVector();

    // deque
    void sortPairsDeque();
    void buildChainsDeque();
    void sortElementsInPairsDeque();
    void makePairsDeque();
    void insertPendingDeque();
    void insertStragglerDeque();
    void insertFirstPendingDeque();

    void buildJacobsthalOrder(size_t n);

public:
    PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe();

    void addNumber(int number);

    // depuracion
    void printVector() const;
    void printDeque() const;
    // void printPairs() const;
    void printChains() const;
    void sortVector();
    void sortDeque();
};

#endif