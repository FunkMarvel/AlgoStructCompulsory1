#include <algorithm>
#include <iostream>
#include "DynamicArray.h"

using namespace std;


int BinarySort(DynamicArray<int> Arr);



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

//Test

    //DynamicArray<int>::BinarySort(Array);

   // cout << Array.BinarySearch(5);
    cout << BinarySort(Array);
    return 0;
}


int BinarySort(DynamicArray<int> Arr)
{
    
    int n = Arr.GetSize();
    int key;
    cin >> key;
    
    int index = DynamicArray<int>::BinarySearch(Arr,n,key);
    
    if (index != -1)
    {
        cout << key << " Is present in the index:" << index << endl;
    }
    else
    {
        cout << " Is MISSING from the index!" << endl;
    }

    return 0;
}