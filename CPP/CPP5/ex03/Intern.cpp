#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern()
{
}

Intern::Intern(const Intern &other)
{
    (void)other;
}
Intern &Intern::operator=(const Intern &other)
{
    (void)other;
    return *this;
}

Intern::~Intern()
{
}
static AForm *createShrubbery(const std::string &target)
{
    return new ShrubberyCreationForm(target);
}

static AForm *createRobotomy(const std::string &target)
{
    return new RobotomyRequestForm(target);
}

static AForm *createPardon(const std::string &target)
{
    return new PresidentialPardonForm(target);
}
AForm *Intern::makeForm(const std::string &formName, const std::string &target)
{
    // create an array of form names and corresponding form creation functions
    static const std::string names[3] = {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"};

    // array of pointers to form creation functions
    static AForm *(*forms[3])(const std::string &) = {
        &createShrubbery,
        &createRobotomy,
        &createPardon};

    // loop through the form names and if a match is found, call the corresponding form creation function
    for (int i = 0; i < 3; i++)
    {
        if (formName == names[i])
        {
            std::cout << "Intern creates " << formName << std::endl;
            return forms[i](target);
        }
    }

    std::cout << "Intern: this form does not exist" << std::endl;
    return NULL;
}
