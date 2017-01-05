typedef unsigned float_bits;

float_bits float_twice(float_bits f)
{
    unsigned sign = f >> 31;
    unsigned exp = f >> 23;
    unsigned frac = f & 0x7fffff;

    switch (exp) {
    case 0:
        frac << = 1;
        if (frac & 0x800000)
            exp = 1;
        frac &= 0x7fffff;
        break;
    case 0xfe:
        exp = 0xff;
        frac =0;
        break;
    case 0xff:
        break;
    default:
        exp += 1;
        break;
    }

    return (sign << 31) | (exp << 23) | frac;
}


