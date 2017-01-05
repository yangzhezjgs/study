#include <stdio.h>

unsigned replace_byte(unsigned x, unsigned char b, int i)
{
    return (b << (i << 3)) | (x & (~(0xff << (i << 3))));
}

int main(void)
{
    unsigned x = replace_byte(0x12345678, 0xAB, 2);
    unsigned y = replace_byte(0x12345678, 0xAB, 0);

    printf("%x\n", x);
    printf("%x\n", y);

    return 0;
}
