#!/usr/bin/env python
from randata import getrandata
from timing import timing

@timing
def select_sort(arr):
    length = len(arr)
    for i in range(length-1):
        small = i
        for j in range(i, length):
            if arr[j] < arr[small]:
                small = j
        arr[i], arr[small] = arr[small], arr[i]

if __name__ == '__main__':
    arr = getrandata(5000)
    select_sort(arr)
    print(arr)

