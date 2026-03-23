#include "Contact.hpp"
#include <iomanip>

// Constructor vacío
Contact::Contact() {}

// Guardar datos
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

/* Función auxiliar para formatear
(si tiene mas de 10 caracteres, eliminamos los sobrantes y ponemos un . al final)*/
static std::string format(std::string str)
{
    if (str.length() > 10)
        return str.substr(0, 9) + ".";
    return str;
}

// Mostrar en tabla(index=contacto)
// setw(n)= el siguiente valor ocupará exactamente n caracteres de ancho
void Contact::displayShort(int index)
{
    std::cout << std::setw(10) << index << "|"
              << std::setw(10) << format(firstName) << "|"
              << std::setw(10) << format(lastName) << "|"
              << std::setw(10) << format(nickname)
              << std::endl;
}

// Mostrar completo
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