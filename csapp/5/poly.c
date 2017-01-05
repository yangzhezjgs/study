#include <stdio.h>
#include <time.h>

double poly(double a[], double x, int degree)
{
    long int i;
    double result = a[0];
    double xpwr = x;
    for (i = 1; i <= degree; i++) {
        result += xpwr * a[i];
        xpwr *= x;
    }
    return result;
}

double polyh(double a[], double x, int degree)
{
    long int i;
    double result = a[degree];
    for (i = degree - 1; i >= 0; i--) {
        result = a[i] + x * result;
    }
    return result;
}

int main()
{
    double a[] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7, 7.8, 8.9, 9};
    double result, x = 2;
    int degree = 8;
    clock_t start, end;

    start = clock();
    result = poly(a, 2, 8);
    end = clock();
    printf("%f\t%f\n", result, (float) (end - start) / CLOCKS_PER_SEC);

    start = clock();
    result = polyh(a, 2, 8);
    end = clock();
    printf("%f\t%f\n", result, (float) (end - start) / CLOCKS_PER_SEC);

    return 0;
}


