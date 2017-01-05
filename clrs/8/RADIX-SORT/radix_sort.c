#include <stdio.h>
#include "data.h"

void counting_sort(int *arr, int n, int exp)
{
    int i;
    int cnt[10] = { 0 };
    int result[n];

//    for (i = 0; i < base; i++)
//        cnt[i] = 0;

    for (i = 0; i < n; i++)
        cnt[arr[i] / exp % 10]++;

    for (i = 1; i < 10; i++)
        cnt[i] += cnt[i-1];

    for (i = n - 1; i >= 0; i--) {
        result[cnt[arr[i] / exp % 10]-1] = arr[i];
        cnt[arr[i] / exp % 10]--;
    }
    for (i = 0; i < n; i++)
        arr[i] = result[i];
}

int get_max(int *arr, int n)
{
    int i;
    int max = arr[0];
    for (i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}


void radix_sort(int *arr, int n)
{
    int max = get_max(arr, n);
    int exp;

    for (exp = 1; max / exp > 0; exp *= 10) {
        counting_sort(arr, n, exp);
    }
}

int main(void)
{
    int *arr;
    arr = get_randata(1000, 10000);
    print_arr(arr, 1000);

    radix_sort(arr, 1000);
    print_arr(arr, 1000);
    return 0;
}


