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

int main()
{
    srand(time(0));

    int sizes[] = {100, 500, 1000, 5000, 10000};

    cout << "Bubble Sort Performance Analysis\n\n";

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
        bubbleSort(temp);
        auto stop = high_resolution_clock::now();

        long long sortTime =
            duration_cast<microseconds>(stop-start).count();

        cout << "Number of Elements = " << n << endl;

        cout << "Bubble Sort Time : "
             << sortTime << " microseconds" << endl;

        cout << "----------------------------------------\n";
    }

    return 0;
}
