#include <stdio.h>
#include <limits.h>

int saturating_add(int x, int y)
{
    int sum = x + y;
    int neg_over = (x & INT_MIN) && (y & INT_MIN) && !(sum & INT_MIN);
    int pos_over = !((x & INT_MIN) || (y & INT_MIN) || !(sum & INT_MIN));

    (neg_over && (sum = INT_MIN)) || (pos_over && (sum = INT_MAX));

    return sum;
}

void test_add(int x,int y)
{
    printf("saturating_add(%d, %d) = %d\n", x, y, saturating_add(x, y));
}



int main(void)
{
    test_add(1, 2);
    test_add(INT_MAX, 1);
    test_add(-1, -2);
    test_add(INT_MIN, -1);

    return 0;
}










