#include <stdio.h>

int horner(int a[], int x, int length)
{
    int i;
    int y;

    for (i = length - 1; i >= 0; i--)
        y = a[i] + x * y;
    return y;
}

int main()
{
    int a[] = {1, 2, 3};
    int x = 2;

    printf("x = %d, y = %d\n", x, horner(a, x, 3));

    return 0;
}
