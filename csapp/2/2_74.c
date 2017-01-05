#include <stdio.h>
#include <limits.h>

int tsub_ovf(int x, int y)
{
    int sub = x - y;
    int pos_over = !(x & INT_MIN) && (y & INT_MIN) && (sub & INT_MIN);
    int neg_over = (x & INT_MIN) && !(y & INT_MIN) && !(sub & INT_MIN);

    return pos_over || neg_over;
}

int main(void)
{
    printf("%d\n%d\n%d\n%d\n", tsub_ovf(1, 3), tsub_ovf(INT_MAX, -1), tsub_ovf(-1, -3), tsub_ovf(INT_MIN, 1));
    return 0;
}
