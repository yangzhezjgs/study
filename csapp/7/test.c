#include <stdio.h>
#include <tgmath.h>

enum status { MISS, HIT };

int foo()
{
    return MISS;
}
int main()
{
    int state;
    state = foo();
    if (state == MISS)
        printf("OK\n");
    return 0;
}
