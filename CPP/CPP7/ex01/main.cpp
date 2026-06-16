#include "iter.hpp"

void multiplyByTwo(int &n)
{
    n *= 2;
}
void print(const int &n)
{
    std::cout << n << std::endl;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    const int arr2[] = {6, 7, 8, 9, 10};
    // Calculate the length of the array(the total size of the array divided by the size of one element)
    size_t length = sizeof(arr) / sizeof(arr[0]);
    size_t length2 = sizeof(arr2) / sizeof(arr2[0]);

    iter(arr, length, multiplyByTwo);
    iter(arr2, length2, print);

    for (size_t i = 0; i < length; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    return 0;
}