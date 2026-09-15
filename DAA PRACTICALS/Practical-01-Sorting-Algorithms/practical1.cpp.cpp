#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

// Bubble Sort
void bubbleSort(vector<int>& arr)
{
    int n = arr.size();

    for(int i = 0; i < n-1; i++)
    {
        for(int j = 0; j < n-i-1; j++)
        {
            if(arr[j] > arr[j+1])
            {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

// Selection Sort
void selectionSort(vector<int>& arr)
{
    int n = arr.size();

    for(int i = 0; i < n-1; i++)
    {
        int min = i;

        for(int j = i+1; j < n; j++)
        {
            if(arr[j] < arr[min])
            {
                min = j;
            }
        }

        swap(arr[i], arr[min]);
    }
}

// Insertion Sort
void insertionSort(vector<int>& arr)
{
    int n = arr.size();

    for(int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i-1;

        while(j >= 0 && arr[j] > key)
        {
            arr[j+1] = arr[j];
            j--;
        }

        arr[j+1] = key;
    }
}

// Merge Sort
void merge(vector<int>& arr, int l, int m, int r)
{
    int n1 = m-l+1;
    int n2 = r-m;

    vector<int> left(n1);
    vector<int> right(n2);

    for(int i = 0; i < n1; i++)
        left[i] = arr[l+i];

    for(int j = 0; j < n2; j++)
        right[j] = arr[m+1+j];

    int i = 0;
    int j = 0;
    int k = l;

    while(i < n1 && j < n2)
    {
        if(left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }

        k++;
    }

    while(i < n1)
    {
        arr[k] = left[i];
        i++;
        k++;
    }

    while(j < n2)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int l, int r)
{
    if(l < r)
    {
        int m = (l+r)/2;

        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

// Quick Sort
int partition(vector<int>& arr, int low, int high)
{
    int pivot = arr[high];
    int i = low-1;

    for(int j = low; j < high; j++)
    {
        if(arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i+1], arr[high]);

    return i+1;
}

void quickSort(vector<int>& arr, int low, int high)
{
    if(low < high)
    {
        int p = partition(arr, low, high);

        quickSort(arr, low, p-1);
        quickSort(arr, p+1, high);
    }
}

int main()
{
    srand(time(0));

    int sizes[] = {100, 500, 1000, 5000, 10000};

    cout << "Sorting Algorithm Performance Analysis\n\n";

    for(int n : sizes)
    {
        vector<int> arr(n);

        // Generate random numbers
        for(int i = 0; i < n; i++)
        {
            arr[i] = rand() % 1000;
        }

        vector<int> temp;

        // Bubble Sort
        temp = arr;

        auto start = high_resolution_clock::now();
        bubbleSort(temp);
        auto stop = high_resolution_clock::now();

        long long bubbleTime =
            duration_cast<microseconds>(stop-start).count();


        // Selection Sort
        temp = arr;

        start = high_resolution_clock::now();
        selectionSort(temp);
        stop = high_resolution_clock::now();

        long long selectionTime =
            duration_cast<microseconds>(stop-start).count();


        // Insertion Sort
        temp = arr;

        start = high_resolution_clock::now();
        insertionSort(temp);
        stop = high_resolution_clock::now();

        long long insertionTime =
            duration_cast<microseconds>(stop-start).count();


        // Merge Sort
        temp = arr;

        start = high_resolution_clock::now();
        mergeSort(temp, 0, n-1);
        stop = high_resolution_clock::now();

        long long mergeTime =
            duration_cast<microseconds>(stop-start).count();


        // Quick Sort
        temp = arr;

        start = high_resolution_clock::now();
        quickSort(temp, 0, n-1);
        stop = high_resolution_clock::now();

        long long quickTime =
            duration_cast<microseconds>(stop-start).count();


        cout << "Number of Elements = " << n << endl;

        cout << "Bubble Sort Time    : "
             << bubbleTime << " microseconds" << endl;

        cout << "Selection Sort Time : "
             << selectionTime << " microseconds" << endl;

        cout << "Insertion Sort Time : "
             << insertionTime << " microseconds" << endl;

        cout << "Merge Sort Time     : "
             << mergeTime << " microseconds" << endl;

        cout << "Quick Sort Time     : "
             << quickTime << " microseconds" << endl;

        cout << "----------------------------------------\n";
    }

    return 0;
}