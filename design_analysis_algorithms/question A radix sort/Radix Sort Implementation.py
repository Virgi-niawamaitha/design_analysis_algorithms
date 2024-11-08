from typing import List

def counting_sort(arr: List[int], exp: int) -> List[int]:
    n = len(arr)
    output = [0] * n
    count = [0] * 10  # There are 10 possible digits (0-9)

    # Count occurrences of each digit
    for i in arr:
        index = (i // exp) % 10
        count[index] += 1

    # Update count to hold actual position of the digits
    for i in range(1, 10):
        count[i] += count[i - 1]

    # Build the output array
    i = n - 1
    while i >= 0:
        index = (arr[i] // exp) % 10
        output[count[index] - 1] = arr[i]
        count[index] -= 1
        i -= 1

    # Copy the sorted numbers back into arr
    for i in range(n):
        arr[i] = output[i]

    return arr

def radix_sort(arr: List[int]) -> List[int]:
    if not arr:
        return []

    # Find the maximum number to know the number of digits
    max_num = max(arr)

    # Perform counting sort for each digit, increasing exponent each time
    exp = 1
    while max_num // exp > 0:
        counting_sort(arr, exp)
        exp *= 10

    return arr
