#include <stdio.h>
#include <limits.h>

int divide_power2(int x, int k)
{
    int x_mhb = !!(x & INT_MIN);
    int div;

    (!x_mhb && (div = x >> k)) || (x_mhb && (div = (x + (1 << k) - 1) >> k));

    return div;
}

void test_print(int x, int k)
{
    printf("%d/2^%d = %d\n", x, k, divide_power2(x, k));
}

int main(void)
{
    int x = 12340;
    int nx = -x;

    test_print(x, 1);
    test_print(x, 4);
    test_print(nx, 1);
    test_print(nx, 4);
    printf("%d >> %d = %d\n", nx, 4, nx >> 4);

    return 0;
}

