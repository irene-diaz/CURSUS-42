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

public:
    BitcoinExchange();
    ~BitcoinExchange();

    void parseData(const std::string &filename);
    void printData() const;
    void printPrice(const std::string &date, double value) const;
    double getExchangeRate(const std::string &date) const;
};

#endif