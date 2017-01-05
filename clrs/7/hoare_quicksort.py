#!/usr/bin/env python
from randata import getrandata

def hoare_partition(arr, low, high):
    pivot = arr[low]
    i = low - 1
    j = high + 1
    while True:
        i += 1
        j -= 1
        while arr[j] > pivot:
            j -= 1
        while arr[i] < pivot:
            i += 1
        if i < j:
            arr[i], arr[j] = arr[j], arr[i]
        else:
            return j

def quicksort(arr, low, high):
    if low < high:
        mid = hoare_partition(arr, low, high)
        quicksort(arr, low, mid)
        quicksort(arr, mid + 1, high)


if __name__ == '__main__':
    arr = getrandata(0)
    print(arr)
    quicksort(arr, 0, -1)
    print(arr)


