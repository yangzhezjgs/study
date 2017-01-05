#include <stdio.h>

int any_even_one(unsigned x)
{
    return !!(x & 0x55555555);
}

int main(void)
{
    int x = 0x4;

    printf("%d\n", any_even_one(x));

    return 0;
}
