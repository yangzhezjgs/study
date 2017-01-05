#include <stdio.h>
#include <limits.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len)
{
    int i;
    for (i = 0; i < len; i++)
        printf(" %.2x", start[i]);
    printf("\n");
}

void show_long_long(long long x)
{
    show_bytes((byte_pointer) &x, sizeof(long long));
}

void show_int(int x)
{
    show_bytes((byte_pointer) &x, sizeof(int));
}


int signed_high_prod(int x, int y)
{
    int w = sizeof(int) << 3;
    long long prod = (long long) x * y;
    return prod >> w;
}

unsigned unsigned_high_prod(unsigned x, unsigned y)
{
    unsigned x_mhb = !!(x & INT_MIN);
    unsigned y_mhb = !!(y & INT_MIN);

    return (unsigned) signed_high_prod(x, y) + x_mhb * y + y_mhb * x;
}

int main(void)
{
    int x = 0xf8147590;
    int y = 0x9a8471bc;
    long long prod = (long long) x * y;

    show_long_long(prod);
    show_int(signed_high_prod(x, y));
    show_int(x * y);

    show_long_long((unsigned long long) (unsigned) x * (unsigned) y);
    show_int(unsigned_high_prod((unsigned) x,(unsigned) y));
    show_int((unsigned) x * (unsigned) y);

    return 0;
}



