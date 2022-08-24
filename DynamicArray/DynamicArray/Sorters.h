#pragma once
#include "DynamicArray.h"

namespace Sorters
{
    template<typename T>
    void HeapSort(DynamicArray<T>& Array);
}

template<typename T>
void SiftDown(DynamicArray<T>& Array, size_t NodeToSift);

template<typename T>
void Heapify(DynamicArray<T>& Array);

template<typename T>
void Sorters::HeapSort(DynamicArray<T>& Array)
{
    // Heapify array
    Heapify(Array);

    // perform sift down during sorting.
}

template <typename T>
void SiftDown(DynamicArray<T>& Array, size_t NodeToSift)
{
    size_t MaxNode{ NodeToSift };
    size_t LeftChild{ 2*NodeToSift + 1 };
    size_t RightChild{ 2*NodeToSift + 2 };

    if (RightChild < Array.GetSize() && Array[RightChild] > Array[MaxNode])
    {
        MaxNode = RightChild;
    }

    if (LeftChild < Array.GetSize() && Array[LeftChild] > Array[MaxNode])
    {
        MaxNode = LeftChild;
    }
    
    if(MaxNode != NodeToSift)
    {
        Array.Swap(MaxNode, NodeToSift);
        SiftDown(Array, MaxNode);
    }

    if (RightChild < Array.GetSize() && Array[LeftChild] < Array[RightChild])
    {
        Array.Swap(LeftChild, RightChild);
    }
}

template <typename T>
void Heapify(DynamicArray<T>& Array)
{
    size_t LastNonLeaf{Array.GetSize()/2 - 1};
    for (int i = LastNonLeaf; i >= 0; --i)
    {
        SiftDown(Array, i);
    }
}
