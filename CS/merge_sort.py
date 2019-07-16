import math

def merge_sort(arr):
    # 1. Recursively, break array into two halves until each half has only one element.
    # 2. Merge sub-array of size 1 in sorted order to form sub-array of size 2. 
    # Repeat for that sub-array of size 2, etc. until original array is completely sorted. 
    # Note, sorting sub-arrays themselves need an algorithm!

    # Step 1
    if len(arr) <= 1:
        return arr

    median = math.ceil(len(arr)/2)

    left = arr[:median]
    merge_sort(left)

    right = arr[median:] 
    merge_sort(right)

    # Step 2
    return bubble_sort(left, right)

def bubble_sort(left, right):
    arr = list((*left, *right))
    for i in range(len(arr)):
        for j in range(i+1, len(arr)):
            if arr[i] > arr[j]:
                arr[i], arr[j] = arr[j], arr[i]
    return arr

print(merge_sort([50, 70, 10, 40, 60, 30, 20]))
print(merge_sort([]))
print(merge_sort([1]))