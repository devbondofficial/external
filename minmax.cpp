#include <iostream>
#include <omp.h>
#include <climits>

using namespace std;

void min_reduction(int arr[], int n) {
    int min_value = INT_MAX;
    #pragma omp parallel for reduction(min: min_value)
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_value) {
            min_value = arr[i];
        }
    }
    cout << "Minimum value: " << min_value << endl;
}

void max_reduction(int arr[], int n) {
    int max_value = INT_MIN;
    #pragma omp parallel for reduction(max: max_value)
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
    }
    cout << "Maximum value: " << max_value << endl;
}

void sum_reduction(int arr[], int n) {
    int sum = 0;
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    cout << "Sum: " << sum << endl;
}

void average_reduction(int arr[], int n) {
    int sum = 0;
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    cout << "Average: " << (double)sum / n << endl;
}

int main() {
    int *arr, n;
    cout << "\nEnter total number of elements: ";
    cin >> n;
    arr = new int[n];
    cout << "\nEnter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    double start_time = omp_get_wtime(); // Start measuring time for sequential execution
    min_reduction(arr, n);
    max_reduction(arr, n);
    sum_reduction(arr, n);
    average_reduction(arr, n);
    double end_time = omp_get_wtime(); // End measuring time for sequential execution
    cout << "Sequential Execution Time: " << end_time - start_time << " seconds" << endl;

    int max_threads;
    #pragma omp parallel
    {
        max_threads = omp_get_num_threads();
    }

    start_time = omp_get_wtime(); // Start measuring time for parallel execution
    #pragma omp parallel
    {
        min_reduction(arr, n);
        max_reduction(arr, n);
        sum_reduction(arr, n);
        average_reduction(arr, n);
    }
    end_time = omp_get_wtime(); // End measuring time for parallel execution
    cout << "Parallel Execution Time: " << end_time - start_time << " seconds" << endl;
    cout << "Number of threads used: " << max_threads << endl;

    delete[] arr;

    return 0;
}
s
