
double poly(double a[], double x, int degree)
{
    long int i;
    double result = 0;
    double val1, val2, xpwr = 1;
    double xpwr2 = x * x;
    double xpwr4 = xpwr2 * xpwr2;

    for (i = 0; i <= degree - 3; i += 4) {
        val1 = a[i] + a[i+1] * x;
        val2 = a[i+2] + a[i+3] * x;
        result = result + (val1 + val2 * xpwr2) * xpwr;
        xpwr *= xpwr4;
    }
    for (; i <= degree; i++) {
        result += a[i] * xpwr;
        xpwr *= x;
    }
    return result;
}
