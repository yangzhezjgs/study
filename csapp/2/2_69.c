#include <stdio.h>

unsigned rotate_right(unsigned x, int n)
{
    unsigned right_n_bits = x & ((1 << n) - 1);
    unsigned w = sizeof(unsigned) << 3;
    
    return x >> n | right_n_bits << w - n;
}

int main()
{
    unsigned x = 0x12345678;

    printf("n=4: %x\nn=20: %x\nn=0: %x\n", rotate_right(x, 4), rotate_right(x, 20), rotate_right(x, 0));

    return 0;
}

