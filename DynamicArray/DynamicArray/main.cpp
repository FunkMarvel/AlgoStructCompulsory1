#include <iostream>
#include "DynamicArray.h"
#include "Sorters.h"

using namespace std;


//searching
void BinarySort(DynamicArray<int>& Arr);
void LinearSort(DynamicArray<int>& Arr);

int main()
{
    DynamicArray<int> Array = {14, 6, 16, 3, 13, 20, 18, 1, 10, 5, 10, 3, 17, 2, 12, 4, 19, 7, 15, 8, 7, 11};
    DynamicArray<int> TestArray = Array;
    cout << "Selection sort:" << endl;
    cout << "Unsorted: " << TestArray << endl;
    Sorters::SelectionSort(TestArray);
    cout << "Sorted: " << TestArray << endl << endl;
    TestArray = Array;

    cout << "Bubble sort:" << endl;
    cout << "Unsorted: " << TestArray << endl;
    cout << "num swaps: " << Sorters::BubbleSort(TestArray) << endl;
    cout << "Sorted: " << TestArray << endl << endl;
    TestArray = Array;

    cout << "Merge sort:" << endl;
    cout << "Unsorted: " << TestArray << endl;
    Sorters::MergeSort(TestArray);
    cout << "Sorted: " << TestArray << endl << endl;
    TestArray = Array;

    cout << "Quick sort:" << endl;
    cout << "Unsorted: " << TestArray << endl;
    Sorters::QuickSort(TestArray, 0, Array.GetSize() - 1);
    cout << "Sorted: " << TestArray << endl << endl;
    TestArray = Array;

    cout << "Heap sort:" << endl;
    cout << "Unsorted: " << TestArray << endl;
    Sorters::HeapSort(TestArray);
    cout << "Sorted: " << TestArray << endl << endl;
    TestArray = Array;

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
