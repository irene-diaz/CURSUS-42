#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string>

class ScalarConverter
{
private:
    // the constructor, copy constructor, assignment operator, and destructor are private to prevent instantiation of this class
    ScalarConverter();
    ScalarConverter(const ScalarConverter &other);
    ScalarConverter &operator=(const ScalarConverter &other);
    ~ScalarConverter();

    static bool isCharLiteral(const std::string &literal);
    static bool isPseudoLiteral(const std::string &literal);

    static bool handlePseudoLiterals(const std::string &literal);
    static bool getDoubleValue(const std::string &literal, double &value);
    static void convertToChar(double value);
    static void convertToInt(double value);
    static void convertToFloat(double value);
    static void convertToDouble(double value);

public:
    static void convert(const std::string &literal);
};

#endif