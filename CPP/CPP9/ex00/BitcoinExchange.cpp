#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    _data = other._data;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
    {
        _data = other._data;
    }
    return *this;
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

// Function to print the price of Bitcoin for a given date and value
void BitcoinExchange::printPrice(const std::string &date, double value) const
{
    double exchangeRate = getExchangeRate(date);
    if (exchangeRate == -1)
    {
        std::cerr << "Error: no exchange rate found for date " << date << std::endl;
        return;
    }

    double result = value * exchangeRate;
    std::cout << date << " => " << value << " = " << result << std::endl;
}

// Function to get the exchange rate for a given date
double BitcoinExchange::getExchangeRate(const std::string &date) const
{
    std::map<std::string, double>::const_iterator it = _data.lower_bound(date);

    // Case 1: Exact date
    if (it != _data.end() && it->first == date)
        return it->second;

    // Case 2: Date before the first one
    if (it == _data.begin())
        return -1;

    // Case 3: Date after the last one
    if (it == _data.end())
    {
        --it;
        return it->second;
    }

    // Case 4: Between two dates
    --it;
    return it->second;
}

/*void BitcoinExchange::printData() const
{
    std::map<std::string, double>::const_iterator it;

    for (it = _data.begin(); it != _data.end(); ++it)
        std::cout << it->first << " -> " << it->second << std::endl;
}*/