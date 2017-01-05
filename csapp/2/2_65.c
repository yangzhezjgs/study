#include <stdio.h>

int even_ones(unsigned x)
{
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    
    return !(x & 0x1);
}

int main(void)
{
    unsigned x = 0xcb;
    unsigned y = 0xf0f0;

    printf("sizeof(int): %lu\n", sizeof(int));
    printf("%d\n%d\n", even_ones(x), even_ones(y));
    return 0;
}

