#include <stdio.h>

void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void select_sort(int a[], int n)
{
    int i, j;
    int k = n - 1;
    int small;

    for (i = 0; i < k; i++) {
        small = i;
        j = i + 1;
        while (j < n) {
            if (a[j] < a[small])
                small = j;
            j++;
        }
        swap(a + i, a + small);
    }
}

int main()
{
    int a[] = {1, 4, 124, 9599, 9, 1, 40, 29};
    int i;
    
    select_sort(a, 8);
    for (i = 0; i < 8; i++)
        printf("%d ", a[i]);
    printf("\n");

    return 0;
}


        



