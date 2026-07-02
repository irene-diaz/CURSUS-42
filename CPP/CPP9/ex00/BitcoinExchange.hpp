#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <sstream>

class BitcoinExchange
{
private:
    std::map<std::string, double> _data;

public:
    BitcoinExchange();
    ~BitcoinExchange();
    void parseData(const std::string &filename);
    void printPrice(const std::string &date, double amount) const;
};

#endif