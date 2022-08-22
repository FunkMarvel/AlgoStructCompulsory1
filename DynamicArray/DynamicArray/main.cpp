#include <iostream>
#include "DynamicArray.h"

int main()
{
    DynamicArray<int> Array = {3, 4, 5};

    std::cout << "Size: " << Array.GetSize() << std::endl;
    std::cout << "Capacity: " << Array.GetCapacity() << std::endl;
    
    Array.Append(11);
    std::cout << "Size: " << Array.GetSize() << std::endl;
    std::cout << "Capacity: " << Array.GetCapacity() << std::endl;
    
    Array.Append(12);
    std::cout << "Size: " << Array.GetSize() << std::endl;
    std::cout << "Capacity: " << Array.GetCapacity() << std::endl;
    
    std::cout << Array << std::endl;
    std::cout << Array[1] << std::endl;

    std::cout << Array[1] << std::endl;
    return 0;
}
