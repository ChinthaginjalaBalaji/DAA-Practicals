#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

// Linear Search
int linearSearch(vector<int> arr, int key)
{
    for(int i = 0; i < arr.size(); i++)
    {
        if(arr[i] == key)
        {
            return i;
        }
    }

    return -1;
}

// Binary Search
int binarySearch(vector<int> arr, int key)
{
    int low = 0;
    int high = arr.size() - 1;

    while(low <= high)
    {
        int mid = low + (high - low) / 2;

        if(arr[mid] == key)
        {
            return mid;
        }
        else if(arr[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}

int main()
{
    int sizes[] = {100, 500, 1000, 5000, 10000, 50000, 100000};

    cout << "Searching Algorithm Performance Analysis\n\n";

    for(int n : sizes)
    {
        vector<int> arr(n);

        // Creating a sorted array
        for(int i = 0; i < n; i++)
        {
            arr[i] = i + 1;
        }

        // Search for the last element
        int key = n;

        // Linear Search
        auto start = high_resolution_clock::now();

        int linearIndex = linearSearch(arr, key);

        auto stop = high_resolution_clock::now();

        long long linearTime =
            duration_cast<microseconds>(stop - start).count();


        // Binary Search
        start = high_resolution_clock::now();

        int binaryIndex = binarySearch(arr, key);

        stop = high_resolution_clock::now();

        long long binaryTime =
            duration_cast<microseconds>(stop - start).count();


        cout << "Number of Elements = " << n << endl;

        cout << "Search Element     = " << key << endl;

        cout << "Linear Search      : ";

        if(linearIndex != -1)
        {
            cout << "Found at index " << linearIndex;
        }
        else
        {
            cout << "Not Found";
        }

        cout << endl;

        cout << "Linear Search Time : "
             << linearTime << " microseconds" << endl;


        cout << "Binary Search      : ";

        if(binaryIndex != -1)
        {
            cout << "Found at index " << binaryIndex;
        }
        else
        {
            cout << "Not Found";
        }

        cout << endl;

        cout << "Binary Search Time : "
             << binaryTime << " microseconds" << endl;

        cout << "----------------------------------------\n";
    }

    return 0;
}