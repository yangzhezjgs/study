#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define PARENT(i) ((i - 1) / 2)
#define LEFT(i) ((i) * 2 + 1)
#define RIGHT(i) ((i) * 2 + 2)

typedef struct {
    int *nodes;
    int heap_size;
    int length;
} heap;

void max_heapify(heap *A, int i)
{
    int l, r, largest, temp;
    while (1) {
        l = LEFT(i);
        r = RIGHT(i);

        if (l < A->heap_size && A->nodes[l] > A->nodes[i]) {
            largest = l;
        } else {
            largest = i;
        }
        if (r < A->heap_size && A->nodes[r] > A->nodes[largest]) {
            largest = r;
        }
        if (largest == i) {
            return;
        } else {
            temp = A->nodes[i];
            A->nodes[i] = A->nodes[largest];
            A->nodes[largest] = temp;
            i = largest;
        }
    }
}

void build_max_heap(heap *A)
{
    int i;
    A->heap_size = A->length;

    for (i = (A->length - 1) / 2; i >= 0; i--)
        max_heapify(A, i);
}

void heapsort(heap *A)
{
    int i, temp;
    A->heap_size = A->length;
    build_max_heap(A);
    for (i = A->heap_size - 1; i > 0; i--) {
        temp = A->nodes[0];
        A->nodes[0] = A->nodes[i];
        A->nodes[i] = temp;
        A->heap_size--;
        max_heapify(A, 0);
    }
}

void print_arr(int *arr, int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int heap_maximum(heap *A)
{
    return A->nodes[0];
}

int heap_extract_max(heap *A)
{
    if (A->heap_size < 1) {
        fprintf(stderr, "heap underflow");
        exit(0);
    }
    int max = A->nodes[0];
    A->nodes[0] = A->nodes[A->heap_size - 1];
    A->heap_size--;
    max_heapify(A, 0);
    return max;
}

void heap_increase_key(heap *A, int i, int key)
{
    if (A->nodes[i] >= key) {
        fprintf(stderr, "new key should be bigger than current key");
        exit(0);
    }
    while (i > 0 && A->nodes[PARENT(i)] < key) {
        A->nodes[i] = A->nodes[PARENT(i)];
        i = PARENT(i);
    }
    A->nodes[i] = key;
}

void max_heap_insert(heap *A, int key)
{
    if (A->length == A->heap_size) {
        fprintf(stderr, "heap overflow");
        exit(0);
    }
    A->nodes[A->heap_size] = INT_MIN;
    A->heap_size++;
    heap_increase_key(A, A->heap_size - 1, key);
}

void heap_delete(heap *A, int i)
{
    if (i >= A->heap_size) {
        fprintf(stderr, "heap overflow");
        exit(0);
    }
    A->nodes[i] = A->nodes[A->heap_size - 1];
    A->heap_size--;
    max_heapify(A, i);
}

void build_max_heap_2(heap *A)
{
    int i;
    A->heap_size = 0;
    for (i = 0; i < A->length; i++) {
        max_heap_insert(A, A->nodes[i]);
    }
}

int main()
{
    int i = 0;
    int arr[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    heap A = {arr, 0, 10};
    print_arr(arr, 10);

    build_max_heap(&A);
    print_arr(A.nodes, 10);
    heap_delete(&A, 5);
    print_arr(A.nodes, A.heap_size);
    return 0;
}

