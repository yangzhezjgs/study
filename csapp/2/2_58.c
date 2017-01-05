#include <stdio.h>

int is_little_endian(void)
{
    int i = 1;
    return *((char *) &i);
}

int main(void)
{
    int x = is_little_endian();

    if (x)
        printf("little endian\n");
    else
        printf("big endian\n");

    return 0;
}

