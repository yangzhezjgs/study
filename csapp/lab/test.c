#include <stdlib.h>
#include <stdio.h>

int main()
{
    int *b;
    *b = 2;
    unsigned int a = (long) b;
    int *c;
    c = (unsigned int*)(long) b;
    if (c == b)
        printf("yes\n");
    return 0;
}
