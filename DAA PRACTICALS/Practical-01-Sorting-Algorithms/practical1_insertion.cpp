#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

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

int main()
{
    srand(time(0));

    int sizes[] = {100, 500, 1000, 5000, 10000};

    cout << "Insertion Sort Performance Analysis\n\n";

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
        insertionSort(temp);
        auto stop = high_resolution_clock::now();

        long long sortTime =
            duration_cast<microseconds>(stop-start).count();

        cout << "Number of Elements = " << n << endl;

        cout << "Insertion Sort Time : "
             << sortTime << " microseconds" << endl;

        cout << "----------------------------------------\n";
    }

    return 0;
}
