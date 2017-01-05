#include <stdio.h>
#include <limits.h>

typedef unsigned float_bits;

int float_f2i(float_bits f)
{
    unsigned sign = f >> 31;
    unsigned exp = (f >> 23) & 0xff;
    unsigned frac = f & 0x7fffff;
    int result;

    if ((f >= 0xcf000000) || ((f >= 0x4f000000) && !sign))
        return 0x80000000;

    if (exp < 127)
        return 0;

    exp -= 127;
    frac |= 0x800000;

    if (exp < 23)
        result = frac >> (23 - exp);
    else
        result = frac << (exp - 23);

    if (sign)
        result = -result;

    return result;
}

int main()
{
    float_bits x = 0x4640e400;
    float_bits y = 0xcf000000;
    float_bits z = 0x4effffff;

    printf("%d\n", float_f2i(x));
    printf("%d\n", float_f2i(y));
    printf("%d\n", float_f2i(z));

    return 0;
}
        
