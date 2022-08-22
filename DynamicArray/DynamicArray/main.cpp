#include <iostream>
#include <vector>
#include "DynamicArray.h"

int main(int argc, char* argv[])
{
    DynamicArray<int> Array{};
    Array.Append(11);
    Array.Append(12);
    std::cout << Array[0] << std::endl;
    std::cout << Array[1] << std::endl;

    std::cout << Array[1] << std::endl;
    return 0;
}
