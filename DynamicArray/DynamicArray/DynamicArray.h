#pragma once
#include <stdexcept>

template<typename T>
class DynamicArray
{
private:
    // internal data array:
    T* Data_{nullptr};

    // internal variables:
    int GrowthFactor_{2};  // amount to increase capacity by when reallocating.
    int Capacity_{2};  // initial amount elements to allocate data for.
    int Size_{0};  // initial amount of elements in DynamicArray.

    // internal methods:
    void ReallocateData();
    void GrowAndReallocate();
    void ShrinkToFit();
    
public:
    // constructors and destructors:
    DynamicArray();
    DynamicArray(int InitialSize);
    DynamicArray(int InitialSize, T ElementToFill);
    ~DynamicArray();

    // public array methods:
    void Append(T NewValue);
    void Expand(T NewCapacity);
    T Delete(int Index);
    int Find(T SearchValue);

    // opperatpor overloads:
    T& operator[](int Index);

    // getters:
    int GetSize() const {return Size_;}
    int GetCapacity() const {return Capacity_;}
    
};

template <typename T>
DynamicArray<T>::DynamicArray()
{
    // allocate private data array:
    Data_ = new T[Capacity_];
}

/**
 * \brief Create empty array with given number of elements.
 * \param InitialSize - number of elements.
 */
template <typename T>
DynamicArray<T>::DynamicArray(int InitialSize)
{
    Size_ = Capacity_ = InitialSize;
    Data_ = new T[Capacity_]
}

/**
 * \brief Create array of given size, and filled with given element.
 * \param InitialSize - number of elments.
 * \param ElementToFill - Value to fill array with.
 */
template <typename T>
DynamicArray<T>::DynamicArray(int InitialSize, T ElementToFill) : DynamicArray(InitialSize)
{
    for (int i = 0; i < Capacity_; ++i)
        Data_[i] = ElementToFill;
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
    // deallocate data array on destruction:
    delete[] Data_;
}

/**
 * \brief Add new value to end of array.
 * \param NewValue - value to be added.
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
T& DynamicArray<T>::operator[](int Index)
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
    memcpy(TempData, Data_, Size_*sizeof(T));

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
}
