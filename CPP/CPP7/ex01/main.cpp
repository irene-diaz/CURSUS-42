#include "iter.hpp"

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    size_t length = sizeof(arr) / sizeof(arr[0]);

    iter(arr, length, [](int &n)
         { n *= 2; });

    for (size_t i = 0; i < length; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    return 0;
}