#include "Span.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <list>

int main()
{
    Span sp = Span(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    std::cout << sp.shortestSpan() << std::endl;
    std::cout << sp.longestSpan() << std::endl;
    return 0;
}

/*int main()
{
    std::cout << "===== SUBJECT TEST =====" << std::endl;
    {
        Span sp(5);

        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);

        std::cout << "Shortest Span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest Span: " << sp.longestSpan() << std::endl;
    }

    std::cout << "\n===== TEST: NOT ENOUGH NUMBERS =====" << std::endl;
    {
        try
        {
            Span sp(5);
            sp.addNumber(10);

            std::cout << sp.shortestSpan() << std::endl;
        }
        catch (std::exception &e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    std::cout << "\n===== TEST: SPAN WITH EXACTLY TWO NUMBERS =====" << std::endl;
    {
        Span sp(2);
        sp.addNumber(10);
        sp.addNumber(20);

        std::cout << "Shortest Span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest Span: " << sp.longestSpan() << std::endl;
    }

    std::cout << "\n===== TEST: ALL NUMBERS ARE THE SAME =====" << std::endl;
    {
        Span sp(5);
        sp.addNumber(10);
        sp.addNumber(10);
        sp.addNumber(10);

        std::cout << "Shortest Span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest Span: " << sp.longestSpan() << std::endl;
    }

    std::cout << "\n===== TEST: NEGATIVE NUMBERS =====" << std::endl;
    {
        Span sp(5);
        sp.addNumber(-10);
        sp.addNumber(-20);
        sp.addNumber(-30);

        std::cout << "Shortest Span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest Span: " << sp.longestSpan() << std::endl;
    }

    std::cout << "\n===== TEST: OVERFLOW =====" << std::endl;
    {
        try
        {
            Span sp(3);
            sp.addNumber(1);
            sp.addNumber(2);
            sp.addNumber(3);
            sp.addNumber(4);
        }
        catch (std::exception &e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    std::cout << "\n===== TEST: ADD RANGE =====" << std::endl;
    {
        Span sp(10000);

        std::vector<int> v;
        for (int i = 0; i < 10000; i++)
            v.push_back(i);

        sp.addRange(v.begin(), v.end());

        std::cout << "Shortest Span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest Span: " << sp.longestSpan() << std::endl;
    }

    std::cout << "\n===== TEST: PARTIAL RANGE =====" << std::endl;
    {
        Span sp(10000);

        std::vector<int> v;
        for (int i = 0; i < 5000; i++)
            v.push_back(i);

        sp.addRange(v.begin(), v.end());

        std::cout << "Shortest Span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest Span: " << sp.longestSpan() << std::endl;
    }

    std::cout << "\n===== TEST: DIFFERENT CONTAINER =====" << std::endl;
    {
        Span sp(10000);

        std::list<int> l;
        for (int i = 0; i < 10000; i++)
            l.push_back(i);

        sp.addRange(l.begin(), l.end());

        std::cout << "Shortest Span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest Span: " << sp.longestSpan() << std::endl;
    }

    std::cout << "\n===== RANDOM LARGE TEST =====" << std::endl;
    {
        Span sp(10000);

        // generate random numbers(change numbers in each run)
        std::srand(std::time(NULL));

        std::vector<int> v;
        for (int i = 0; i < 10000; i++)
            v.push_back(std::rand());

        // insert the numbers into the Span object using addRange
        sp.addRange(v.begin(), v.end());

        std::cout << "Shortest Span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest Span: " << sp.longestSpan() << std::endl;
    }

    return 0;
}*/