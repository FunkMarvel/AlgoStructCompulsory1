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
    void ShrinkToFit();
    
public:
    // constructors and destructors:
    DynamicArray();
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

template <typename T>
DynamicArray<T>::~DynamicArray()
{
    // deallocate data array on destruction:
    delete[] Data_;
}

template <typename T>
void DynamicArray<T>::Append(T NewValue)
{
    if (Size_ >= Capacity_) ReallocateData();
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

template <typename T>
T& DynamicArray<T>::operator[](int Index)
{
    if (Index < 0 || Index >= Size_) throw std::runtime_error("Index out of range");
    return Data_[Index];
}

template <typename T>
void DynamicArray<T>::ReallocateData()
{
}

template <typename T>
void DynamicArray<T>::ShrinkToFit()
{
}
