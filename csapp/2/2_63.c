#include <stdio.h>

int sra(int x, int k)
{
    int xsrl = (unsigned) x >> k;
    int w = sizeof(int) << 3;
    int sign = x & (1 << (w - 1));

    int mask = (1 << k -1) << (w - k);
    sign && (xsrl |= mask);
    return xsrl;
}

unsigned srl(unsigned x, int k)
{
    unsigned xsra = (int) x >> k;
    int w = sizeof(int) << 3;

    int mask = ~((1 << k - 1) << (w - k));
    return mask & xsra;
}

int main(void)
{
    int x = 0xffff;
    unsigned y = x;

    int sra_x = sra(x, 1);
    unsigned srl_y = srl(y, 1);

    printf("x: %x\tsra_x: %x\n", x, sra_x);
    printf("y: %x\tsrl_y: %x\n", y, srl_y);

    return 0;
}

