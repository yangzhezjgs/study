#include <time.h>
#include <stdlib.h>

#define SWAP(a, b, t)   \
    do {                \
        t temp = a;     \
        a = b;          \
        b = temp;       \
    } while (0)

typedef struct part {
    int low;
    int high;
} part;

/* θ(high - low + 1) */
part
equal_partition(int buf[], int low, int high)
{
    part p;
    int i, pivot;

    srand((unsigned) time(NULL));
    pivot = low + rand() % (high - low + 1);
    SWAP(buf[pivot], buf[high], int);

    p.low = low;
    p.high = high - 1;
    /* p.high之后都是比pivot大的，不需要比较 */
    for (i = low; i <= p.high; i++)
        if (buf[i] < buf[high]) {
            /* p.low之前的都是比pivot小的，p.low是相等的或是正在比较的(p.low == i) */
            SWAP(buf[i], buf[p.low], int);
            p.low++;
        } else if (buf[i] > buf[high]) {
            /* p.high未知，需要比较，所以i-- */
            SWAP(buf[i], buf[p.high], int);
            p.high--;
            i--;
        }

    p.high++;
    SWAP(buf[high], buf[p.high], int);

    return p;
}

part
equal_partition_2(int buf[], int low, int high)
{
    part p;
    int i, j, pivot;

    srand((unsigned) time(NULL));
    pivot = low + rand() % (high - low + 1);
    SWAP(buf[pivot], buf[high], int);

    for (i = j = low; j < high; j++)
        if (buf[j] <= buf[high]) {
            SWAP(buf[j], buf[i], int);
            i++;
        }
    SWAP(buf[i], buf[high], int);

    p.high = i;
    /* 交换比较过的元素就不需要再处理，如果交换未比较的元素，仍需要比较 */
    for (i = j = p.high - 1; j >= low; j--)
        if (buf[j] == buf[p.high]) {
            SWAP(buf[j], buf[i], int);
            i--;
        }
    p.low = i + 1;

    return p;
}


void
equal_quicksort(int buf[], int low, int high)
{
    part p;

    if (low < high) {
        p = equal_partition_2(buf, low, high);
        equal_quicksort(buf, low, p.low - 1);
        equal_quicksort(buf, p.high + 1, high);
    }
}
