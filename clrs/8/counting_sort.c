#include <string.h>

/* θ(size + max)*/
void
counting_sort(int src[], int dst[], int size, int max)
{
    int buf[max + 1], i;

    memset(buf, 0, sizeof(int) * (max + 1));
    for (i = 0; i < size; i++)
        buf[src[i]]++;
    for (i = 1; i <= max; i++)
        buf[i] += buf[i - 1];
    /* 从后向前，保证稳定 */
    for (i = size - 1; i >= 0; i--) {
        dst[buf[src[i]] - 1] = src[i];
        buf[src[i]]--;
    }
}

int
count_a2b(int buf[], int size, int max, int a, int b)
{
    int arr[max + 1], i;

    /* θ(size + max) */
    memset(arr, 0, sizeof(int) * (max + 1));
    for (i = 0; i < size; i++)
        arr[buf[i]]++;
    for (i = 1; i <= max; i++)
        arr[i] += arr[i - 1];
    
    /* θ(1) */
    return (arr[b] - arr[a - 1]);
}
