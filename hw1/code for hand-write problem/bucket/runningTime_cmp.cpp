#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

using namespace std;
using namespace std::chrono;

// Function to generate n random integers
vector<int> generateRandomNumbers(int n)
{
    vector<int> data(n);
    for (int i = 0; i < n; i++)
    {
        data[i] = rand() % 100000; // Generate random numbers between 0 and 99999
    }
    return data;
}

// Insertion Sort
void insertionSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Merge Sort
void merge(vector<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Bucket Sort
void bucketSort(vector<int> &arr)
{
    int n = arr.size();
    if (n <= 0)
        return;

    int maxVal = *max_element(arr.begin(), arr.end());
    vector<int> buckets[maxVal + 1];

    for (int i = 0; i < n; i++)
    {
        buckets[arr[i]].push_back(arr[i]);
    }

    int idx = 0;
    for (int i = 0; i <= maxVal; i++)
    {
        for (size_t j = 0; j < buckets[i].size(); j++)
        {
            arr[idx++] = buckets[i][j];
        }
    }
}

// Function to measure running time
void measureSortingTime(void (*sortingFunc)(vector<int> &), vector<int> &data, const string &sortName)
{
    auto start = high_resolution_clock::now();
    sortingFunc(data);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << sortName << " took " << duration.count() << " milliseconds." << endl;
}

int main()
{
    srand(time(0)); // Seed for random number generation

    vector<int> n_values = {1000, 5000, 10000, 50000, 100000};

    for (int n : n_values)
    {
        cout << "\nSorting " << n << " random numbers:\n";

        // Generate random data
        vector<int> data = generateRandomNumbers(n);

        // Insertion Sort
        vector<int> data_copy = data;
        measureSortingTime(insertionSort, data_copy, "Insertion Sort");

        // Merge Sort
        data_copy = data;
        measureSortingTime([](vector<int> &arr)
                           { mergeSort(arr, 0, arr.size() - 1); }, data_copy, "Merge Sort");

        // Bucket Sort
        data_copy = data;
        measureSortingTime(bucketSort, data_copy, "Bucket Sort");
    }

    return 0;
}
