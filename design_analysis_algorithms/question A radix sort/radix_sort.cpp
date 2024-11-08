#include <vector>
#include <algorithm>

using namespace std;

void countingSort(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    int count[10] = {0};

    // Count occurrences of each digit
    for (int i = 0; i < n; i++) {
        int index = (arr[i] / exp) % 10;
        count[index]++;
    }

    // Update count to hold the actual position of each digit
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        int index = (arr[i] / exp) % 10;
        output[count[index] - 1] = arr[i];
        count[index]--;
    }

    // Copy the sorted elements into original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

vector<int> radixSort(vector<int>& arr) {
    if (arr.empty()) return arr;

    // Find the maximum number to know the number of digits
    int max_num = *max_element(arr.begin(), arr.end());

    // Perform counting sort for each digit, increasing exponent each time
    for (int exp = 1; max_num / exp > 0; exp *= 10) {
        countingSort(arr, exp);
    }

    return arr;
}
