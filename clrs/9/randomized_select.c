#include <stdlib.h>
#include <time.h>

#define SWAP(a, b, t)   \
    do {                \
        t temp = a;     \
        a = b;          \
        b = temp;       \
    } while (0)

int
randomized_partition(int buf[], int low, int high)
{
    int pivot, i, j;

    srand((unsigned) time(NULL));
    pivot = low + rand() % (high - low + 1);
    SWAP(buf[pivot], buf[high], int);

    for (i = j = low; i < high; i++)
        if (buf[i] <= buf[high]) {
            SWAP(buf[i], buf[j], int);
            j++;
        }
    SWAP(buf[j], buf[high], int);

    return j;
}

int
recursive_randomized_select(int buf[], int low, int high, int i)
{
    int mid, k;

    if (low == high)
        return buf[low];

    mid = randomized_partition(buf, low, high);
    k = mid - low + 1;

    return (k == i) ? buf[mid] : 
    (k < i) ? recursive_randomized_select(buf, mid + 1, high, i - k) : 
    recursive_randomized_select(buf, low, mid - 1, i);
}

int
iterative_randomized_select(int buf[], int low, int high, int i)
{
    int mid, k;

    do {
        mid = randomized_partition(buf, low, high);
        k = mid - low + 1;
        if (k > i)
            high = mid - 1;
        else if (k < i) {
            low = mid + 1;
            i -= k;
        }
    } while (k != i);

    return buf[mid];
}


