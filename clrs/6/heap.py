#!/usr/bin/env python

class Heap:
    def __init__(self, items, size = None):
        self.items = items
        self.heap_size = size or len(items)

    def __getitem__(self, key):
        return self.items[key]

    def __setitem__(self, key, val):
        self.items[key] = val

    def __len__(self):
        return len(self.items)

    def __str__(self):
        return str(self.items)
            
    __repr__ = __str__


def left(i):
    return i * 2 + 1

def right(i):
    return i * 2 + 2

def parent(i):
    return (i - 1) // 2

def max_heapify(A, i):
    l = left(i)
    r = right(i)

    if l < A.heap_size and A[l] > A[i]:
        largest = l
    else:
        largest = i
    if r < A.heap_size and A[r] > A[largest]:
        largest = r
    if largest != i:
        A[i], A[largest] = A[largest], A[i]
        max_heapify(A, largest)

def build_max_heap(A):
    A.heap_size = len(A)
    for i in range((A.heap_size - 1) // 2, -1, -1):
        max_heapify(A, i)

def heapsort(A):
    A.heap_size = len(A)
    build_max_heap(A)
    for i in range(len(A) - 1, 0, -1):
        A[0], A[A.heap_size - 1] = A[A.heap_size - 1], A[0]
        A.heap_size -= 1
        max_heapify(A, 0)

def heap_maximum(A):
    return A[0]

def heap_extract_max(A):
    if A.heap_size < 1:
        raise Exception("heap underflow")
    max = A[0]
    A[0] = A[A.heap_size - 1]
    A.heap_size -= 1
    max_heapify(A, 0)
    return max

def heap_increase_key(A, i, key):
    if key <= A[i]:
        raise Exception("new key should be bigger than current key")
    A[i] = key
    while i > 0 and A[parent(i)] < A[i]:
        A[i], A[parent(i)] = A[parent(i)], A[i]
        i = parent(i)

def max_heap_insert(A, key):
    A.heap_size += 1
    A[A.heap_size - 1] = float("-inf")
    heap_increase_key(A, A.heap_size - 1, key)

def build_max_heap2(A):
    A.heap_size = 1
    for i in range(1, len(A)):
        max_heap_insert(A, A[i])

       
if __name__ == "__main__":
    arr = [4, 1, 3, 2, 16, 9, 10, 14, 8, 7]
    heap = Heap(arr)
    print(heap)

    build_max_heap2(heap)
    print(heap)
    





        
