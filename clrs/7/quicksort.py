#!/usr/bin/env python
from randata import getrandata
from timing import timing
import random

def quicksort(arr, low, high):
    if low < high:
        mid = partition(arr, low, high)
        quicksort(arr, low, mid - 1)
        quicksort(arr, mid + 1, high)

def partition(arr, low, high):
    pivot = arr[low]
    i = low
    for j in range(low + 1, high + 1):
        if arr[j] < pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i], arr[low] = arr[low], arr[i]
    return i

def randomized_partition(arr, low, high):
    pivot = random.randint(low, high)
    arr[pivot], arr[low] = arr[low], arr[pivot]
    return partition(arr, low, high)

def randomized_quicksort(arr, low, high):
    if low < high:
        mid = randomized_partition(arr, low, high)
        randomized_quicksort(arr, low, mid - 1)
        randomized_quicksort(arr, mid + 1, high)


if __name__ == '__main__':
    arr = getrandata(20)
    print(arr)
    
    randomized_quicksort(arr, 0, len(arr) - 1)
    print(arr)


        
