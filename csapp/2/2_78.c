#include <stdio.h>
#include <limits.h>

int mul5div8(int x)
{
    return ((x << 2) + x) >> 3;
}

int main(void)
{
    int x = 2;
    
    printf("5 * %d / 8 = %d\n", x, mul5div8(x));
    printf("5 * %d / 8 = %d\n", INT_MAX, mul5div8(INT_MAX));

    return 0;
}

