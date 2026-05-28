#include "Bureaucrat.hpp"

int main()
{
    try
    {
        Bureaucrat b("John", 50);
        std::cout << b << std::endl;

        b.incrementGrade();
        std::cout << b << std::endl;

        b.decrementGrade();
        std::cout << b << std::endl;

        Bureaucrat c("Doe", 151); // This will throw an exception
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}