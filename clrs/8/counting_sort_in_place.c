#include <string.h>

void
counting_sort_in_place(int buf[], int size, int max)
{
    int i, j, count[max + 1];

    memset(count, 0, sizeof(int) * (max + 1));
    for (i = 0; i < size; i++)
        count[buf[i]]++;
    /* 用计数数组的下标和个数来排序 */
    for (i = j = 0; i <= max; i++)
        for (; count[i] > 0; count[i]--)
            buf[j++] = i;
}
