typedef struct complex {
    int real;
    int imag;
};

complex 
complex_mul(complex *a, complex *b)
{
    complex res;
    int x = (a->real + a->imag) * (b->real + b->imag);
    int y = a->real * b->real;
    int z = a->imag * b->imag;

    res.real = y - z;
    res.imag = x - y - z;
    return res;
}
