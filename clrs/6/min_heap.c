#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define PARENT(i) (((i) - 1) / 2)
#define LEFT(i) ((i) * 2 + 1)
#define RIGHT(i) ((i) * 2 + 2)

typedef struct {
    int *elements;
    int length;
    int heap_size;
} heap;

int heap_minimum(heap *h)
{
    return h->elements[0];
}


void min_heapify(heap *h, int i)
{
    int left = LEFT(i),
        right = RIGHT(i),
        temp,
        smallest;

    if (left < h->heap_size && h->elements[left] < h->elements[i]) {
        smallest = left;
    } else {
        smallest = i;
    }
    if (right < h->heap_size && h->elements[right] < h->elements[smallest]) {
        smallest = right;
    }
    if (smallest != i) {
        temp = h->elements[i];
        h->elements[i] = h->elements[smallest];
        h->elements[smallest] = temp;
        min_heapify(h, smallest);
    }
}

int heap_extract_min(heap *h)
{
    if (h->heap_size < 1) {
        fprintf(stderr, "heap underflow\n");
    }
    int min = h->elements[0];
    h->elements[0] = h->elements[h->heap_size - 1];
    h->heap_size--;
    min_heapify(h, 0);
    return min;
}

void heap_decrease_key(heap *h, int i, int key)
{
    if (h->elements[i] <= key) {
        fprintf(stderr, "new key should be smaller than current key\n");
    }
    while (i > 0 && h->elements[PARENT(i)] > key) {
        h->elements[i] = h->elements[PARENT(i)];
        i = PARENT(i);
    }
    h->elements[i] = key;
}

void min_heap_insert(heap *h, int key)
{
    if (h->heap_size == h->length) {
        fprintf(stderr, "heap overflow");
    }
    h->elements[h->heap_size] = INT_MAX;
    h->heap_size++;
    heap_decrease_key(h, h->heap_size - 1, key);
}

void build_min_heap(heap *h)
{
    int i;
    h->heap_size = 1;
    for (i = 1; i < h->length; i++) {
        min_heap_insert(h, h->elements[i]);
    }
}

void print_heap(heap *h)
{
    int i;
    for (i = 0; i < h->heap_size; i++) {
        printf("%d ", h->elements[i]);
    }
    printf("\n");
}

int main()
{
    int arr[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    heap h = {arr, 10, 0};

    build_min_heap(&h);
    print_heap(&h);

    return 0;
}



