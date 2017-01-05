#include <stdio.h>

int leftmost_one(unsigned x)
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x ^= x >> 1;
    return x;
}

int main(void)
{
    printf("%x\n%x\n", leftmost_one(0xff00), leftmost_one(0x6600));
    return 0;
}
