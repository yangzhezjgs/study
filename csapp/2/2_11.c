#include <stdio.h>

void inplace_swap(int *x, int *y)
{
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}

void reverse_array(int a[], int cnt)
{
    int first, last;

    for (first = 0, last = cnt - 1;
         first < last;                     //当相等时异或为0
         first++, last--)
        inplace_swap(&a[first], &a[last]);
}

void print_array(int a[], int len)
{
    int i;
    
    for (i = 0; i < len; i++)
        printf(" %d", a[i]);
    printf("\n");
}

int main(void)
{
    int a[] = {1, 2, 3, 4};
    int b[] = {1, 2, 3, 4, 5};

    printf("a[4]: ");
    print_array(a, 4);

    printf("b[5]: ");
    print_array(b, 5);

    reverse_array(a, 4);
    reverse_array(b, 5);

    printf("a[4]: ");
    print_array(a, 4);

    printf("b[5]: ");
    print_array(b, 5);

    return 0;
}







