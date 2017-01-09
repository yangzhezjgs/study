#include <stdint.h>
#include <string.h>

void
merge_sentinel(int buf[], int p, int q, int r)
{
    int L[q - p + 2];
    int R[r - q + 1];
    int i, j, k;

    memcpy(L, buf + p, sizeof(int) * (q - p + 1));
    memcpy(R, buf + q + 1, sizeof(int) * (r - q));
    L[q - p + 1] = R[r - q] = INT32_MAX;

    for (i = j = 0, k = p; k <= r; k++) {
        if (L[i] < R[j]) {
            buf[k] = L[i];
            i++;
        } else {
            buf[k] = R[j];
            j++;
        }
    }
}

void
merge(int buf[], int p, int q, int r)
{
    int L[q - p + 1];
    int R[r - q];
    int i, j, k;

    memcpy(L, buf + p, sizeof(int) * (q - p + 1));
    memcpy(R, buf + q + 1, sizeof(int) * (r - q));

    for (i = j = 0, k = p; k <= r && i < q - p + 1 && j < r - q; k++) {
        if (L[i] < R[j]) {
            buf[k] = L[i];
            i++;
        } else {
            buf[k] = R[j];
            j++;
        }
    }

    for (; i < q - p + 1; i++)
        buf[k++] = L[i];
    for (; j < r - q; j++)
        buf[k++] = R[j];
}

void
merge_sort(int buf[], int p, int r)
{
    if (p < r) {
        int q = (p + r) / 2;

        merge_sort(buf, p, q);
        merge_sort(buf, q + 1, r);
        merge(buf, p, q, r);
    }
}

void
merge_insertion_sort(int buf[], int p, int r, int n)
{
    if (r - p > n) {
        int q = (p + r) / 2;

        merge_insertion_sort(buf, p, q, n);
        merge_insertion_sort(buf, q + 1, r, n);
        merge(buf, p, q, r);
    } else if (p < r) {
        int i, j, k, key;

        for (i = p + 1; i <= r; i++) {
            key = buf[i];
            for (j = i - 1; j >= p && buf[j] > key; j--)
                buf[j + 1] = buf[j];

            buf[j + 1] = key;
        }
    }
}

