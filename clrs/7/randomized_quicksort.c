#include <stdlib.h>

#define SWAP(a, b, t)   \
    do {                \
        t temp = a;     \
        a = b;          \
        b = temp;       \
    } while (0)

int
partition(int buf[], int low, int high)
{
    int pivot, i, j;

    srand((unsigned) time(NULL));
    pivot = low + rand() % (high - low + 1);
    SWAP(buf[pivot], buf[high], int);

    for (i = j = low; j < high; j++) 
        if (buf[j] <= buf[high]) {
            SWAP(buf[j], buf[i], int);
            i++;
        }
    SWAP(buf[i], buf[high], int);

    return i;
}

void
randomized_quicksort(int buf[], int low, int high)
{
    int mid;

    if (low < high) {
        mid = partition(buf, low, high);
        randomized_quicksort(buf, low, mid - 1);
        randomized_quicksort(buf, mid + 1, high);
    }
}
