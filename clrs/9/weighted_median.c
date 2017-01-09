#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(a, b, t)   \
    do {                \
        t temp = a;     \
        a = b;          \
        b = temp;       \
    } while (0)

typedef struct {
    double num;
    double weight;
} weighted_num;

int
randomized_partition(weighted_num buf[], int low, int high)
{
    int pivot, i, j;

    srand((unsigned) time(NULL));
    pivot = low + rand() % (high - low + 1);
    SWAP(buf[pivot], buf[high], weighted_num);

    for (i = j = low; i < high; i++)
        if (buf[i].num <= buf[high].num) {
            SWAP(buf[i], buf[j], weighted_num);
            j++;
        }
    SWAP(buf[j], buf[high], weighted_num);

    return j;
}

double
weighted_median(weighted_num buf[], int low, int high, double weight)
{
    int mid, i;
    double weight_sum;

    mid = randomized_partition(buf, low, high);
    weight_sum = 0;
    for (i = low; i < mid; i++)
        weight_sum += buf[i].weight;
    /* 按权重分 */
    if (weight_sum > weight)
        return weighted_median(buf, low, mid - 1, weight);
    else if (weight_sum + buf[mid].weight >= weight)
        return buf[mid].num;
    else
        weighted_median(buf, mid, high, weight - weight_sum);
}

int
main(void)
{
    weighted_num buf[] = {
        { 0.1, 0.1 },
        { 0.35, 0.35 },
        { 0.05, 0.05 },
        { 0.1, 0.1 },
        { 0.15, 0.15 },
        { 0.05, 0.05 },
        { 0.2, 0.2 }
    };
    double median;

    median = weighted_median(buf, 0, 6, 0.5);
    printf("%.2f\n", median);

    return 0;
}

