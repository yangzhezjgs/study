#include <string.h>

/* θ(size + max)*/
void
counting_sort(int src[], int size, int digit)
{
    int buf[10], res[size], i, exp;

    for (exp = i = 1; i < digit; i++)
        exp *= 10;

    memset(buf, 0, sizeof(int) * 10);
    for (i = 0; i < size; i++)
        buf[src[i] / exp % 10]++;
    for (i = 1; i < 10; i++)
        buf[i] += buf[i - 1];
    for (i = size - 1; i >= 0; i--) {
        res[buf[src[i] / exp % 10] - 1] = src[i];
        buf[src[i] / exp % 10]--;
    }

    memcpy(src, res, sizeof(int) * size);

}

/* 以十为底的基数 */
void
radix_sort(int buf[], int size, int digit)
{
    int i, exp;

    for (i = 1; i <= digit; i++)
        counting_sort(buf, size, i);
}
