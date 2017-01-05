#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(a, b) { int tmp = a; a = b; b = tmp; }
#define N 0

int hoare_partition(int *arr, int low, int high)
{
    int x = arr[low],
        i = low - 1,
        j = high + 1;
    while (1) {
        do {
            j--;
        } while (arr[j] > x);
        do {
            i++;
        } while (arr[i] < x);
        if (i < j) {
            SWAP(arr[i], arr[j]);
        } else {
            return j;
        }
    }
}

void hoare_quicksort(int *arr, int low, int high)
{
    if (low < high) {
        int mid = hoare_partition(arr, low, high);
        hoare_quicksort(arr, low, mid);
        hoare_quicksort(arr, mid + 1, high);
    }
}

int *get_randata(int n)
{
    int *buf, i;
    buf = (int *) calloc(n, sizeof(int));
    if (!buf) {
        return NULL;
    }
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
    arr = get_randata(N);
    if (arr) {
        int arr2[] = {1, 1, 1, 1, 1};
        print_arr(arr, N);
        hoare_quicksort(arr, 0, N - 1);
        print_arr(arr, N);
        print_arr(arr2, 5);
        hoare_quicksort(arr2, 0, 4);
        print_arr(arr2, 5);
    }

    return 0;
}

