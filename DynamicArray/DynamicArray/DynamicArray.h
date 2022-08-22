
template<typename T>
class DynamicArray
{
public:
    DynamicArray();

    ~DynamicArray();

private:
    // internal data array:
    T* Data_{nullptr};
    
    int GrowthFactor_{2};  // amount to increase capacity by when reallocating.
    int Capacity{1};  // initial amount elements to allocate data for.
    int Size{0};  // initial amount of elements in DynamicArray.
};

template <typename T>
DynamicArray<T>::DynamicArray()
{
    // allocate private data array:
    Data_ = new T[Capacity];
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
    // deallocate data array on destruction:
    delete[] Data_;
}
