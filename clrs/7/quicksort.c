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
    int mid;
    if (low < high) {
        mid = partition(arr, low, high);
        quicksort(arr, low, mid - 1);
        quicksort(arr, mid + 1, high);
    }
}

int randomized_partition(int *arr, int low, int high)
{
    srand((unsigned) time(NULL));
    int pivot = rand() % (high - low + 1) + low;
    EXCHANGE(arr[pivot], arr[high]);
    return partition(arr, low, high);
}

int randomized_quicksort(int *arr, int low, int high)
{
    int mid;
    if (low < high) {
        mid = randomized_partition(arr, low ,high);
        randomized_quicksort(arr, low, mid - 1);
        randomized_quicksort(arr, mid + 1, high);
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

    randomized_partition(arr, 0, 11);
    print_arr(arr, 12);

    randomized_quicksort(arr, 0, 11);
    print_arr(arr, 12);

    return 0;
}

        
