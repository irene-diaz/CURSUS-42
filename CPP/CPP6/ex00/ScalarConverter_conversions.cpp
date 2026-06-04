#include "ScalarConverter.hpp"
#include <iostream>
#include <cmath>
#include <cctype>
#include <climits>

void ScalarConverter::convertToChar(double value)
{
    std::cout << "char: ";
    // Check if the value can be converted to a character
    if (std::isnan(value) || value < 0 || value > 127)
        std::cout << "impossible" << std::endl;
    // Check if the character is displayable
    else if (!std::isprint(static_cast<int>(value)))
        std::cout << "Non displayable" << std::endl;
    else
        std::cout << "'" << static_cast<char>(value) << "'" << std::endl;
}

void ScalarConverter::convertToInt(double value)
{
    std::cout << "int: ";
    // Check if the value can be converted to an integer
    if (std::isnan(value) || value > INT_MAX || value < INT_MIN)
        std::cout << "impossible" << std::endl;
    else
        std::cout << static_cast<int>(value) << std::endl;
}

void ScalarConverter::convertToFloat(double value)
{
    std::cout << "float: ";
    // Check if the value can be converted to a float
    if (std::isnan(value))
        std::cout << "nanf" << std::endl;
    // Check if the value is positive or negative infinity
    else if (std::isinf(value))
        std::cout << (value > 0 ? "+inff" : "-inff") << std::endl;
    else
        std::cout << static_cast<float>(value) << "f" << std::endl;
}

void ScalarConverter::convertToDouble(double value)
{
    std::cout << "double: ";
    // Check if the value can be converted to a double
    if (std::isnan(value))
        std::cout << "nan" << std::endl;
    // Check if the value is positive or negative infinity
    else if (std::isinf(value))
        std::cout << (value > 0 ? "+inf" : "-inf") << std::endl;
    else
        std::cout << value << std::endl;
}
