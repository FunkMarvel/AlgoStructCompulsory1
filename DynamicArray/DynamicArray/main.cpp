#include <algorithm>
#include <iostream>
#include "DynamicArray.h"

using namespace std;

void LinearSort(DynamicArray<int>& Arr);



void BinarySort(DynamicArray<int>& Arr);
void selectionSort(DynamicArray<int> &arr);

void BubbleSort(DynamicArray<int> arr);
bool CompareBubbleSort(int a, int b);



int main()
{
    DynamicArray<int> Array = {3, 2, 1,7,9,19,55};

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
     //std::cout << Array.RemoveLastElement() << std::endl;
     //std::cout << Array.RemoveLastElement() << std::endl;
    std::cout << Array<< std::endl;
    std::cout << "Size: " << Array.GetSize() << std::endl;
    std::cout << "Capacity: " << Array.GetCapacity() << std::endl;

    //Test
    //cout << DynamicArray<int>::BinarySearch(Array, 4);
    //cout << Array.BinarySearch(5);
    // BinarySort(Array);
    //cout << DynamicArray<int>::LinearSearch(Array,5); //Static Version
    //cout << Array.LinearSearch(5); //Instance Version
    //LinearSort(Array); //Function Version
    
    //cout << DynamicArray<int>::BinarySearch(Array, 5); //Static Version
    //cout << Array.BinarySearch(5); //Instance Version
    //BinarySort(Array); //Function Version

    //selectionSort(Array);
    BubbleSort(Array);
    DynamicArray<int> Array = {3, 3, 5, 1, 2, 17, 5, 3};
    cout << Array << endl;
    Sorters::HeapSort<int>(Array);
    cout << Array << endl;
    
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
void LinearSort(DynamicArray<int>& Arr)
{
    int n = Arr.GetSize();
    int key;
    cin >> key;


    int index = DynamicArray<int>::LinearSearch(Arr, key);

    if (index != -1)
    {
        cout << key << " Is present in the index:" << index << endl;
    }
    else
    {
        cout << " Is MISSING from the index!" << endl;
    }
}
void selectionSort(DynamicArray<int> &arr)
{
    int n = arr.GetSize();
    for (int i = 0;i<= n-2;i++)
    {
        int current = arr[i];
        int currentMin = i;

        //Find the minimal element
        for (int j=i;j < n;j++)
        {
            if (arr[j] < arr[currentMin])
            {
                currentMin = j;
            }
        }
        //swap outside the loop
        swap(arr[currentMin],arr[i]);  
        
    }
    for (int k = 0; k < n; k++)
    {
        cout << arr[k] << " ";
    }

    
}

bool CompareBubbleSort(int a, int b)
{
    //Here i can decided  > if i want it inn a deacreasing order or < increasing order;
  
    return a > b;
}
void BubbleSort(DynamicArray<int> arr)
{
    
    int n = arr.GetSize();
    int TimeSwapped{};
    //sort the elements in an increasing order
    for (int i = 1; i <= n - 1; i++)
    {
        int swapped = 0;
        //Repeated swapping, {5-3-2} - 5->3 - {3,5,2} - 5->2 - {3-2-5} - 3->2 - {2,3,5}
        //With adding -i-1 we decrease the amount times it need to go over.
        for (int j = 0; j <= n - i - 1; j++)
        {
            
            if (CompareBubbleSort(arr[j],arr[j + 1]))
            {
                swap(arr[j + 1], arr[j]);
                swapped = 1;
                
             TimeSwapped++;
            }
            
        }
        if (swapped == 0)
            break;
        
    }
    for (int k = 0; k < n; k++)
    {
        cout << arr[k] << " ";
    }
    cout << endl;
    cout <<"How many Swaps arr needed :" << TimeSwapped << endl;
}

