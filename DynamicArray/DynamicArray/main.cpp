#include <iostream>
#include "DynamicArray.h"

int main()
{
    DynamicArray<int> Array{3, 4, 5};
    Array.Append(11);
    Array.Append(12);
    std::cout << Array[0] << std::endl;
    std::cout << Array[1] << std::endl;

    std::cout << Array[1] << std::endl;
    return 0;
}
