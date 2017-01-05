#!/usr/bin/env python
from timing import timing
from randata import getrandata
import time

@timing
def insert_sort(array):
    length = len(array)
    for i in range(1, length):
        key = array[i]
        j = i - 1
        while j >= 0 and array[j] > key:
            array[j+1] = array[j]
            j = j - 1
        array[j+1] = key

@timing
def insert_sort2(array):    
    ' faster '
    length = len(array)
    for i in range(1, length):
        j = i - 1
        while j >= 0 and array[j] < array[i]:
            j -= 1
        array.insert(j+1, array[i])
        array.pop(i+1)




if __name__ == '__main__':
    arr = getrandata(5000)
    start = time.clock()
    arr.sort(reverse=True)              #fastest
    end = time.clock()
    print(arr)
    print("%s: %fs" % (".sort()", end - start))

    insert_sort2(arr)
    print(arr)


    

