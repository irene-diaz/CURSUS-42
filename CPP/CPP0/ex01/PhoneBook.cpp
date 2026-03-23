#include "PhoneBook.hpp"

// Initialize the state of the PhoneBook
PhoneBook::PhoneBook()
{
    index = 0;
    total = 0;
}

// Function to add a contact
// getLine = reads strings with spaces
// When there are more than 8 contacts, overwrite the first one and so on
void PhoneBook::addContact()
{
    std::string fn, ln, nn, pn, ds;

    std::cout << "First name: ";
    std::getline(std::cin, fn);

    std::cout << "Last name: ";
    std::getline(std::cin, ln);

    std::cout << "Nickname: ";
    std::getline(std::cin, nn);

    std::cout << "Phone number: ";
    std::getline(std::cin, pn);

    std::cout << "Darkest secret: ";
    std::getline(std::cin, ds);

    if (fn.empty() || ln.empty() || nn.empty() || pn.empty() || ds.empty())
    {
        std::cout << "Error: empty field\n";
        return;
    }

    contacts[index].setContact(fn, ln, nn, pn, ds);

    index = (index + 1) % 8;

    if (total < 8)
        total++;
}

// Search for the contact with index x
void PhoneBook::searchContact()
{
    if (total == 0)
    {
        std::cout << "PhoneBook is empty\n";
        return;
    }

    std::cout << std::setw(10) << "index" << "|"
              << std::setw(10) << "first name" << "|"
              << std::setw(10) << "last name" << "|"
              << std::setw(10) << "nickname"
              << std::endl;

    // Display contacts in table format
    for (int i = 0; i < total; i++)
        contacts[i].displayShort(i);

    // Create a string variable and store the input
    std::string input;
    std::cout << "Index: ";
    std::getline(std::cin, input);

    std::istringstream iss(input);
    int i;
    if (!(iss >> i))
    {
        std::cout << "Error: Input is not a valid number\n";
        return;
    }

    // Error control
    if (i < 0 || i >= total)
    {
        std::cout << "Invalid index\n";
        return;
    }

    // Display full contact details
    contacts[i].displayFull();
}
