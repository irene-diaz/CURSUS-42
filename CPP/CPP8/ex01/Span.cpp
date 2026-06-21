#include "Span.hpp"

Span::Span(unsigned int N) : _N(N) {}

Span::Span(const Span &other) : _N(other._N), _numbers(other._numbers) {}

Span &Span::operator=(const Span &other)
{
    if (this != &other)
    {
        _N = other._N;
        _numbers = other._numbers;
    }
    return *this;
}

Span::~Span() {}

void Span::addNumber(int number)
{
    if (_numbers.size() >= _N)
        throw std::runtime_error("Span is full");
    _numbers.push_back(number);
}

unsigned int Span::shortestSpan() const
{
    if (_numbers.size() < 2)
        throw std::runtime_error("Not enough numbers to find a span");

    // Create a copy of the numbers
    std::vector<int> sortedNumbers = _numbers;
    // Sort the numbers in ascending order
    std::sort(sortedNumbers.begin(), sortedNumbers.end());

    // Find the minimum span by comparing adjacent numbers
    unsigned int minSpan = UINT_MAX;
    for (size_t i = 1; i < sortedNumbers.size(); ++i)
    {
        // Calculate the span between adjacent numbers
        unsigned int span = sortedNumbers[i] - sortedNumbers[i - 1];
        // Update minSpan if the current span is smaller
        if (span < minSpan)
            minSpan = span;
    }
    // Return the minimum span found
    return minSpan;
}

unsigned int Span::longestSpan() const
{
    if (_numbers.size() < 2)
        throw std::runtime_error("Not enough numbers to find a span");

    // Find the minimum and maximum numbers in the vector
    int minNumber = *std::min_element(_numbers.begin(), _numbers.end());
    int maxNumber = *std::max_element(_numbers.begin(), _numbers.end());

    return static_cast<unsigned int>(maxNumber - minNumber);
}