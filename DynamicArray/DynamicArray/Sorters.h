#pragma once
#include "DynamicArray.h"

/**
 * \brief Library of sorting algorithms
 */
namespace Sorters
{
    template<typename T>
    void HeapSort(DynamicArray<T>& Array);
}

/**
 * \brief Internal support functions for Sorters-library.
 */
namespace SortersHelpers
{
    template<typename T>
    void SiftDown(DynamicArray<T>& Array, size_t NodeToSift);

    template<typename T>
    void Heapify(DynamicArray<T>& Array);
}

/**
 * \brief Sorting input array in ascending order using Heap sort.
 * \tparam T Data type of elements in array.
 * \param Array Array to sort.
 */
template<typename T>
void Sorters::HeapSort(DynamicArray<T>& Array)
{
    // Organize Array into Min-Heap:
    SortersHelpers::Heapify(Array);

    // Create Temp array for storing sorted values:
    DynamicArray<T> TempArray{};
    auto NumElements = Array.GetSize();  // saving amount of elements to sort.
    TempArray.Expand(NumElements);  // reserving necessary amount of memory.

    for (int i = 0; i < NumElements-1; ++i)  // looping until there is only one element left.
    {
        TempArray.Append(Array[0]);  // adding smallest element to front of temp array.
        Array[0] = Array.RemoveLastElement();  // shifting last heap element to be new root.
        SortersHelpers::SiftDown(Array, 0);  // sifting down root to restore heap property.
    }
    TempArray.Append(Array.RemoveLastElement());  // moving final element.
    Array = TempArray;  // populating Array from temp array by copy assignment.
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
    size_t SmallestNode{ NodeToSift };  // Index of node to start shifting at.
    size_t LeftChild{ 2*NodeToSift + 1 };  // Index of left child node.
    size_t RightChild{ 2*NodeToSift + 2 };  // Index of right child node.

    // set SmallestNode to be index of smallest child node:
    if (RightChild < Array.GetSize() && Array[RightChild] < Array[SmallestNode])
        SmallestNode = RightChild;
    
    if (LeftChild < Array.GetSize() && Array[LeftChild] < Array[SmallestNode])
        SmallestNode = LeftChild;

    if(SmallestNode != NodeToSift)
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
    size_t LastNonLeaf{Array.GetSize()/2 - 1};  // finds index of last non-leaf node in binary tree.
    for (int i = LastNonLeaf; i >= 0; --i)
    {
        // performs sift-down on all non-leaf nodes backwards to root:
        SortersHelpers::SiftDown(Array, i);
    }
}
