#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    BitcoinExchange bitcoinExchange;
    bitcoinExchange.parseData("data.csv");

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    std::string line;

    // Saltar la cabecera
    std::getline(inputFile, line);

    while (std::getline(inputFile, line))
    {
        std::stringstream ss(line);

        std::string date;
        double value;

        if (std::getline(ss, date, '|') && ss >> value)
        {
            bitcoinExchange.printPrice(date, value);
        }
    }
}