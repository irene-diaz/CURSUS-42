#include "PmergeMe.hpp"
#include <ctime>

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        std::cerr << "Error" << std::endl;
        return (1);
    }

    PmergeMe sorter;

    try
    {
        for (int i = 1; i < argc; i++)
        {
            std::stringstream ss(argv[i]);
            long number;

            if (!(ss >> number) || !ss.eof())
                throw std::runtime_error("Invalid number");

            if (number < 0 || number > INT_MAX)
                throw std::runtime_error("Number out of range");

            sorter.addNumber(static_cast<int>(number));
        }

        std::cout << "Before: ";
        sorter.printVector();

        std::clock_t startVector = std::clock();
        sorter.sortVector();
        std::clock_t endVector = std::clock();

        std::clock_t startDeque = std::clock();
        sorter.sortDeque();
        std::clock_t endDeque = std::clock();

        std::cout << "After: ";
        sorter.printVector();

        double vectorTime =
            static_cast<double>(endVector - startVector) / CLOCKS_PER_SEC * 1000000.0;

        double dequeTime =
            static_cast<double>(endDeque - startDeque) / CLOCKS_PER_SEC * 1000000.0;

        std::cout << "Time to process a range of "
                  << argc - 1
                  << " elements with std::vector : "
                  << vectorTime
                  << " us"
                  << std::endl;

        std::cout << "Time to process a range of "
                  << argc - 1
                  << " elements with std::deque : "
                  << dequeTime
                  << " us"
                  << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return (1);
    }

    return (0);
}