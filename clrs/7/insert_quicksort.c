#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EXCHANGE(a, b) { int tmp = a; a = b; b = tmp; }

int partition(int *arr, int low, int high)
{
    int i = low - 1,
        j, tmp,
        pivot = arr[high];
    for (j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            EXCHANGE(arr[j], arr[i]);
        }
    }
    EXCHANGE(arr[i + 1], arr[high]);
    return i + 1;
}

void limited_quicksort(int *arr, int low, int high, int treshold)
{
    if (high - low > treshold) {
        int mid = partition(arr, low, high);
        limited_quicksort(arr, low, mid - 1, treshold);
        limited_quicksort(arr, mid + 1, high, treshold);
    }
}

void insertion_sort(int *arr, int low, int high)
{
    int i, j, key;
    
    for (i = low + 1; i <= high; i++) {
        key = arr[i];
        for (j = i - 1; j >= low && arr[j] > key; j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = key;
    }
}

void quicksort(int *arr, int low, int high, int treshold)
{
    limited_quicksort(arr, low, high, treshold);
    insertion_sort(arr, low, high);
}

int *get_randata(int n)
{
    int *buf, i;
    buf = (int *) calloc(n, sizeof(int));
    if (!buf) {
        return NULL;
    }
    
    srand((unsigned) time(NULL));
    for (i = 0; i < n; i++)  {
        *(buf + i) = rand() % 100;
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


int main()
{
    int *arr;
    arr = get_randata(10);
    print_arr(arr, 10);

    partition(arr, 0, 9);
    print_arr(arr, 10);
    return 0;
}


    
