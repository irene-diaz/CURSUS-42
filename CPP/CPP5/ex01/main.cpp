#include "Form.hpp"
#include "Bureaucrat.hpp"

int main()
{
    try
    {
        Bureaucrat b("John", 50);
        Form f("Top Secret", 30, 20);

        std::cout << b << std::endl;
        std::cout << f << std::endl;

        b.signForm(f);
        std::cout << f << std::endl;

        Bureaucrat c("Doe", 150);
        c.signForm(f); // This will throw an exception
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}