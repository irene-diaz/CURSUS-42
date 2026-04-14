#include "Harl.hpp"

void Harl::debug(void)
{
    std::cout << "[ DEBUG ]\nI love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!" << std::endl;
}

void Harl::info(void)
{
    std::cout << "[ INFO ]\nI cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
}

void Harl::warning(void)
{
    std::cout << "[ WARNING ]\nI think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month." << std::endl;
}

void Harl::error(void)
{
    std::cout << "[ ERROR ]\nThis is unacceptable! I want to speak to the manager now." << std::endl;
}

void Harl::complain(std::string level)
{
    //array of strings corresponding to the levels
    std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

    //array of pointers to member functions
    void (Harl::*functions[])(void) = { 
        &Harl::debug, 
        &Harl::info,
        &Harl::warning, 
        &Harl::error
    };

    int i = 0;
    //find the index of the level in the levels array
    while (i < 4 && levels[i] != level)
        i++;

    //switch statement to call the appropriate function based on the index
    switch (i)
    {
        case 0:
            (this->*functions[0])();
            //fallthrough
        case 1:
            (this->*functions[1])();
            //fallthrough
        case 2:
            (this->*functions[2])();
            //fallthrough
        case 3:
            (this->*functions[3])();
            break;
        default:
            std::cout << "[ Probably complaining about insignificant problems ]\n";
    }
}