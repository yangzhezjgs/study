#include <stdio.h>

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int a[], int length)
{
    int i, j;

    for (i = 0; i < length - 1; i++) {
        for (j = length - 1; j > i; j--) {
            if (a[j] < a[j - 1])
                swap(a + j, a + j - 1);
        }
    }
}

int main()
{
    int a[] = {3, 4, 1, 5, 7, 2, 3, 1, 5, 9};
    int i;
    
    for (i = 0; i < 10; i++)
        printf("%d ", a[i]);
    printf("\n");

    bubble_sort(a, 10);
    for (i = 0; i < 10; i++)
        printf("%d ", a[i]);
    printf("\n");
    
    return 0;
}

    



    
