#include <stdlib.h>
#include <time.h>

#define SWAP(a, b, t)   \
    do {                \
        t temp = a;     \
        a = b;          \
        b = temp;       \
    } while (0)

int
median_partition(int buf[], int low, int high)
{
    int i, j, pivot;

    srand((unsigned) time(NULL));
    i = low + rand() % (high - low + 1);
    j = low + rand() % (high - low + 1);
    pivot = low + rand() % (high - low + 1);
    
    if ((buf[i] <= buf[j] && buf[i] >= buf[pivot]) || 
        (buf[i] >= buf[j] && buf[i] <= buf[pivot]))
        pivot = i;
    else if ((buf[j] <= buf[i] && buf[j] >= buf[pivot]) ||
             (buf[j] >= buf[i] && buf[j] <= buf[pivot]))
        pivot = j;

    SWAP(buf[pivot], buf[high], int);
    for (i = j = low; j < high; j++)
        if (buf[j] <= buf[high]) {
            SWAP(buf[j], buf[i], int);
            i++;
        }
    SWAP(buf[high], buf[i], int);

    return i;
}

void
median_quicksort(int buf[], int low, int high)
{
    int mid;

    if (low < high) {
        mid = median_partition(buf, low, high);
        median_quicksort(buf, low, mid - 1);
        median_quicksort(buf, mid + 1, high);
    }
}
