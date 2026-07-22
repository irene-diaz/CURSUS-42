#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other)
{
    *this = other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        _vector = other._vector;
        _deque = other._deque;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

// save the number in both vector and deque, check for duplicates
void PmergeMe::addNumber(int number)
{
    if (std::find(_vector.begin(), _vector.end(), number) != _vector.end())
        throw std::runtime_error("Duplicate number");

    _vector.push_back(number);
    _deque.push_back(number);
}

// VECTOR SPECIFIC FUNCTIONS
void PmergeMe::printVector() const
{
    for (size_t i = 0; i < _vector.size(); i++)
    {
        std::cout << _vector[i] << " ";
    }
    std::cout << std::endl;
}

// Sort pairs of numbers in the vector, the smaller number is placed first
void PmergeMe::sortElementsInPairsVector()
{
    // the last element is a straggler if the size of the vector is odd
    for (size_t i = 0; i + 1 < _vector.size(); i += 2)
    {
        if (_vector[i] > _vector[i + 1])
            std::swap(_vector[i], _vector[i + 1]);
    }
}

void PmergeMe::makePairsVector()
{
    _pairsVector.clear();
    for (size_t i = 0; i + 1 < _vector.size(); i += 2)
    {
        _pairsVector.push_back(std::make_pair(_vector[i], _vector[i + 1]));
    }

    if (_vector.size() % 2 == 1)
    {
        _hasStraggler = true;
        _straggler = _vector.back();
    }
    else
    {
        _hasStraggler = false;
    }
}

/*void PmergeMe::printPairs() const
{
    std::cout << "Pairs:" << std::endl;

    for (size_t i = 0; i < _pairsVector.size(); i++)
    {
        std::cout << "("
                  << _pairsVector[i].first
                  << ", "
                  << _pairsVector[i].second
                  << ")"
                  << std::endl;
    }

    if (_hasStraggler)
        std::cout << "Straggler: " << _straggler << std::endl;
}*/

// Return true if the second element of pair a is less than the second element of pair b
bool PmergeMe::comparePairs(const std::pair<int, int> &a,
                            const std::pair<int, int> &b)
{
    return a.second < b.second;
}

// Sort the pairs in the vector based on the second element of each pair
void PmergeMe::sortPairsVector()
{
    std::sort(_pairsVector.begin(), _pairsVector.end(), comparePairs);
}

void PmergeMe::buildChainsVector()
{
    _mainChainVector.clear();
    _pendingChainVector.clear();

    for (size_t i = 0; i < _pairsVector.size(); i++)
    {
        _mainChainVector.push_back(_pairsVector[i].second);
        _pendingChainVector.push_back(_pairsVector[i].first);
    }
}

void PmergeMe::printChains() const
{
    std::cout << "Main chain: ";
    for (size_t i = 0; i < _mainChainVector.size(); i++)
    {
        std::cout << _mainChainVector[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Pending chain: ";
    for (size_t i = 0; i < _pendingChainVector.size(); i++)
    {
        std::cout << _pendingChainVector[i] << " ";
    }

    std::cout << std::endl;
    std::cout << "Straggler: ";
    if (_hasStraggler)
        std::cout << _straggler << " ";
    else
        std::cout << "None";
    std::cout << std::endl;
}

// Insert the first element of the pending chain into the main chain
void PmergeMe::insertFirstPendingVector()
{
    if (_pendingChainVector.empty())
        return;

    _mainChainVector.insert(_mainChainVector.begin(), _pendingChainVector[0]);
}

void PmergeMe::insertPendingVector()
{
    for (size_t i = 0; i < _jacobsthalOrder.size(); i++)
    {
        size_t index = _jacobsthalOrder[i];

        if (index >= _pendingChainVector.size())
            continue;

        std::vector<int>::iterator pos = std::lower_bound(
            _mainChainVector.begin(),
            _mainChainVector.end(),
            _pendingChainVector[index]);

        _mainChainVector.insert(pos, _pendingChainVector[index]);
    }
}

void PmergeMe::insertStragglerVector()
{
    if (!_hasStraggler)
        return;

    std::vector<int>::iterator pos;

    pos = std::lower_bound(
        _mainChainVector.begin(),
        _mainChainVector.end(),
        _straggler);

    _mainChainVector.insert(pos, _straggler);
}

void PmergeMe::sortVector()
{
    sortElementsInPairsVector();

    makePairsVector();
    // printPairs();
    sortPairsVector();

    // printPairs();
    buildChainsVector();
    // printChains();
    buildJacobsthalOrder(_pendingChainVector.size());

    insertFirstPendingVector();
    insertPendingVector();
    insertStragglerVector();

    _vector = _mainChainVector;
}

// FUNCTION SPECIFIC TO DEQUE
void PmergeMe::printDeque() const
{
    for (size_t i = 0; i < _deque.size(); i++)
    {
        std::cout << _deque[i] << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::sortPairsDeque()
{
    std::sort(_pairsDeque.begin(), _pairsDeque.end(), comparePairs);
}

void PmergeMe::sortElementsInPairsDeque()
{
    for (size_t i = 0; i + 1 < _deque.size(); i += 2)
    {
        if (_deque[i] > _deque[i + 1])
            std::swap(_deque[i], _deque[i + 1]);
    }
}

void PmergeMe::makePairsDeque()
{
    _pairsDeque.clear();
    for (size_t i = 0; i + 1 < _deque.size(); i += 2)
    {
        _pairsDeque.push_back(std::make_pair(_deque[i], _deque[i + 1]));
    }

    if (_deque.size() % 2 == 1)
    {
        _hasStraggler = true;
        _straggler = _deque.back();
    }
    else
    {
        _hasStraggler = false;
    }
}

void PmergeMe::buildChainsDeque()
{
    _mainChainDeque.clear();
    _pendingChainDeque.clear();

    for (size_t i = 0; i < _pairsDeque.size(); i++)
    {
        _mainChainDeque.push_back(_pairsDeque[i].second);
        _pendingChainDeque.push_back(_pairsDeque[i].first);
    }
}
void PmergeMe::insertFirstPendingDeque()
{
    if (_pendingChainDeque.empty())
        return;

    _mainChainDeque.insert(_mainChainDeque.begin(), _pendingChainDeque[0]);
}
void PmergeMe::insertPendingDeque()
{
    for (size_t i = 0; i < _jacobsthalOrder.size(); i++)
    {
        size_t index = _jacobsthalOrder[i];

        if (index >= _pendingChainDeque.size())
            continue;

        std::deque<int>::iterator pos = std::lower_bound(
            _mainChainDeque.begin(),
            _mainChainDeque.end(),
            _pendingChainDeque[index]);

        _mainChainDeque.insert(pos, _pendingChainDeque[index]);
    }
}

void PmergeMe::insertStragglerDeque()
{
    if (!_hasStraggler)
        return;

    std::deque<int>::iterator pos;

    pos = std::lower_bound(
        _mainChainDeque.begin(),
        _mainChainDeque.end(),
        _straggler);

    _mainChainDeque.insert(pos, _straggler);
}

void PmergeMe::sortDeque()
{
    sortElementsInPairsDeque();

    makePairsDeque();
    // printPairs();
    sortPairsDeque();
    // printPairs();

    buildChainsDeque();
    // printChains();
    buildJacobsthalOrder(_pendingChainDeque.size());

    insertFirstPendingDeque();
    insertPendingDeque();
    insertStragglerDeque();

    _deque = _mainChainDeque;
}
void PmergeMe::buildJacobsthalOrder(size_t n)
{
    _jacobsthalOrder.clear();

    if (n <= 1)
        return;

    std::vector<size_t> jacob;
    jacob.push_back(1);
    jacob.push_back(3);

    while (jacob.back() < n)
        jacob.push_back(jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2]);

    std::vector<bool> used(n, false);
    used[0] = true; // el primer pendiente se inserta aparte

    for (size_t i = 1; i < jacob.size(); i++)
    {
        size_t current = jacob[i];

        if (current > n)
            current = n;

        for (size_t j = current; j > jacob[i - 1]; j--)
        {
            size_t index = j - 1;

            if (!used[index])
            {
                _jacobsthalOrder.push_back(index);
                used[index] = true;
            }
        }
    }

    // Añadir los índices que no hayan aparecido
    for (size_t i = 1; i < n; i++)
    {
        if (!used[i])
            _jacobsthalOrder.push_back(i);
    }
}