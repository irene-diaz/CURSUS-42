#include "PhoneBook.hpp"

// Inicializa el estado del phoneBook
PhoneBook::PhoneBook()
{
    index = 0;
    total = 0;
}

// funcion para añadir un contacto
// getLine= lee strings con espacios
// Cuando haya mas de 8 contactos, sobrescribimso el primero y asi sucesivamente
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

// Busca el contacto con el indice x
void PhoneBook::searchContact()
{
    if (total == 0)
    {
        std::cout << "PhoneBook is empty\n";
        return;
    }

    // mostramos los contactos en formato tabla
    for (int i = 0; i < total; i++)
        contacts[i].displayShort(i);

    // Creamos una variable de tipo cadena y guardamos lo que escribamos
    std::string input;
    std::cout << "Index: ";
    std::getline(std::cin, input);

    // Convertir string a entero(para indice real)
    int i = std::stoi(input);

    // control de errores
    if (i < 0 || i >= total)
    {
        std::cout << "Invalid index\n";
        return;
    }

    //mostramos los contactos enteros
    contacts[i].displayFull();
}
