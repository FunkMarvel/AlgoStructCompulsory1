#include <chrono>
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
    DynamicArray<int> Array = {0};
    cout << Array << endl;
    Array = {14, 6, 16, 3, 13, 20, 18, 1, 10, 5, 10, 3, 17, 2, 12, 4, 19, 7, 15, 8, 7, 11};
    cout << Array << endl;
    DynamicArray<int> TestArray = Array;

    // sorting algorithms:
    chrono::time_point<chrono::high_resolution_clock> Start;
    chrono::time_point<chrono::high_resolution_clock> Finish;
    int NumItter{static_cast<int>(1e3)};
    double MeanDuration{}, StdDeviation{};
    DynamicArray<double> Timings(NumItter, 0);

    cout << fixed << setprecision(2);
    cout << "Selection sort:" << endl;
    cout << "Unsorted: " << TestArray << endl;
    for (int i = 0; i < NumItter; ++i)
    {
        TestArray = Array;
        Start = chrono::high_resolution_clock::now();
        Sorters::SelectionSort(TestArray);
        Finish = chrono::high_resolution_clock::now();
        MeanDuration += Timings[i] = chrono::duration<double>(Finish - Start).count();
    }
    MeanDuration /= NumItter;
    StdDeviation = CalcStdDeviation(Timings, MeanDuration);
    cout << "Sorted: " << TestArray << endl;
    cout << "Elapsed time: " << MeanDuration*1e9 << " +/- " << StdDeviation*1e9 << " ns." << endl << endl;
    TestArray = Array;

    cout << "Bubble sort:" << endl;
    cout << "Unsorted: " << TestArray << endl;
    MeanDuration = 0;
    int NumSwaps{};
    for (int i = 0; i < NumItter; ++i)
    {
        TestArray = Array;
        Start = chrono::high_resolution_clock::now();
        NumSwaps = Sorters::BubbleSort(TestArray);
        Finish = chrono::high_resolution_clock::now();
        MeanDuration += Timings[i] = chrono::duration<double>(Finish - Start).count();
    }
    MeanDuration /= NumItter;
    StdDeviation = CalcStdDeviation(Timings, MeanDuration);
    cout << "Sorted: " << TestArray << endl;
    cout << "Number of swaps: " << NumSwaps << endl;
    cout << "Elapsed time: " << MeanDuration*1e9 << " +/- " << StdDeviation*1e9 << " ns." << endl << endl;
    TestArray = Array;

    cout << "Merge sort:" << endl;
    cout << "Unsorted: " << TestArray << endl;
    MeanDuration = 0;
    for (int i = 0; i < NumItter; ++i)
    {
        TestArray = Array;
        Start = chrono::high_resolution_clock::now();
        Sorters::MergeSort(TestArray);
        Finish = chrono::high_resolution_clock::now();
        MeanDuration += Timings[i] = chrono::duration<double>(Finish - Start).count();
    }
    MeanDuration /= NumItter;
    StdDeviation = CalcStdDeviation(Timings, MeanDuration);
    cout << "Sorted: " << TestArray << endl;
    cout << "Elapsed time: " << MeanDuration*1e9 << " +/- " << StdDeviation*1e9 << " ns." << endl << endl;
    TestArray = Array;

    cout << "Quick sort:" << endl;
    cout << "Unsorted: " << TestArray << endl;
    MeanDuration = 0;
    for (int i = 0; i < NumItter; ++i)
    {
        TestArray = Array;
        Start = chrono::high_resolution_clock::now();
        Sorters::QuickSort(TestArray);
        Finish = chrono::high_resolution_clock::now();
        MeanDuration += Timings[i] = chrono::duration<double>(Finish - Start).count();
    }
    MeanDuration /= NumItter;
    StdDeviation = CalcStdDeviation(Timings, MeanDuration);
    cout << "Sorted: " << TestArray << endl;
    cout << "Elapsed time: " << MeanDuration*1e9 << " +/- " << StdDeviation*1e9 << " ns." << endl << endl;
    TestArray = Array;

    cout << "Heap sort:" << endl;
    cout << "Unsorted: " << TestArray << endl;
    MeanDuration = 0;
    for (int i = 0; i < NumItter; ++i)
    {
        TestArray = Array;
        Start = chrono::high_resolution_clock::now();
        Sorters::HeapSort(TestArray);
        Finish = chrono::high_resolution_clock::now();
        MeanDuration += Timings[i] = chrono::duration<double>(Finish - Start).count();
    }
    MeanDuration /= NumItter;
    StdDeviation = CalcStdDeviation(Timings, MeanDuration);
    cout << "Sorted: " << TestArray << endl;
    cout << "Elapsed time: " << MeanDuration*1e9 << " +/- " << StdDeviation*1e9 << " ns." << endl << endl;

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
        SqrSum += Term*Term;
    }
    return sqrt(SqrSum/NumElems);
}
