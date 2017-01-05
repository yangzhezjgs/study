#include <stdio.h>

int bit_a(int n)
{
    return ~0 << n;
}

int bit_b(int m, int n)
{
    return (1 << n + m) - (1 << m);
}

int main(void)
{
    printf("%x\n%x\n", bit_a(2), bit_b(2, 3));

    return 0;
}
