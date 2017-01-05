#include <stdio.h>

int main(void)
{
    int x = 1;

    int mul_5 = (x << 2) + x;
    int mul_9 = (x << 3) + x;
    int mul_30 = (x << 5) - (x << 1);
    int mul_neg_56 = (x <<3) - (x << 6);

    printf("%d\t%d\t%d\t%d\n", mul_5, mul_9, mul_30, mul_neg_56);

    return 0;
}
