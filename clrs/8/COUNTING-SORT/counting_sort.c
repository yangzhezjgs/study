#include <stdio.h>
#include <stdlib.h>
#include <data.h>

void counting_sort(int *src, int *dst, int n, int k)
{
    int *buf;
    buf = (int *) calloc(k+1, sizeof(int)); //初始化为0
    if (!buf)
        return;
    int i;
/*    for (i = 0; i <= k; i++) {
        buf[i] = 0;
    } */
    for (i = 0; i < n; i++) {
        buf[src[i]]++;
    }
    for (i = 1; i <= k; i++) {
        buf[i] += buf[i-1];
    }
    for (i = n - 1; i >= 0; i--) {
        dst[buf[src[i]]-1] = src[i];   //需要-1
        buf[src[i]]--;
    }
}

void counting_sort_in_place(int *arr, int n, int max)
{
    int *buf;
    int i, j, k = 0;
    buf = (int *) calloc(max+1, sizeof(int));
    if (!buf)
        return;
    for (i = 0; i < n; i++)
        buf[arr[i]]++;
    for (i = 0; i <= max; i++) {
        for (j = buf[i]; j > 0; j--) {
            arr[k++] = i;
        }
    }
}



    


int main()
{
    int *arr;
    arr = get_randata(10, 100);
    print_arr(arr, 10);
    counting_sort_in_place(arr, 10, 100);
    print_arr(arr, 10);

    return 0;
}


