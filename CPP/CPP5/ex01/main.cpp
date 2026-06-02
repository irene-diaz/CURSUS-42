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

        b.signForm(f); // This will throw an exception

        std::cout << f << std::endl;
        Bureaucrat c("Doe", 10);
        c.signForm(f); 
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}