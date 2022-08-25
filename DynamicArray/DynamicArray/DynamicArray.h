#pragma once
#include <stdexcept>
#include <initializer_list>
#include <iostream>

/**
 * \brief Dynamic Array class made by Anders Petershagen Åsbø and Thomas Dalstein Sæther.
 * \tparam T Element data type.
 */
template <typename T>
class DynamicArray
{
private:
    // internal data array:
    T* Data_{nullptr};

    // internal variables:
    const size_t GrowthFactor_{2}; // amount to increase capacity by when reallocating.
    size_t Capacity_{1}; // initial amount elements to allocate data for.
    size_t Size_{0}; // initial amount of elements in DynamicArray.

    // internal methods:
    void ReallocateData();
    void GrowAndReallocate();

public:
    // constructors and destructor:
    DynamicArray();
    explicit DynamicArray(size_t InitialSize);
    DynamicArray(size_t InitialSize, T ElementToFill);
    DynamicArray(std::initializer_list<T> ArgList);
    DynamicArray(const DynamicArray<T>& OtherArray);
    ~DynamicArray();

    // getters:
    /**
     * \return Number of elements in array.
     */
    size_t GetSize() const { return Size_; }
    
    /**
     * \return Number of elements there is allocated space for.
     */
    size_t GetCapacity() const { return Capacity_; }

    /**
     * \return Pointer to first element in array.
     */
    T* GetBegin() { return Data_; }

    // public array methods:
    void Append(T NewValue);
    void Insert(size_t Index, T NewValue);
    void Expand();
    void Expand(size_t NewCapacity);
    T Remove(size_t Index);
    T RemoveLastElement();
    int Find(T SearchValue, bool Linear = false);
    void ShrinkToFit();
    void Reverse();

    void Swap(size_t FirstIndex, size_t SecondIndex);

    // Thomas
    // LinearSearch
    static T LinearSearch(DynamicArray<T>& Array, T Key);
    int LinearSearch(T Key);
    // BinarySearch
    static T BinarySearch(DynamicArray<T>& Array, T Key);
    int BinarySearch(T key);

    // opperatpor overloads:
    T& operator[](size_t Index);
    DynamicArray<T>& operator=(const DynamicArray<T>& OtherArray);

    /**
     * \brief Add elements of array to out-stream.
     * \param out Ostream reference.
     * \param SomeArray array to extract.
     * \return Ostream reference.
     */
    friend std::ostream& operator<<(std::ostream& out, DynamicArray<T>& SomeArray)
    {
        for (size_t i = 0; i < SomeArray.GetSize(); ++i)
        {
            if (i != 0 && i != SomeArray.GetSize()) out << " ";
            out << SomeArray[i];
        }
        return out;
    }
};

template <typename T>
DynamicArray<T>::DynamicArray()
{
    // allocate private data array:
    Data_ = new T[Capacity_];
}

/**
 * \brief Create empty array with given number of elements.
 * \param InitialSize Number of elements.
 */
template <typename T>
DynamicArray<T>::DynamicArray(size_t InitialSize)
{
    Size_ = Capacity_ = InitialSize;
    Data_ = new T[Capacity_];
}

/**
 * \brief Create array of given size, and filled with given element.
 * \param InitialSize Number of elments.
 * \param ElementToFill Value to fill array with.
 */
template <typename T>
DynamicArray<T>::DynamicArray(size_t InitialSize, T ElementToFill) : DynamicArray(InitialSize)
{
    for (int i = 0; i < Capacity_; ++i)
        Data_[i] = ElementToFill;
}

template <typename T>
DynamicArray<T>::DynamicArray(std::initializer_list<T> ArgList) : DynamicArray(ArgList.size())
{
    memcpy(Data_, ArgList.begin(), ArgList.size() * sizeof(Data_[0]));
}

/**
 * \brief Copy constructor creating new array from existing array.
 * \param OtherArray Array to copy from.
 */
template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& OtherArray)
{
    Capacity_ = OtherArray.Capacity_;
    Size_ = OtherArray.Size_;

    Data_ = new T[Capacity_];
    memcpy(Data_, OtherArray.Data_, Size_ * (sizeof(Data_[0])));
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
    // deallocate data array on destruction:
    delete[] Data_;
}

/**
 * \brief Add new value to end of array.
 * \param NewValue Value to be added.
 */
template <typename T>
void DynamicArray<T>::Append(T NewValue)
{
    // reallocate data array if necessary:
    if (Size_ >= Capacity_) GrowAndReallocate();
    Data_[Size_++] = NewValue;
}

/**
 * \brief Insert new element at given index.
 * \param Index Index to insert at.
 * \param NewValue Element to insert.
 */
template <typename T>
void DynamicArray<T>::Insert(size_t Index, T NewValue)
{
    if (Index < 0 || Index > Size_) throw std::runtime_error("Index out of range");
    if (Index == Size_) Append(NewValue);
    if (++Size_ >= Capacity_) GrowAndReallocate(); // reallocate if no space for new element.

    // moving existing elements to make space for new element, and then inserting:
    memmove(Data_ + Index + 1, Data_ + Index, (Size_ - Index - 1) * sizeof(Data_[0]));
    Data_[Index] = NewValue;
}

/**
 * \brief Reallocates data with double capacity.
 */
template <typename T>
void DynamicArray<T>::Expand()
{
    GrowAndReallocate();
}

/**
 * \brief Reallocates data to array with given capacity, if possible.
 * \param NewCapacity Desired new capacity of array.
 */
template <typename T>
void DynamicArray<T>::Expand(size_t NewCapacity)
{
    // if given capacity is less than the number of elements
    // the array will instead shrink to smallest Size that can hold all data.
    if (NewCapacity <= Size_)
    {
        Capacity_ = Size_;
        ReallocateData();
        return;
    }

    Capacity_ = NewCapacity;
    ReallocateData();
}

/**
 * \brief Remove and return element at given index.
 * \param Index Element to remove.
 * \return Removed element.
 */
template <typename T>
T DynamicArray<T>::Remove(size_t Index)
{
    if (Index < 0 || Index >= Size_) throw std::runtime_error("Index out of range");

    auto RemovedElement = Data_[Index]; // retrieve value for return.
    // using memmove to copy data, because source and destination overlaps:
    memmove(Data_ + Index, Data_ + Index + 1, (Size_ - Index - 1) * sizeof(Data_[0]));

    if (--Size_ < Capacity_ / 2) ShrinkToFit();  // reduce amount of unused memory.
    return RemovedElement;
}

/**
 * \brief Returns and removes last element in array.
 * \return Removed element.
 */
template <typename T>
T DynamicArray<T>::RemoveLastElement()
{
    return Remove(Size_ - 1);
}

/**
 * \brief Find index of element in array.
 * \param SearchValue Element to search for.
 * \param Linear If true, use linear search.
 * \return Returns index of element, or -1 if element not in array.
 */
template <typename T>
int DynamicArray<T>::Find(T SearchValue, bool Linear)
{
    if (Linear) return LinearSearch(SearchValue);
    return BinarySearch(SearchValue);
}


/**
 * \brief Access element in array at given index.
 * \param Index of element to access.
 * \return Reference to element at given index.
 */
template <typename T>
T& DynamicArray<T>::operator[](size_t Index)
{
    if (Index < 0 || Index >= Size_) throw std::runtime_error("Index out of range");
    return Data_[Index];
}

/**
 * \brief Assign value to array by copy.
 * \param OtherArray Array to copy.
 * \return Returns assigned array.
 */
template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& OtherArray)
{
    // if assigned to self:
    if (this == OtherArray) return *this;
    
    // delete already allocated data:
    delete[] Data_;

    // copy properties and data from given array:
    Capacity_ = OtherArray.Capacity_;
    Size_ = OtherArray.Size_;
    Data_ = new T[Capacity_];
    memcpy(Data_, OtherArray.Data_, Size_*sizeof(Data_[0]));
    
    return *this;
}


/**
 * \brief Reallocate internal data array.
 */
template <typename T>
void DynamicArray<T>::ReallocateData()
{
    // allocating and copying data:
    auto* TempData = new T[Capacity_];
    memcpy(TempData, Data_, Size_ * sizeof(Data_[0]));

    // deleting old data and retargeting pointer:
    delete[] Data_;
    Data_ = TempData;
}

/**
 * \brief Increase internal capacity and reallocate data.
 */
template <typename T>
void DynamicArray<T>::GrowAndReallocate()
{
    Capacity_ *= GrowthFactor_;
    ReallocateData();
}

/**
 * \brief Shrinks array if < 50% of allocated memory is used.
 */
template <typename T>
void DynamicArray<T>::ShrinkToFit()
{
    if (Capacity_ <= GrowthFactor_ * Size_) return;
    Capacity_ /= GrowthFactor_;
    ReallocateData();
}

/**
 * \brief Reversing order of elements.
 */
template <typename T>
void DynamicArray<T>::Reverse()
{
    if (Size_ <= 0) return;
    for (size_t i = 0; i < Size_/2; ++i)
        Swap(i, Size_-i-1);
}

/**
 * \brief Swaps elements at given indices.
 * \param FirstIndex First index to swap.
 * \param SecondIndex Second index to swap.
 */
template <typename T>
void DynamicArray<T>::Swap(size_t FirstIndex, size_t SecondIndex)
{
    if (FirstIndex == SecondIndex) return;
    auto Temp = Data_[FirstIndex];
    Data_[FirstIndex] = Data_[SecondIndex];
    Data_[SecondIndex] = Temp;
}


template <typename T>
T DynamicArray<T>::LinearSearch(DynamicArray<T>& Array, T Key)
{
    const int n = static_cast<int>(Array.GetSize());
    for (int i = 0; i < n; i++)
    {
        //check if current element matches the key
        if (Array[i] == Key)
        {
            return i;
        }
    }
    //out of the loop
    return -1;
}

template <typename T>
int DynamicArray<T>::LinearSearch(T Key)
{
    for (int i = 0; i < Size_; i++)
    {
        //check if current element matches the key
        if (Data_[i] == Key)
        {
            return i;
        }
    }
    //out of the loop
    return -1;
}


template <typename T>
T DynamicArray<T>::BinarySearch(DynamicArray<T>& Array, T Key)
{
    const int n = static_cast<int>(Array.GetSize());
    int Start = 0;
    // N - 1 is the last element in an array
    int End = n - 1;
    //K = Log(2)^N ---- O(Log.N) Example(16->8->4->2->1) log(2)^16 = 4.
    while (Start <= End)
    {
        int mid = (Start + End) / 2;
        if (Array[mid] == Key)
        {
            return mid;
        }
        //take the end marker and put it on mid - 1
        if (Array[mid] > Key)
        {
            End = mid - 1;
        }
        //take the Start marker and put it on mid + 1
        else
        {
            Start = mid + 1;
        }
    }

    return -1;
}

template <typename T>
int DynamicArray<T>::BinarySearch(T key)
{
    int Start = 0;
    // N - 1 is the last element in an array
    int End = Size_ - 1;
    //K = Log(2)^N ---- O(Log.N) Example(16->8->4->2->1) log(2)^16 = 4.
    while (Start <= End)
    {
        int mid = (Start + End) / 2;
        if (Data_[mid] == key)
        {
            return mid;
        }
        //take the end marker and put it on mid - 1
        if (Data_[mid] > key)
        {
            End = mid - 1;
        }
        //take the Start marker and put it on mid + 1
        else
        {
            Start = mid + 1;
        }
    }

    return -1;
}
