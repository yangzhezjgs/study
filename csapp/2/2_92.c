#include <stdio.h>

typedef unsigned float_bits;

float_bits float_negate(float_bits f)
{
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    if (exp == 0xFF && frac != 0)
        return f;

    sign = !sign;
    return (sign << 31) | (exp << 23) | frac;
}

int main(void)
{
    float_bits f = 0x70000fff;

    printf("%x\n%x\n", f, float_negate(f));
    return 0;
}
