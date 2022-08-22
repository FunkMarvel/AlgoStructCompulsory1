#pragma once
#include <stdexcept>
#include <initializer_list>
#include <iostream>

using namespace std;

template <typename T>
class DynamicArray
{
private:
    // internal data array:
    T* Data_{nullptr};

    // internal variables:
    size_t GrowthFactor_{2}; // amount to increase capacity by when reallocating.
    size_t Capacity_{2}; // initial amount elements to allocate data for.
    size_t Size_{0}; // initial amount of elements in DynamicArray.

    // internal methods:
    void ReallocateData();
    void GrowAndReallocate();
    void ShrinkToFit();

public:
    // constructors and destructors:
    DynamicArray();
    DynamicArray(size_t InitialSize);
    DynamicArray(size_t InitialSize, T ElementToFill);
    DynamicArray(std::initializer_list<T> ArgList);
    ~DynamicArray();

    // public array methods:
    void Append(T NewValue);
    void Expand(T NewCapacity);
    T Delete(int Index);
    int Find(T SearchValue);
    // Thomas
    static T BinarySearch(DynamicArray<T>& arr, T key);
    int BinarySearch(T key);

    // opperatpor overloads:
    T& operator[](size_t Index);

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

    // getters:
    size_t GetSize() const { return Size_; }
    size_t GetCapacity() const { return Capacity_; }
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
    memcpy(Data_, ArgList.begin(), ArgList.size() * sizeof(T));
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

template <typename T>
void DynamicArray<T>::Expand(T NewCapacity)
{
}

template <typename T>
T DynamicArray<T>::Delete(int Index)
{
}

template <typename T>
int DynamicArray<T>::Find(T SearchValue)
{
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
 * \brief Reallocate internal data array.
 */
template <typename T>
void DynamicArray<T>::ReallocateData()
{
    auto* TempData = new T[Capacity_];
    memcpy(TempData, Data_, Size_ * sizeof(T));

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

template <typename T>
void DynamicArray<T>::ShrinkToFit()
{
    if (Capacity_ <= GrowthFactor_ * Size_) return;
    Capacity_ /= GrowthFactor_;

    ReallocateData();
}

//Thomas

template <typename T>
T DynamicArray<T>::BinarySearch(DynamicArray<T>& arr, T key)
{
    int n = arr.GetSize();
    int Start = 0;
    // N - 1 is the last element in an array
    int End = n - 1;
    //K = Log(2)^N ---- O(Log.N) Example(16->8->4->2->1) log(2)^16 = 4.
    while (Start <= End)
    {
        int mid = (Start + End) / 2;
        if (arr[mid] == key)
        {
            return mid;
        }
        //take the end marker and put it on mid - 1
        if (arr[mid] > key)
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
