#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define SWAP(a, b) { tmp = a; a = b; b = tmp; }

typedef struct {
    int left;
    int right;
} interval;

bool before(interval a, interval b)
{
    return a.right < b.left;
}

bool after(interval a, interval b)
{
    return a.left > b.right;
}

bool intersect(interval a, interval b)
{
    return (a.right >= b.left) && (a.left <= b.right);
}

interval partition(interval *arr, int low, int high)
{
    interval intersection = arr[high], tmp;
    int i = low - 1;
    int j;
    
    for (j = low; j < high; j++) {
        if (intersect(intersection, arr[j])) {
            if (intersection.left < arr[j].left) {
                intersection.left = arr[j].left;
            }
            if (intersection.right > arr[j].right) {
                intersection.right = arr[j].right;
            }
        }
    }

    for (j = low; j < high; j++) {
        if (before(arr[j], intersection)) {
            i++;
            SWAP(arr[j], arr[i]);
        }
    }
    int s = i + 1;
    for (j = s; j <= high; j++) {
        if (intersect(intersection, arr[j])) {
            i++;
            SWAP(arr[j], arr[i]);
        }
    }

    return (interval) {s, i};
}

void quicksort(interval *arr, int low, int high)
{
    if (low < high) {
        interval pivot = partition(arr, low, high);
        quicksort(arr, low, pivot.left - 1);
        quicksort(arr, pivot.right + 1, high);
    }
}

void print_interval(interval *arr, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        printf("[%d, %d] ", arr[i].left, arr[i].right);
    }
    printf("\n");
}

interval *get_rand_interval(int n, int bound)
{
    interval *buf;
    buf = (interval *) calloc(n, sizeof(interval));
    if (!buf)
        return NULL;
    srand((unsigned) time(NULL));
    int left, right, i;

    for (i = 0; i < n; i++) {
        left = rand() % bound;
        right = rand() % bound;
        if (left < right) {
            buf[i].left = left;
            buf[i].right = right;
        } else {
            buf[i].left = right;
            buf[i].right = left;
        }
    }
    return buf;
}

            

int main(void)
{
    interval *arr = get_rand_interval(10, 100);
    if (arr) {
        print_interval(arr, 10);
        quicksort(arr, 0, 9);
        print_interval(arr, 10);
    }
    return 0;
}


