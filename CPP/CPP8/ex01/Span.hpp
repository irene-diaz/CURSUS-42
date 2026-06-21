#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <climits>

class Span
{
public:
    Span(unsigned int N);
    Span(const Span &other);
    Span &operator=(const Span &other);
    ~Span();

    template <typename Iterator>
    void addRange(Iterator begin, Iterator end);

    void addNumber(int number);
    unsigned int shortestSpan() const;
    unsigned int longestSpan() const;

private:
    unsigned int _N;
    std::vector<int> _numbers;
};

template <typename Iterator>
// add many numbers from a range defined by two iterators
void Span::addRange(Iterator begin, Iterator end)
{
    while (begin != end)
    {
        if (_numbers.size() >= _N)
            throw std::runtime_error("Span is full");

        _numbers.push_back(*begin);
        ++begin;
    }
}

#endif
