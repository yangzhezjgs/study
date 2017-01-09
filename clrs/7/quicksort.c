#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SWAP(a, b, t)   \
    do {                \
        t temp = a;     \
        a = b;          \
        b = temp;       \
    } while (0)         \

int
partition(int buf[], int low, int high)
{
    int i, j, pivot;

    pivot = buf[high];
    i = low;
    for (j = low; j < high; j++)
        if (buf[j] <= pivot) {
            SWAP(buf[i], buf[j], int);
            i++;
        }
    SWAP(buf[i], buf[high], int);

    return i;
}

int
hoare_partition1(int buf[], int low, int high)
{
    int pivot = buf[low];

    while (1) {
        while (buf[high] > pivot)
            high--;
        while (buf[low] < pivot)
            low++;
        if (low < high) {
            SWAP(buf[low], buf[high], int);
            low++;
            high--;
        } else
            return high;
    }
}

int
hoare_partition2(int buf[], int low, int high)
{
    int pivot, i, j;

    pivot = buf[low];
    i = low - 1;
    j = high + 1;

    while (1) {
        do {
            j--;
        } while (buf[j] > pivot);

        do {
            i++;
        } while (buf[i] < pivot);

        if (i < j)
            SWAP(buf[i], buf[j], int);
        else {
            return j;
        }
    }
}


int
hoare_partition3(int buf[], int low, int high)
{
    int pivot = buf[low];
    int i = low, j = high;
    while (i < j) {
        while (i < j && buf[j] >= pivot)
            j--;
        buf[i] = buf[j];
        while (i < j && buf[i] <= pivot)
            i++;
        buf[j] = buf[i];
    }
    buf[i] = pivot;
    return i;

}

void
quicksort(int buf[], int low, int high)
{
    int mid, temp;
    int i;

    if (low < high) {
        mid = hoare_partition3(buf, low, high);
        quicksort(buf, low, mid - 1);
        quicksort(buf, mid+1, high);
    }
}


