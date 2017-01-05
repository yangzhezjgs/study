#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(a, b) { int tmp = a; a = b; b = tmp; }

typedef struct {
    int low;
    int high;
} pivot_t;

pivot_t partition(int *arr, int low, int high)
{
    int x = arr[high],
        i = low - 1,
        j;
    for (j = low; j < high; j++) {
        if (arr[j] < x) {
            i++;
            SWAP(arr[i], arr[j]);
        }
    }
    int s = i + 1;
    for (j = s; j <= high; j++) {
        if (arr[j] == x) {
            i++;
            SWAP(arr[j], arr[i]);
        }
    }
    pivot_t result = {s, i};
    return result;
}

pivot_t randomized_partition(int *arr, int low, int high)
{
    srand((unsigned) time(NULL));
    int pivot = low + rand() % (high - low + 1);
    SWAP(arr[pivot], arr[high]);
    return partition(arr, low, high);
}

void quicksort(int *arr, int low, int high)
{
    if (low < high) {
        pivot_t pivot = randomized_partition(arr, low ,high);
        quicksort(arr, low, pivot.low - 1);
        quicksort(arr, pivot.high + 1, high);
    }
}

int *get_randata(int n)
{
    int *buf;
    buf = (int *) calloc(n, sizeof(int));
    if (!buf)
        return NULL;
    int i;
    srand((unsigned) time(NULL));
    for (i = 0; i < n; i++) {
        buf[i] = rand() % 100;
    }
    return buf;
}

void print_arr(int *arr, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void)
{
    int *arr;
    arr = get_randata(20);
    if (arr) {
        print_arr(arr, 20);
        int arr2[] = {1, 1, 1, 1, 1, 1, 1, 1};
        pivot_t result = randomized_partition(arr2, 0, 8);
        print_arr(arr, 20);
        printf("pivot:%d %d\n", result.low, result.high);
        quicksort(arr, 0, 10);
        print_arr(arr, 20);
    }
    return 0;
}

