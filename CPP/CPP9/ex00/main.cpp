#include "BitcoinExchange.hpp"

/*int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <data_file>" << std::endl;
        return 1;
    }

    BitcoinExchange btc;
    btc.parseData(argv[1]);
    btc.printData();

    return 0;
}*/

int main()
{
    BitcoinExchange btc;
    btc.parseData("data.csv");
    btc.printData();

    /*std::string date = "2023-01-01";
    double amount = 100.0;
    btc.printPrice(date, amount);*/

    return 0;
}