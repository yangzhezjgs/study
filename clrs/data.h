#ifndef _DATA_H_
#define _DATA_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *get_randata(int n, int max) 
{
    int *buf, i;
    buf = (int *) calloc(n, sizeof(int));
    if (!buf)
        return NULL;
    srand((unsigned) time(NULL));
    for (i = 0; i < n; i++) {
        buf[i] = rand() % (max + 1);
    }
    return buf;
}

void print_arr(int *arr, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

#endif
