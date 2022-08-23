#include <algorithm>
#include <iostream>
#include "DynamicArray.h"

using namespace std;


void BinarySort(DynamicArray<int>& Arr);


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
    std::cout << Array.RemoveLastElement() << std::endl;
    std::cout << Array.RemoveLastElement() << std::endl;
    std::cout << Array.RemoveLastElement() << std::endl;
    std::cout << Array<< std::endl;
    std::cout << "Size: " << Array.GetSize() << std::endl;
    std::cout << "Capacity: " << Array.GetCapacity() << std::endl;

    //Test
    cout << DynamicArray<int>::BinarySearch(Array, 5);
    cout << Array.BinarySearch(5);
    // BinarySort(Array);
    return 0;
}


void BinarySort(DynamicArray<int>& Arr)
{
    int n = Arr.GetSize();
    int key;
    cin >> key;

    int index = DynamicArray<int>::BinarySearch(Arr, key);

    if (index != -1)
    {
        cout << key << " Is present in the index:" << index << endl;
    }
    else
    {
        cout << " Is MISSING from the index!" << endl;
    }
}
