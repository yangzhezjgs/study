#include <stdio.h>

int fits_bits(int x, int n)
{
    unsigned mask = x >> n;

    return !(~mask) || !mask; //neg: all 1; pos: all 0;
}

void test(int x, int n)
{
    printf("%x %d: %d\n", x, n, fits_bits(x, n));
}

int main(void)
{
    test(-100, 5);
    test(15, 3);
    return 0;
}

