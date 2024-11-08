#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace chrono;

int binary_search(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;
        }
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

void measure_time(const vector<int>& arr, int target) {
    auto start = high_resolution_clock::now();
    binary_search(arr, target);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Execution time: " << duration.count() << " microseconds" << endl;
}

void analyzeSearchPerformance() {
    // Create a sorted array for testing
    vector<int> arr(1000000);
    for (int i = 0; i < 1000000; ++i) {
        arr[i] = i + 1;
    }

    // Best Case: Middle element
    int best_case_target = arr[arr.size() / 2];

    // Worst Case: Element not in array
    int worst_case_target = -1;

    // Average Case: Random element
    int average_case_target = arr[rand() % arr.size()];

    cout << "Best case scenario (target in middle): " << endl;
    measure_time(arr, best_case_target);

    cout << "Worst case scenario (target not in array): " << endl;
    measure_time(arr, worst_case_target);

    cout << "Average case scenario (random target): " << endl;
    measure_time(arr, average_case_target);
}

int main() {
    analyzeSearchPerformance();
    return 0;
}
