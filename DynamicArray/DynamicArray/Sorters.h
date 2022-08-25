#pragma once
#include "DynamicArray.h"

/**
 * \brief Library of sorting algorithms
 */
namespace Sorters
{
    template <typename T>
    void HeapSort(DynamicArray<T>& Array);

    template <typename T>
    void SelectionSort(DynamicArray<T>& Array);

    template <typename T>
    int BubbleSort(DynamicArray<T>& Array);
    
    template <typename T>
    void MergeSort(DynamicArray<T>&arr);
}

/**
 * \brief Internal support functions for Sorters-library.
 */
namespace SortersHelpers
{
    template <typename T>
    bool CompareBubbleSort(T a, T b);

    template <typename T>
    void SiftDown(DynamicArray<T>& Array, size_t NodeToSift);

    template <typename T>
    void Heapify(DynamicArray<T>& Array);

    template <typename T>
    void Merge(DynamicArray<T> &arr,DynamicArray<T> &LeftArray, DynamicArray<T> &RightArray);
}

/**
 * \brief Sorting input array in ascending order using Heap sort.
 * \tparam T Data type of elements in array.
 * \param Array Array to sort.
 */
template <typename T>
void Sorters::HeapSort(DynamicArray<T>& Array)
{
    // Organize Array into Min-Heap:
    SortersHelpers::Heapify(Array);

    // Create Temp array for storing sorted values:
    DynamicArray<T> TempArray{};
    auto NumElements = Array.GetSize(); // saving amount of elements to sort.
    TempArray.Expand(NumElements); // reserving necessary amount of memory.

    for (int i = 0; i < NumElements - 1; ++i) // looping until there is only one element left.
    {
        TempArray.Append(Array[0]); // adding smallest element to front of temp array.
        Array[0] = Array.RemoveLastElement(); // shifting last heap element to be new root.
        SortersHelpers::SiftDown(Array, 0); // sifting down root to restore heap property.
    }
    TempArray.Append(Array.RemoveLastElement()); // moving final element.
    Array = TempArray; // populating Array from temp array by copy assignment.
}

/**
 * \brief Performs selection sort on given array.
 * \tparam T Data type of elements in array.
 * \param Array Dynamic Array to sort.
 */
template <typename T>
void Sorters::SelectionSort(DynamicArray<T>& Array)
{
    const int NumElements = static_cast<const int>(Array.GetSize());
    for (int i = 0; i <= NumElements - 2; i++)
    {
        int CurrentMin = i;

        //Find the minimal element
        for (int j = i; j < NumElements; j++)
        {
            if (Array[j] < Array[CurrentMin])
            {
                CurrentMin = j;
            }
        }
        //swap outside the loop
        Array.Swap(CurrentMin, i);
    }
}

/**
 * \brief Performs bubble sort on given array.
 * \tparam T Data type of elements in array.
 * \param Array Dynamic Array to sort.
 * \return Number of swaps performed during sort.
 */
template <typename T>
int Sorters::BubbleSort(DynamicArray<T>& Array)
{
    const int NumElements = static_cast<const int>(Array.GetSize());
    int TimeSwapped{};
    //sort the elements in an increasing order
    for (int i = 1; i <= NumElements - 1; i++)
    {
        int Swapped = 0;
        //Repeated swapping, {5-3-2} - 5->3 - {3,5,2} - 5->2 - {3-2-5} - 3->2 - {2,3,5}
        //With adding -i-1 we decrease the amount times it need to go over.
        for (int j = 0; j <= NumElements - i - 1; j++)
        {
            if (SortersHelpers::CompareBubbleSort(Array[j], Array[j + 1]))
            {
                Array.Swap(j, j + 1);
                Swapped = 1;

                TimeSwapped++;
            }
        }
        if (Swapped == 0)
            break;
    }
    return TimeSwapped;
}

template <typename T>
void Sorters::MergeSort(DynamicArray<T>& arr)
{
}

template <typename T>
bool SortersHelpers::CompareBubbleSort(T a, T b)
{
    //Here i can decided  > if i want it inn a decreasing order or < increasing order;
    return a > b;
}

/**
 * \brief Performing sift-down procedure on given node of array-based binary tree.
 * \tparam T Data type of elements in array.
 * \param Array Array storing binary tree.
 * \param NodeToSift Index of node to start sifting at.
 */
template <typename T>
void SortersHelpers::SiftDown(DynamicArray<T>& Array, size_t NodeToSift)
{
    size_t SmallestNode{NodeToSift}; // Index of node to start shifting at.
    size_t LeftChild{2 * NodeToSift + 1}; // Index of left child node.
    size_t RightChild{2 * NodeToSift + 2}; // Index of right child node.

    // set SmallestNode to be index of smallest child node:
    if (RightChild < Array.GetSize() && Array[RightChild] < Array[SmallestNode])
        SmallestNode = RightChild;

    if (LeftChild < Array.GetSize() && Array[LeftChild] < Array[SmallestNode])
        SmallestNode = LeftChild;

    if (SmallestNode != NodeToSift)
    {
        // swap smallest child with parent and performs sift-down on new child node:
        Array.Swap(SmallestNode, NodeToSift);
        SortersHelpers::SiftDown(Array, SmallestNode);
    }
}

/**
 * \brief Makes min-heap out of binary tree represented by given array.
 * \tparam T Data type of element in array.
 * \param Array Array to make into min-heap.
 */
template <typename T>
void SortersHelpers::Heapify(DynamicArray<T>& Array)
{
    // finds index of last non-leaf node in binary tree:
    const int LastNonLeaf = static_cast<const int>(Array.GetSize() / 2 - 1);
    
    for (int i = LastNonLeaf; i >= 0; --i)
    {
        // performs sift-down on all non-leaf nodes backwards to root:
        SortersHelpers::SiftDown(Array, i);
    }
}

template <typename T>
void SortersHelpers::Merge(DynamicArray<T>& arr, DynamicArray<T>& LeftArray, DynamicArray<T>& RightArray)
{
}
