#include <stdio.h>

int bad_int_size_is_32()
{
    int set_msb = 1 << 31;

    int beyond_msb = 2 << 31;

    return set_msb && !beyond_msb;
}

int at_least_16_bits()
{
    int set_msb = 1 << 15 << 15 << 1;
    
    int beyond_msb = 1 << 15 << 15 << 2;

    return set_msb && !beyond_msb;
}

int main(void)
{
    printf("%d\n", at_least_16_bits());
    return 0;
}
