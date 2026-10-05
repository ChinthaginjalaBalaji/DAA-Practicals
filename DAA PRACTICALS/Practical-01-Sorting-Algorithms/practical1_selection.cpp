#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

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

int main()
{
    srand(time(0));

    int sizes[] = {100, 500, 1000, 5000, 10000};

    cout << "Selection Sort Performance Analysis\n\n";

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
        selectionSort(temp);
        auto stop = high_resolution_clock::now();

        long long sortTime =
            duration_cast<microseconds>(stop-start).count();

        cout << "Number of Elements = " << n << endl;

        cout << "Selection Sort Time : "
             << sortTime << " microseconds" << endl;

        cout << "----------------------------------------\n";
    }

    return 0;
}
