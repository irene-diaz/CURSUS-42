#include "ScalarConverter.hpp"
#include <iostream>
#include <cerrno>
#include <cstdlib>
#include <cctype>

bool ScalarConverter::isCharLiteral(const std::string &literal)
{
    if (literal.length() == 1 && !std::isdigit(literal[0]))
        return true;
    else
        return false;
}

bool ScalarConverter::isPseudoLiteral(const std::string &literal)
{
    if (literal == "nan" || literal == "nanf" || literal == "+inf" || literal == "-inf" || literal == "+inff" || literal == "-inff")
        return true;
    else
        return false;
}

// Handle pseudo-literals and display the appropriate output
bool ScalarConverter::handlePseudoLiterals(const std::string &literal)
{
    // Check if the literal is a pseudo-literal
    if (!isPseudoLiteral(literal))
        return false;

    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;

    // Display the appropriate output for float and double pseudo-literals
    if (literal[0] == '-')
    {
        std::cout << "float: -inff" << std::endl;
        std::cout << "double: -inf" << std::endl;
    }
    else if (literal[0] == '+')
    {
        std::cout << "float: +inff" << std::endl;
        std::cout << "double: +inf" << std::endl;
    }
    else
    {
        std::cout << "float: nanf" << std::endl;
        std::cout << "double: nan" << std::endl;
    }
    return true;
}

// Convert the literal to a double value. If the conversion fails, return false.
bool ScalarConverter::getDoubleValue(const std::string &literal, double &value)
{
    if (isCharLiteral(literal))
    {
        value = static_cast<double>(literal[0]);
        return true;
    }

    char *end = NULL;
    errno = 0;
    // Use strtod to convert the string to a double. This function will set errno if the conversion fails or if the value is out of range.
    value = std::strtod(literal.c_str(), &end);

    if (errno == ERANGE)
        return false;
    return true;
}
