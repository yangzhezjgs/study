#include <stdio.h>
#include <limits.h>

typedef unsigned float_bits;

float_bits float_i2f(int i)
{
    unsigned sign = 0, exp, frac, tail;
    
    if (i == 0)
        return 0;
    
    if (i < 0) {
        sign = 1;
        i = -i;
    }
        
    frac = (unsigned) i;

    for (exp = 31 + 127; !(frac & INT_MIN); exp--)  
        frac <<= 1;
    tail = frac & 0xff;
    frac >>= 8;

    if ((tail > 0x80) || ((tail == 0x80) && (frac & 1)))
        frac++;
    if (frac == 0x01000000)
        exp++;

    frac &= 0x7fffff;

    return (sign << 31) | (exp << 23) | frac;
}

int main()
{
    int i = 0x123451;
    int min = INT_MIN;
    int max = INT_MAX;

    printf("%d: %x\n", i, float_i2f(i));
    printf("%d: %x\n", min, float_i2f(min));
    printf("%d: %x\n", max, float_i2f(max));

    return 0;
}


