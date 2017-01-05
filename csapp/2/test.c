#include <stdio.h>

int test(int x, int y)
{
    return !((y + ~x + 1) >> 31) ;
}
int main(void)
{
    int i = -100;
    unsigned j = i;
    unsigned k = (unsigned) i;
    char s = 'a';

    printf("%d\n", s);


    return 0;
}
