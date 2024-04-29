#include<iostream>
#include<stdlib.h>
#include<omp.h>

using namespace std;

void bubble(int *, int);
void swap(int &, int &);

void bubble(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        int first = i % 2;

        #pragma omp parallel for shared(a, first)
        for (int j = first; j < n - 1; j += 2)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void swap(int &a, int &b)
{
    int test;
    test = a;
    a = b;
    b = test;
}

int main()
{
    int *a, n;
    cout << "\nEnter total number of elements: ";
    cin >> n;
    a = new int[n];
    cout << "\nEnter elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    double start_time = omp_get_wtime(); // Start measuring time for sequential execution
    bubble(a, n);
    double end_time = omp_get_wtime(); // End measuring time for sequential execution
    cout << "\nSequential Execution Time: " << end_time - start_time << " seconds" << endl;

    int max_threads;
    #pragma omp parallel
    {
        max_threads = omp_get_num_threads();
    }

    start_time = omp_get_wtime(); // Start measuring time for parallel execution
    #pragma omp parallel
    {
        bubble(a, n);
    }
    end_time = omp_get_wtime(); // End measuring time for parallel execution
    cout << "Parallel Execution Time: " << end_time - start_time << " seconds" << endl;
    cout << "Number of threads used: " << max_threads << endl;

    cout << "\nSorted array is: ";
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;

    delete[] a;

    return 0;
}

