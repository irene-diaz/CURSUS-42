#include "Array.hpp"
#include <iostream>

int main()
{
    std::cout << "===== EMPTY ARRAY =====" << std::endl;

    Array<int> empty;
    std::cout << "Empty array size: " << empty.size() << std::endl;

    std::cout << "\n===== ARRAY OF SIZE 5 =====" << std::endl;

    Array<int> arr(5);

    for (unsigned int i = 0; i < arr.size(); i++)
        arr[i] = i * 10;

    for (unsigned int i = 0; i < arr.size(); i++)
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;

    std::cout << "\n===== COPY CONSTRUCTOR =====" << std::endl;

    Array<int> copy(arr); // copy of the array

    arr[0] = 999;

    std::cout << "Original array:" << std::endl;
    for (unsigned int i = 0; i < arr.size(); i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    std::cout << "Copied array:" << std::endl;
    for (unsigned int i = 0; i < copy.size(); i++)
        std::cout << copy[i] << " ";
    std::cout << std::endl;

    std::cout << "\n===== ASSIGNMENT OPERATOR =====" << std::endl;

    Array<int> assign; // copy of the array

    assign = arr;

    arr[1] = 777;

    std::cout << "Original array:" << std::endl;
    for (unsigned int i = 0; i < arr.size(); i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    std::cout << "Assigned array:" << std::endl;
    for (unsigned int i = 0; i < assign.size(); i++)
        std::cout << assign[i] << " ";
    std::cout << std::endl;

    std::cout << "\n===== OUT OF BOUNDS =====" << std::endl;
    try
    {
        std::cout << arr[10] << std::endl;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Exception caught: "
                  << e.what() << std::endl;
    }

    std::cout << "\n===== ARRAY OF STRINGS =====" << std::endl;

    Array<std::string> words(3);

    words[0] = "Hello";
    words[1] = "CPP";
    words[2] = "42";

    for (unsigned int i = 0; i < words.size(); i++)
        std::cout << words[i] << std::endl;

    return 0;
}