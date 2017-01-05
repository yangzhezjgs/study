#include <stdio.h>

int lower_bits(int n)
{
    return (2 << n - 1) - 1;
}

int main(void)
{
    printf("6: %x\n17: %x\n32: %x\n", lower_bits(6), lower_bits(17), lower_bits(32));

    return 0;
}
