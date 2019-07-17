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
    left = merge_sort(left)

    right = arr[median:] 
    right = merge_sort(right)

    # Step 2
    return merge_arr(left, right)

# merge two sorted arrays
def merge_arr(left, right):
    print("LR", left, right)
    sorted_arr = []
    while(len(left) and len(right)):
        if left[0] > right[0]:
            sorted_arr.append(right[0])
            right.remove(right[0])
        else:
            sorted_arr.append(left[0])
            left.remove(left[0])

    while len(left):
        sorted_arr.append(left[0])
        left.remove(left[0])

    while len(right):
        sorted_arr.append(right[0])
        right.remove(right[0])

    print("So", sorted_arr)
    return sorted_arr

print(merge_sort([50, 70, 10, 40, 60, 30, 20]))
print(merge_sort([]))
print(merge_sort([1]))