#include <stdio.h>

void inplace_swap(int *x, int *y)
{
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}

int main(void)
{
    int a = 1;
    int b = 2;

    printf("a: %d\n", a);
    printf("b: %d\n", b);

    inplace_swap(&a, &b);

    printf("a: %d\n", a);
    printf("b: %d\n", b);

    return 0;
}

