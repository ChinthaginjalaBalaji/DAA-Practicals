#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

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

    cout << "Quick Sort Performance Analysis\n\n";

    for(int n : sizes)
    {
        vector<int> arr(n);

        // Generate random numbers
        for(int i = 0; i < n; i++)
        {
            arr[i] = rand() % 1000;
        }

        vector<int> temp = arr;

        auto start = high_resolution_clock::now();
        quickSort(temp, 0, n-1);
        auto stop = high_resolution_clock::now();

        long long sortTime =
            duration_cast<microseconds>(stop-start).count();

        cout << "Number of Elements = " << n << endl;

        cout << "Quick Sort Time : "
             << sortTime << " microseconds" << endl;

        cout << "----------------------------------------\n";
    }

    return 0;
}
