#include "BitcoinExchange.hpp"

bool isValidDate(const std::string &date)
{
    // Check if the date is in the format YYYY-MM-DD
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (year < 2009 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;

    if (month == 2)
    {
        bool leap = (year % 4 == 0 && year % 100 != 0) ||
                    (year % 400 == 0);

        if ((leap && day > 29) || (!leap && day > 28))
            return false;
    }

    return true;
}
int main(int argc, char **argv)
{
    // Check if the user provided the correct number of arguments
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    // Create an instance of BitcoinExchange and parse the data from the CSV file
    BitcoinExchange bitcoinExchange;
    bitcoinExchange.parseData("data.csv");

    // Open the input file provided by the user and check if it was opened successfully
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    // create a string to store each line of the input file
    std::string line;

    // skip the first line of the input file (header)
    std::getline(inputFile, line);

    // read each line of the input file, extract the date and value, and print the price of Bitcoin for that date and value
    while (std::getline(inputFile, line))
    {
        // create a stringstream to parse the line
        std::stringstream ss(line);

        std::string date;
        double value;

        // extract the date and value from the line using the stringstream

        if (!std::getline(ss, date, '|') || !(ss >> value))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        // Remove leading space after '|'
        if (!date.empty() && date[date.size() - 1] == ' ')
            date.erase(date.size() - 1);

        // Validate the date and value, and print the price of Bitcoin for that date and value
        if (!isValidDate(date))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        // Check if the value is a positive number
        if (value < 0)
        {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }

        // Check if the value is too large (greater than 1000)
        if (value > 1000)
        {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        // Print the price of Bitcoin for the given date and value
        bitcoinExchange.printPrice(date, value);
    }

    return 0;
}