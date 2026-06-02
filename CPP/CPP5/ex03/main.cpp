#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main()
{
    Intern someRandomIntern;
    Bureaucrat boss("Boss", 1);

    AForm *shrub = someRandomIntern.makeForm("shrubbery creation", "home");
    AForm *robot = someRandomIntern.makeForm("robotomy request", "Bender");
    AForm *pardon = someRandomIntern.makeForm("presidential pardon", "Alice");
    AForm *wrong = someRandomIntern.makeForm("unknown", "X");

    std::cout << "\n=== SIGN ===\n";
    boss.signForm(*shrub);
    boss.signForm(*robot);
    boss.signForm(*pardon);

    std::cout << "\n=== EXECUTE ===\n";
    boss.executeForm(*shrub);
    boss.executeForm(*robot);
    boss.executeForm(*pardon);

    delete shrub;
    delete robot;
    delete pardon;
    delete wrong;
}