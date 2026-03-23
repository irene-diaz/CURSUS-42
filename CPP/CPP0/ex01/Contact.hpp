#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>
#include <iostream>
#include <iomanip>

class Contact
{
private:
    std::string firstName;
    std::string lastName;
    std::string nickname;
    std::string phoneNumber;
    std::string darkestSecret;

public:
    Contact();

    void setContact(std::string fn, std::string ln,
                    std::string nn, std::string pn,
                    std::string ds);

    void displayShort(int index);
    void displayFull();

    std::string getFirstName();
    std::string getLastName();
    std::string getNickname();
};

#endif