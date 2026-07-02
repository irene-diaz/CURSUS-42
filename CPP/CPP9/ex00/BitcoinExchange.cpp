#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::parseData(const std::string &filename)
{
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::getline(file, line); // Skip header

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string date;
        std::string price_str;
        std::getline(ss, date, ',');
        std::getline(ss, price_str);

        try
        {
            double price = std::stod(price_str);
            _data[date] = price;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: Invalid price format in line: " << line << std::endl;
        }
    }

    file.close();
}

void BitcoinExchange::printPrice(const std::string &date, double amount) const
{
    auto it = _data.find(date);
    if (it != _data.end())
    {
        double price = it->second;
        double total = amount * price;
        std::cout << date << " => " << amount << " = " << total << std::endl;
    }
    else
    {
        std::cerr << "Error: Date not found in database." << std::endl;
    }
}