#include "Serializer.hpp"
#include <iostream>

int main()
{
    Data data;

    data.id = 42;
    data.name = "Irene";

    Data *originalPtr = &data;

    uintptr_t raw = Serializer::serialize(originalPtr);

    Data *recoveredPtr = Serializer::deserialize(raw);

    std::cout << "Original:  " << originalPtr << std::endl;
    std::cout << "Recovered: " << recoveredPtr << std::endl;

    std::cout << recoveredPtr->id << std::endl;
    std::cout << recoveredPtr->name << std::endl;

    return 0;
}