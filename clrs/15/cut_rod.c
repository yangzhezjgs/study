#include <stdint.h>
#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int
cut_rod(int p[], int length)
{
    int i, max_price;

    if (length == 0)
        return 0;

    max_price = INT32_MIN;
    for (i = 1; i <= length; i++)
        max_price = MAX(p[i], cut_rod(p, length - i));

    return max_price;
}

int
memoized_cut_rod_aux(int p[], int length, int result[])
{
    int i;
    int price;

    if (result[length] >= 0)
        return result[length];

    if (length == 0)
        price = 0;
    else {
        price = INT32_MIN;
        for (i = 1; i <= length; i++)
            price = MAX(price, p[i] + memoized_cut_rod_aux(p, length - i, result));
    }
    
    result[length] = price;
    return price;
}

int
memoized_cut_rod(int p[], int length)
{
    int i;
    int result[length + 1];

    for (i = 0; i <= length; i++)
        result[i] = INT32_MIN;

    return memoized_cut_rod_aux(p, length, result);
}

int
bottom_up_cut_rod(int p[], int length)
{
    int i, j, price;
    int result[length + 1];
    
    result[0] = 0;
    for (i = 1; i <= length; i++) {
        price = INT32_MIN;
        for (j = 1; j <= i; j++)
            price = MAX(price, p[j] + result[i - j]);
        result[j] = price;
    }

    return result[length];
}

int
extended_bottom_up_cut_rod(int p[], int length, int s[])
{
    int i, j, price;
    int r[length + 1];

    r[0] = 0;
    for (i = 1; i <= length; i++) {
        price = INT32_MIN;
        for (j = 1; j <= i; j++)
            if (price < p[j] + r[i - j]) {
                price = p[j] + r[i - j];
                s[i] = j;
            }
        r[i] = price;
    }

    return r[length];
}

int
print_cut_rod_solution(int p[], int length)
{
    int price, s[length + 1];

    price = extended_bottom_up_cut_rod(p, length, s);
    while (length > 0) {
        printf("%d ", s[length]);
        length -= s[length];
    }
    
    return price;
}

int
main(void)
{
    int p[] = { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
    int price;

    price = print_cut_rod_solution(p, 4);
    printf("\nprice: %d\n", price);

    return 0;
}



