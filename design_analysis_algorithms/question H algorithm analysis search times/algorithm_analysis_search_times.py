import time
import random

def binary_search(arr, target):
    left, right = 0, len(arr) - 1
    while left <= right:
        mid = (left + right) // 2
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    return -1

def measure_time(arr, target):
    start_time = time.time()
    binary_search(arr, target)
    return time.time() - start_time

# Create a sorted list for testing
arr = list(range(1, 1000000))

# Best Case: Target is the middle element
best_case_target = arr[len(arr) // 2]

# Worst Case: Target is not in the array
worst_case_target = -1

# Average Case: Random target from the array
average_case_target = random.choice(arr)

# Measure the execution time for each case
best_case_time = measure_time(arr, best_case_target)
worst_case_time = measure_time(arr, worst_case_target)
average_case_time = measure_time(arr, average_case_target)

print(f"Best case execution time: {best_case_time:.6f} seconds")
print(f"Worst case execution time: {worst_case_time:.6f} seconds")
print(f"Average case execution time: {average_case_time:.6f} seconds")
