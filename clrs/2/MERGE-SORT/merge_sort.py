#!/usr/bin/env python
from randata import getrandata
from timing import timing

@timing
def merge_sort(arr):
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left = merge_sort(arr[: mid])
    right = merge_sort(arr[mid:])
    return merge(left, right)

def merge(left, right):
    result = []
    l_len = len(left)
    r_len = len(right)
    i, j = 0, 0
    
    while i < l_len and j < r_len:
        if left[i] < right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result += left[i:]
    result += right[j:]
    return result
    



if __name__ == '__main__':
    arr = getrandata(5)
    print(arr)
    print(merge_sort(arr))
    print(arr)





        


