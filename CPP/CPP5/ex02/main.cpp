#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
    try
    {
        Bureaucrat boss("Boss", 1);
        Bureaucrat worker("Worker", 150);

        ShrubberyCreationForm shrub("garden");
        RobotomyRequestForm robot("Bender");
        PresidentialPardonForm pardon("Marvin");

        std::cout << "\n=== EXECUTE UNSIGNED ===\n";
        boss.executeForm(shrub);

        std::cout << "\n=== SIGN TEST ===\n";
        worker.signForm(pardon); // should fail because worker's grade is too low
        boss.signForm(pardon); // should succeed because boss's grade is high enough

        std::cout << "\n=== EXECUTE TEST ===\n";
        boss.executeForm(pardon);

        std::cout << "\n=== ROBOTOMY TEST ===\n";
        boss.signForm(robot);

        for (int i = 0; i < 5; i++)
            boss.executeForm(robot);

        std::cout << "\n=== SHRUBBERY TEST ===\n";
        boss.signForm(shrub);
        boss.executeForm(shrub);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}