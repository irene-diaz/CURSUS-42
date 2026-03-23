#include "PhoneBook.hpp"
#include <iostream>
#include <string>

int main()
{
    PhoneBook phoneBook;      // Creamos el objeto PhoneBook
    std::string command;

    while (true)
    {
        std::cout << "Enter command (ADD, SEARCH, EXIT): ";
        std::getline(std::cin, command);

        if (command == "ADD")
            phoneBook.addContact();
        else if (command == "SEARCH")
            phoneBook.searchContact();
        else if (command == "EXIT")
            break;
        else
            std::cout << "Unknown command\n";
    }

    return 0;
}