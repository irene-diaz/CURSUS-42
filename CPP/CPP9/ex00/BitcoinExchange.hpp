#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <cstdlib>

class BitcoinExchange
{
private:
    std::map<std::string, double> _data;
    double getExchangeRate(const std::string &date) const;
    // void printData() const;

public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    ~BitcoinExchange();

    void parseData(const std::string &filename);
    void printPrice(const std::string &date, double value) const;
};

#endif