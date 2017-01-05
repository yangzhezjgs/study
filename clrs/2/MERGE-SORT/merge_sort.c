#include <stdio.h>
#include <stdlib.h>

void merge(int a[], int p, int q, int r)
{
    int i = p;
    int j = q + 1;
    int k = 0;
    int *b;

    b = (int *) malloc((r - p + 1) * sizeof(int));
    if (!b)
        return;

    while (i <= q && j <= r)
        b[k++] = (a[i] < a[j]) ? a[i++] : a[j++];

    while (i <= q)
        b[k++] = a[i++];

    while (j <= r)
        b[k++] = a[j++];

    for (i = p, j = 0; i <= r; i++, j++)
        a[i] = b[j];
}

void merge_sort(int a[], int p, int r)
{
    int q;
    if (p < r) {
        q = (p + r) / 2;
        merge_sort(a, p, q);
        merge_sort(a, q+1, r);
        merge(a, p, q, r);
    }
}

void print_array(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}


int main()
{
    int a[] = {2, 5, 1, 6, 1, 5, 9, 4, 3, 7};
    print_array(a, 10);

    merge_sort(a, 0, 9);
    print_array(a, 10);

    return 0;
}






