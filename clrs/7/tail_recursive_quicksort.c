#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EXCHANGE(i, j) { int tmp = i; i = j; j = tmp; }

int partition(int *arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    int j, temp;

    for (j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            EXCHANGE(arr[i], arr[j]);
        }
    }
    arr[high] = arr[i + 1];
    arr[i + 1] = pivot;
    return i + 1;
}

void quicksort(int *arr, int low, int high)
{
    int mid, pivot;
    while (low < high) {
        pivot = partition(arr, low, high);
        mid = (low + high) / 2;
        if (pivot <= mid) {
            quicksort(arr, low, pivot - 1);
            low = pivot + 1;
        } else {
            quicksort(arr, pivot + 1, high);
            high = pivot - 1;
        }
    }
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
    int arr[] = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};
    print_arr(arr, 12);

    partition(arr, 0, 11);
    print_arr(arr, 12);

    quicksort(arr, 0, 11);
    print_arr(arr, 12);

    return 0;
}

        
