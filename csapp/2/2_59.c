#include <stdio.h>

int combine_x_y(int x, int y)
{
    return (x & 0xff) | (y & (~ 0xff));
}

int main(void)
{
    int x = 0x89ABCDEF;
    int y = 0x76543210;

    int z = combine_x_y(x, y);
    printf("z= %x\n", z);
    
    return 0;
}
