#include <string.h>
#include <stdio.h>

/* 需要排序。如果不排序，需要使用左边的每一个元素和右边的元素比较，总的时间变为O(n^2lgn) */
int 
merge_inversion(int buf[], int low, int mid, int high)
{
    int l[mid - low + 1];
    int r[high - mid];
    int i, j, k, count;

    memcpy(l, buf + low, sizeof(int) * (mid - low + 1));
    memcpy(r, buf + mid + 1, sizeof(int) * (high - mid));

    count = 0;
    for (i = j = 0, k = low; i < mid - low + 1 && j < high - mid; k++)
        if (l[i] <= r[j]) {
            buf[k] = l[i];
            i++;
        } else {
            buf[k] = r[j];
            j++;
            count += mid - low - i + 1;
        }

    for (; i < mid - low + 1; i++, k++)
        buf[k] = l[i];

    for (; j < high - mid; j++, k++)
        buf[k] = r[j];

    return count;
}

int
inversion_count(int buf[], int low, int high)
{
    int mid, count;

    count = 0;
    if (low < high) {
        mid = (low + high) / 2;

        count += inversion_count(buf, low, mid);
        count += inversion_count(buf, mid + 1, high);
        count += merge_inversion(buf, low, mid, high);
    }

    return count;
}

int
main(void)
{
    int buf[] = { 2, 3, 8, 6, 1 };

    int count = inversion_count(buf, 0, 4);

    printf("%d\n", count);
}
