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
    void MergeSort(DynamicArray<T>& Array);

    template <typename T>
    void QuickSort(DynamicArray<T>& Array, int Start = NULL, int End = NULL);
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
    void Merge(DynamicArray<T>& Array, DynamicArray<T>& LeftArray, DynamicArray<T>& RightArray);

    template <typename T>
    int ArraySplit(DynamicArray<T>& Array, int Start, int End);
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
void Sorters::MergeSort(DynamicArray<T>& Array)
{
    const int Length = static_cast<int>(Array.GetSize());

    if (Length <= 1)
    {
        return;
    }
    int Mid = Length / 2;

    DynamicArray<int> LeftArr(Mid);
    DynamicArray<int> RightArr(Length - Mid);

    ////Memcpy ver of splitting up Array(2 different memcpy,No need for if statement.):
    auto ArrPtr = Array.GetBegin();
    memcpy(LeftArr.GetBegin(), Array.GetBegin(), LeftArr.GetSize() * sizeof(LeftArr[0]));
    memcpy(RightArr.GetBegin(), Array.GetBegin() + Mid, RightArr.GetSize() * sizeof(RightArr[0]));

    //   For loop ver of splitting up the Array(One for loop with if statement):
    // int IndexLeftArr = 0;
    // int IndexRightArr = 0;
    // for (; IndexLeftArr < Length; IndexLeftArr++)
    // {
    //     if (IndexLeftArr < Mid)
    //     {
    //         LeftArr[IndexLeftArr] = Array[IndexLeftArr];
    //     }
    //     else
    //     {
    //         RightArr[IndexRightArr] = Array[Mid + IndexRightArr];
    //         IndexRightArr++;
    //     }
    // }

    MergeSort(LeftArr);
    MergeSort(RightArr);
    SortersHelpers::Merge(Array, LeftArr, RightArr);
}

template <typename T>
void Sorters::QuickSort(DynamicArray<T>& Array, int Start, int End)
{
    if (Start == NULL)
    {
        Start = 0;
    }
    if (End == NULL)
    {
        End = Array.GetSize() - 1;
    }
    if (End <= Start)
    {
        return;
    }

    int FocusPivot = SortersHelpers::ArraySplit(Array, Start, End);
    QuickSort(Array, Start, FocusPivot - 1);
    QuickSort(Array, FocusPivot + 1, End);
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
void SortersHelpers::Merge(DynamicArray<T>& Array, DynamicArray<T>& LeftArray, DynamicArray<T>& RightArray)
{
    const int LeftArrSize = static_cast<int>(Array.GetSize() / 2);
    const int RightArrSize = static_cast<int>(Array.GetSize()) - LeftArrSize;

    int i = 0, LS = 0, RS = 0; //indices for loops LS = LeftSide / Rs = RightSide

    //Merging conditions

    while (LS < LeftArrSize && RS < RightArrSize)
    {
        if (LeftArray[LS] < RightArray[RS])
        {
            Array[i] = LeftArray[LS];
            i++;
            LS++;
        }
        else
        {
            Array[i] = RightArray[RS];
            i++;
            RS++;
        }
    }
    while (LS < LeftArrSize)
    {
        Array[i] = LeftArray[LS];
        i++;
        LS++;
    }
    while (RS < RightArrSize)
    {
        Array[i] = RightArray[RS];
        i++;
        RS++;
    }
}

template <typename T>
int SortersHelpers::ArraySplit(DynamicArray<T>& Array, int Start, int End)
{
    auto FocusPivot = Array[End];
    int i = Start - 1;

    for (int j = Start; j <= End; j++)
    {
        if (Array[j] < FocusPivot)
        {
            i++;
            auto TempElem = Array[i];
            Array[i] = Array[j];
            Array[j] = TempElem;
        }
    }
    i++;
    auto TempElm = Array[i];
    Array[i] = Array[End];
    Array[End] = TempElm;

    return i;
}
