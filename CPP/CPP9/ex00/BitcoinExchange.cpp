#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::parseData(const std::string &filename)
{
    std::ifstream file(filename.c_str());

    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    // create a empty line string to store each line of the file
    std::string line;
    // read the first line of the file to skip the header
    std::getline(file, line);

    while (std::getline(file, line))
    {
        // separe the line into date and price using a stringstream
        std::stringstream ss(line);

        std::string date;
        std::string priceString;

        std::getline(ss, date, ',');
        std::getline(ss, priceString);

        // convert the price string to a double using std::atof
        double price = std::atof(priceString.c_str());

        // store the date and price in the map
        _data[date] = price;
    }
}

void BitcoinExchange::printPrice(const std::string &date, double value) const
{
    double exchangeRate = getExchangeRate(date);
    if (exchangeRate == -1)
    {
        std::cerr << "Error: no exchange rate found for date " << date << std::endl;
        return;
    }

    double price = value * exchangeRate;
    std::cout << date << " => " << value << " = " << price << std::endl;
}

void BitcoinExchange::printData() const
{
    std::map<std::string, double>::const_iterator it;

    for (it = _data.begin(); it != _data.end(); ++it)
        std::cout << it->first << " -> " << it->second << std::endl;
}