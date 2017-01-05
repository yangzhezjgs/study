#include <stdio.h>

typedef unsigned float_bits;

float_bits float_half(float_bits f)
{
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xff;
    unsigned frac = f & 0x7fffff;

    switch (exp) {
        case 0:
            frac >>= 1;
            break;
        case 1:
            exp = 0;
            frac = (frac >> 1) | 0x400000;
            break;
        case 0xff:
            break;
        default:
            exp -= 1;
            break;
    }

    return (sign << 31) | (exp << 23) | frac;
}


          
