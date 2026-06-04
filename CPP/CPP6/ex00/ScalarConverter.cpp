#include "ScalarConverter.hpp"
#include <iostream>
#include <iomanip>

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter &)
{
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &)
{
    return *this;
}

ScalarConverter::~ScalarConverter() {}

void ScalarConverter::convert(const std::string &literal)
{
    // Set the output format for floating-point numbers
    std::cout << std::fixed << std::setprecision(1);

    // Handle pseudo-literals (nan, +inf, -inf)
    if (handlePseudoLiterals(literal))
        return;

    double value;
    // Handle literals that are not pseudo-literals and do not represent a char literal
    if (!getDoubleValue(literal, value))
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return;
    }

    // Convert and display the results
    convertToChar(value);
    convertToInt(value);
    convertToFloat(value);
    convertToDouble(value);
}
