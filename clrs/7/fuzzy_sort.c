#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define SWAP(a, b, t)   \
    do {                \
        t temp = a;     \
        a = b;          \
        b = temp;       \
    } while (0)

#define LESS(a, b) ((a).high < (b).low)
#define MORE(a, b) ((a).low > (b).high)
#define EQUAL(a, b) (((a).low <= (b).high && (a).high >= (b).low) ||    \
                     ((b).low <= (a).high && (b).high >= (a).low))

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct interval {
    int low;
    int high;
} interval;

interval
fuzzy_partition(interval buf[], int low, int high)
{
    interval equal, intersection;
    int i, j, pivot;

    srand((unsigned) time(NULL));
    pivot = low + rand() % (high - low + 1);
    SWAP(buf[pivot], buf[high], interval);

    for (i = j = low; j < high; j++)
        if (LESS(buf[j], buf[high])) {
            SWAP(buf[j], buf[i], interval);
            i++;
        }

    intersection = buf[high];
    equal.low = i;
    for (j = i; j <= high; j++)
        /* 相等没有传递性，需要求交集 */
        if (EQUAL(intersection, buf[j])) {
            intersection.low = MAX(buf[j].low, intersection.low);
            intersection.high = MIN(buf[j].high, intersection.high);
            SWAP(buf[i], buf[j], interval);
            i++;
        }
    equal.high = i - 1;

    return equal;
}

void
fuzzy_sort(interval buf[], int low, int high)
{
    interval mid;

    if (low < high) {
        mid = fuzzy_partition(buf, low, high);
        fuzzy_sort(buf, low, mid.low - 1);
        fuzzy_sort(buf, mid.high + 1, high);
    }
}

int
main(void)
{
    int i;
    interval buf[] = {
        {1, 2},
        {3, 4},
        {5, 6},
        {6, 7}
    };

    fuzzy_sort(buf, 0, 3);

    for (i = 0; i < 4; i++)
        printf("(%d, %d)\n", buf[i].low, buf[i].high);

    return 0;
}
