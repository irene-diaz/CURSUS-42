#include "Contact.hpp"

// Empty constructor
Contact::Contact() {}

// Save data
void Contact::setContact(std::string fn, std::string ln,
                         std::string nn, std::string pn,
                         std::string ds)
{
    firstName = fn;
    lastName = ln;
    nickname = nn;
    phoneNumber = pn;
    darkestSecret = ds;
}

/* Helper function to format strings
(if it has more than 10 characters, truncate and add a '.' at the end) */
static std::string format(std::string str)
{
    if (str.length() > 10)
        return str.substr(0, 9) + ".";
    return str;
}

// Display in table format (index=contact)
// setw(n)= the next value will occupy exactly n characters in width
void Contact::displayShort(int index)
{
    std::cout << std::setw(10) << index << "|"
              << std::setw(10) << format(firstName) << "|"
              << std::setw(10) << format(lastName) << "|"
              << std::setw(10) << format(nickname)
              << std::endl;
}

// Display full contact details
void Contact::displayFull()
{
    std::cout << "First name: " << firstName << std::endl;
    std::cout << "Last name: " << lastName << std::endl;
    std::cout << "Nickname: " << nickname << std::endl;
    std::cout << "Phone number: " << phoneNumber << std::endl;
    std::cout << "Darkest secret: " << darkestSecret << std::endl;
}

// Getters
std::string Contact::getFirstName() { return firstName; }
std::string Contact::getLastName() { return lastName; }
std::string Contact::getNickname() { return nickname; }
