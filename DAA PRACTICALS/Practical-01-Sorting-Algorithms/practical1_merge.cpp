#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

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

int main()
{
    srand(time(0));

    int sizes[] = {100, 500, 1000, 5000, 10000};

    cout << "Merge Sort Performance Analysis\n\n";

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
        mergeSort(temp, 0, n-1);
        auto stop = high_resolution_clock::now();

        long long sortTime =
            duration_cast<microseconds>(stop-start).count();

        cout << "Number of Elements = " << n << endl;

        cout << "Merge Sort Time : "
             << sortTime << " microseconds" << endl;

        cout << "----------------------------------------\n";
    }

    return 0;
}
