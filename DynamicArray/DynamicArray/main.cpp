﻿#include <chrono>
#include <iomanip>
#include <iostream>
#include "DynamicArray.h"
#include "Sorters.h"

using namespace std;


//searching
void BinarySort(DynamicArray<int>& Arr);
void LinearSort(DynamicArray<int>& Arr);

double CalcStdDeviation(DynamicArray<double>& Timings, double MeanDuration);

int main()
{
    DynamicArray<int> Array = {0}; // initialize array with list.
    DynamicArray<int> LargeArray{};
    cout << "Testing array methods: " << endl;
    cout << "Starting array: " << Array << endl;
    cout << "Has memory allocated for " << Array.GetCapacity() << " number of element(s)." << endl;
    cout << "Currently contains " << Array.GetSize() << " number of element(s)." << endl << endl;

    // appending: 
    cout << "Appending '11' to end of array: " << endl;
    Array.Append(11);
    cout << "current Array: " << Array << endl;
    cout << "Has memory allocated for " << Array.GetCapacity() << " number of element(s)." << endl;
    cout << "Currently contains " << Array.GetSize() << " number of element(s)." << endl << endl;

    // inserting:
    cout << "Inserting '-11' at index '0': " << endl;
    Array.Insert(0, -11);
    cout << "current Array: " << Array << endl;
    cout << "Has memory allocated for " << Array.GetCapacity() << " number of element(s)." << endl;
    cout << "Currently contains " << Array.GetSize() << " number of element(s)." << endl << endl;

    // expanding:
    cout << "Expanding capacity of array to 32 elements: " << endl;
    Array.Expand(32);
    cout << "current Array: " << Array << endl;
    cout << "Has memory allocated for " << Array.GetCapacity() << " number of element(s)." << endl;
    cout << "Currently contains " << Array.GetSize() << " number of element(s)." << endl << endl;

    // deleting:
    cout << "Deleting element at index '1'" << endl;
    cout << "Removed element was '" << Array.Remove(1) << "'" << endl;
    cout << "current Array: " << Array << endl;
    cout << "Has memory allocated for " << Array.GetCapacity() << " number of element(s)." << endl;
    cout << "Currently contains " << Array.GetSize() << " number of element(s)." << endl << endl;

    // assigning new values:
    DynamicArray<int> TestArray = Array;
    cout << "Creating new array to test binary and linear search: " << endl;
    Array = {14, 6, 16, 3, 13, 20, 18, 1, 10, 5, 10, 3, 17, 2, 12, 4, 19, 7, 15, -8, 7, 11};
    cout << "Linear search for: -8 in array:" << endl;
    cout << " -8 is at index: " << Array.Find(-8) << endl;
    cout << "Binary search of sorted array: " << endl;
    Sorters::QuickSort(TestArray);
    cout << " -8 is at index: " << TestArray.Find(-8, false) << endl;
    
    //Creating a Large test Array for testing
    LargeArray.Expand(1000);
    for (int i = 0; i < 1000; i++)
    {
        LargeArray.Append(rand() % 800 - 200);
    }

    TestArray = Array;
    cout << "current Array: " << Array << endl;
    cout << "Has memory allocated for " << Array.GetCapacity() << " number of element(s)." << endl;
    cout << "Currently contains " << Array.GetSize() << " number of element(s)." << endl << endl;

    // benchmarking variables.
    chrono::time_point<chrono::high_resolution_clock> Start;
    chrono::time_point<chrono::high_resolution_clock> Finish;
    int NumIter{static_cast<int>(1e3)}; // number of sorts to perform when measuring execution time.
    double MeanDuration{}; // Variables for mean and standard deviation.
    DynamicArray<double> Timings(NumIter, 0); // for storing time from each iteration.
    cout << fixed << setprecision(2); // print with two sig-figs.

    // sorting algorithms:
    cout << "Selection sort:" << endl;
    cout << "Unsorted: " << TestArray << endl;
    for (int i = 0; i < NumIter; ++i)
    {
        TestArray = Array; // reset array
        Start = chrono::high_resolution_clock::now();
        Sorters::SelectionSort(TestArray); // measuring sort itself.
        Finish = chrono::high_resolution_clock::now();
        // adding up and storing measured time:
        MeanDuration += Timings[i] = chrono::duration<double>(Finish - Start).count();
    }

    MeanDuration /= NumIter; // calculating mean.
    double StdDeviation = CalcStdDeviation(Timings, MeanDuration); // calculating standard deviation.

    cout << "Sorted: " << TestArray << endl;
    // printing mean time per sort plus-minus standard deviation in nanoseconds:
    cout << "Time per sort: " << MeanDuration * 1e9 << " +/- " << StdDeviation * 1e9 << " nanoseconds" << endl << endl;
    TestArray = Array;

    cout << "Bubble sort:" << endl;
    cout << "Unsorted: " << TestArray << endl;
    MeanDuration = 0;
    int NumSwaps{};
    for (int i = 0; i < NumIter; ++i)
    {
        TestArray = Array;
        Start = chrono::high_resolution_clock::now();
        NumSwaps = Sorters::BubbleSort(TestArray);
        Finish = chrono::high_resolution_clock::now();
        MeanDuration += Timings[i] = chrono::duration<double>(Finish - Start).count();
    }
    MeanDuration /= NumIter;
    StdDeviation = CalcStdDeviation(Timings, MeanDuration);
    cout << "Sorted: " << TestArray << endl;
    cout << "Number of swaps: " << NumSwaps << endl;
    cout << "Time per sort: " << MeanDuration * 1e9 << " +/- " << StdDeviation * 1e9 << " nanoseconds" << endl << endl;
    TestArray = Array;

    cout << "Merge sort:" << endl;
    cout << "Unsorted: " << TestArray << endl;
    MeanDuration = 0;
    for (int i = 0; i < NumIter; ++i)
    {
        TestArray = Array;
        Start = chrono::high_resolution_clock::now();
        Sorters::MergeSort(TestArray);
        Finish = chrono::high_resolution_clock::now();
        MeanDuration += Timings[i] = chrono::duration<double>(Finish - Start).count();
    }
    MeanDuration /= NumIter;
    StdDeviation = CalcStdDeviation(Timings, MeanDuration);
    cout << "Sorted: " << TestArray << endl;
    cout << "Time per sort: " << MeanDuration * 1e9 << " +/- " << StdDeviation * 1e9 << " nanoseconds" << endl << endl;
    TestArray = Array;
    //DO not work with Negative numbers atm

    // cout << "Counting Sort:" << endl;
    // cout << "Unsorted: " << TestArray << endl;
    // MeanDuration = 0;
    // for (int i = 0; i < NumIter; ++i)
    // {
    //     TestArray = Array;
    //     Start = chrono::high_resolution_clock::now();
    //     Sorters::CountingSort(TestArray);
    //     Finish = chrono::high_resolution_clock::now();
    //     MeanDuration += Timings[i] = chrono::duration<double>(Finish - Start).count();
    // }
    // MeanDuration /= NumIter;
    // StdDeviation = CalcStdDeviation(Timings, MeanDuration);
    // cout << "Sorted: " << TestArray << endl;
    // cout << "Time per sort: " << MeanDuration * 1e9 << " +/- " << StdDeviation * 1e9 << " nanoseconds" << endl << endl;
    TestArray = LargeArray;

    cout << "Quick sort:" << endl;
    cout << "Unsorted: " << LargeArray << endl;
    MeanDuration = 0;
    for (int i = 0; i < NumIter; ++i)
    {
        TestArray = LargeArray;
        Start = chrono::high_resolution_clock::now();
        Sorters::QuickSort(TestArray);
        Finish = chrono::high_resolution_clock::now();
        MeanDuration += Timings[i] = chrono::duration<double>(Finish - Start).count();
    }
    MeanDuration /= NumIter;
    StdDeviation = CalcStdDeviation(Timings, MeanDuration);
    cout << "Sorted: " << TestArray << endl;
    cout << "Time per sort: " << MeanDuration * 1e9 << " +/- " << StdDeviation * 1e9 << " nanoseconds" << endl << endl;
    TestArray = LargeArray;

    cout << "Heap sort:" << endl;
    cout << "Unsorted: " << TestArray << endl;
    MeanDuration = 0;
    for (int i = 0; i < NumIter; ++i)
    {
        TestArray = LargeArray;
        Start = chrono::high_resolution_clock::now();
        Sorters::HeapSort(TestArray);
        Finish = chrono::high_resolution_clock::now();
        MeanDuration += Timings[i] = chrono::duration<double>(Finish - Start).count();
    }
    MeanDuration /= NumIter;
    StdDeviation = CalcStdDeviation(Timings, MeanDuration);
    cout << "Sorted: " << TestArray << endl;
    cout << "Time per sort: " << MeanDuration * 1e9 << " +/- " << StdDeviation * 1e9 << " nanoseconds" << endl << endl;
    TestArray = LargeArray;

    cout << "Insertion Sort:" << endl;
    cout << "Unsorted: " << TestArray << endl;
    MeanDuration = 0;
    for (int i = 0; i < NumIter; ++i)
    {
        TestArray = LargeArray;
        Start = chrono::high_resolution_clock::now();
        Sorters::insertionSort(TestArray);
        Finish = chrono::high_resolution_clock::now();
        MeanDuration += Timings[i] = chrono::duration<double>(Finish - Start).count();
    }
    MeanDuration /= NumIter;
    StdDeviation = CalcStdDeviation(Timings, MeanDuration);
    cout << "Sorted: " << TestArray << endl;
    cout << "Time per sort: " << MeanDuration * 1e9 << " +/- " << StdDeviation * 1e9 << " nanoseconds" << endl << endl;
    TestArray = LargeArray;

 
    cout << "Intro Sort Large:" << endl;
    cout << "Unsorted: " << LargeArray << endl;
    MeanDuration = 0;
    for (int i = 0; i < NumIter; ++i)
    {
        TestArray = LargeArray;
        Start = chrono::high_resolution_clock::now();
        Sorters::IntroSort(TestArray);
        Finish = chrono::high_resolution_clock::now();
        MeanDuration += Timings[i] = chrono::duration<double>(Finish - Start).count();
    }
    MeanDuration /= NumIter;
    StdDeviation = CalcStdDeviation(Timings, MeanDuration);
    cout << "Sorted: " << TestArray << endl;
    cout << "Time per sort: " << MeanDuration * 1e9 << " +/- " << StdDeviation * 1e9 << " nanoseconds" << endl << endl;
    TestArray = Array;

    cout << "Intro Sort:" << endl;
    cout << "Unsorted: " << TestArray << endl;
    MeanDuration = 0;
    for (int i = 0; i < NumIter; ++i)
    {
        TestArray = Array;
        Start = chrono::high_resolution_clock::now();
        Sorters::IntroSort(TestArray);
        Finish = chrono::high_resolution_clock::now();
        MeanDuration += Timings[i] = chrono::duration<double>(Finish - Start).count();
    }
    MeanDuration /= NumIter;
    StdDeviation = CalcStdDeviation(Timings, MeanDuration);
    cout << "Sorted: " << TestArray << endl;
    cout << "Time per sort: " << MeanDuration * 1e9 << " +/- " << StdDeviation * 1e9 << " nanoseconds" << endl << endl;
    TestArray = Array;

    return 0;
}

/**
 * \brief Sorting array with BinarySort
 * \param Arr Array to be sorted
 */
void BinarySort(DynamicArray<int>& Arr)
{
    int n = static_cast<int>(Arr.GetSize());
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


/**
 * \brief Calculates standard deviation from array of data points and mean value;
 * \param Timings Array of data points.
 * \param MeanDuration Mean of data points.
 * \return Standard deviation.
 */
double CalcStdDeviation(DynamicArray<double>& Timings, double MeanDuration)
{
    double SqrSum{};
    const double NumElems{static_cast<double>(Timings.GetSize())};
    for (size_t i = 0; i < Timings.GetSize(); ++i)
    {
        const auto Term{(Timings[i] - MeanDuration)};
        SqrSum += Term * Term;
    }
    return sqrt(SqrSum / NumElems);
}
