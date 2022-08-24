#include <algorithm>
#include <iostream>
#include "DynamicArray.h"
#include "Sorters.h"

using namespace std;



//searching
void BinarySort(DynamicArray<int>& Arr);
void LinearSort(DynamicArray<int>& Arr);
// sorting algorithm
void selectionSort(DynamicArray<int> &arr);
void BubbleSort(DynamicArray<int> arr);
bool CompareBubbleSort(int a, int b);

void Merge(DynamicArray<int> &arr,int const Left,int const Right,int const Mid);
void MergeSort(DynamicArray<int>&arr, int const Left, int const Right);




int main()
{
    DynamicArray<int> Array = {12, 11, 13,5,6,7};

    // std::cout << "Size: " << Array.GetSize() << std::endl;
    // std::cout << "Capacity: " << Array.GetCapacity() << std::endl;
    //
    // Array.Append(11);
    // std::cout << "Size: " << Array.GetSize() << std::endl;
    // std::cout << "Capacity: " << Array.GetCapacity() << std::endl;
    //
    // Array.Append(12);
    // std::cout << "Size: " << Array.GetSize() << std::endl;
    // std::cout << "Capacity: " << Array.GetCapacity() << std::endl;
    //
    // std::cout << Array << std::endl;
    // std::cout << Array[1] << std::endl;
    //  std::cout << Array.RemoveLastElement() << std::endl;
    //  std::cout << Array.RemoveLastElement() << std::endl;
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

    //BubbleSort(Array);
    cout << Array << endl;
    MergeSort(Array,0,Array.GetSize()-1);
    cout << Array;

    
    return 0;
}


/**
 * \brief Sorting array with BinarySort
 * \param Arr Array to be sorted
 */
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
    cout << arr;

    
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
void MergeSort(DynamicArray<int> &arr, int const Left,int const Right)
{
    if (Left >= Right)
    {
        return;
    }
    int Mid = (Left + Right) / 2;

    MergeSort(arr,Left,Mid);
    MergeSort(arr,Mid+1,Right);
    Merge(arr,Left,Right,Mid);
    
}
void Merge(DynamicArray<int> &arr,int const Left,int const Right,int const Mid)
{
    

    int TempArrayOne = Mid - Left + 1;
    int TempArrayTwo = Right - Mid;
    int *LeftArray = new int [TempArrayOne];
    int *RightArray = new int [TempArrayTwo];

    auto ArrPtr = arr.GetBegin();
    memcpy(LeftArray, ArrPtr, TempArrayOne*sizeof(LeftArray[0]));
    memcpy(RightArray,ArrPtr+Mid,TempArrayTwo*sizeof(RightArray[0]));
    

    int IndexOfTempArrayOne = 0;
    int IndexOfTempArrayTwo = 0;
    int indexOfMergedArray = Left;


    while (IndexOfTempArrayOne < TempArrayOne && IndexOfTempArrayTwo < TempArrayTwo)
        if (LeftArray[IndexOfTempArrayOne] <= RightArray[IndexOfTempArrayTwo])
        {
            arr[indexOfMergedArray] = LeftArray[IndexOfTempArrayOne];
            IndexOfTempArrayOne++;
        }
        else
        {
            arr[indexOfMergedArray] = RightArray[IndexOfTempArrayTwo];
            IndexOfTempArrayTwo++;
        }
    indexOfMergedArray++;

    while (IndexOfTempArrayOne < TempArrayOne)
    {
        arr[indexOfMergedArray] = LeftArray[IndexOfTempArrayOne];
    IndexOfTempArrayOne++;
    indexOfMergedArray++;
    }
    while (IndexOfTempArrayTwo < TempArrayTwo)
    {
        arr[indexOfMergedArray] = RightArray[IndexOfTempArrayTwo];
        IndexOfTempArrayTwo++;
        indexOfMergedArray++; 
    }
    
    delete[] LeftArray;
    delete[] RightArray;

    
}