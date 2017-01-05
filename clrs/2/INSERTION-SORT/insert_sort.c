#include <stdio.h>

void insert_sort(int a[], int n)
{
    int i, j, key;

    for (j = 1; j < n; j++) {
        key = a[j];
        i = j - 1;
        while (i >= 0 && a[i] > key) {
            a[i + 1] = a[i];
            i--;
        }
        a[i + 1] = key;
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
    int a[] = {5, 3, 2, 7, 1, 3};

    print_array(a, 6);

    insert_sort(a, 6);
    print_array(a, 6);

    return 0;
}

    




