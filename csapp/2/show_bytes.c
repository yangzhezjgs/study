#include <stdio.h>
#include <string.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len)
{
    int i;
    
    for (i = 0; i < len; i++)
        printf(" %.2x", start[i]);
    printf("\n");
}

void show_short(short x)
{
    show_bytes((byte_pointer) &x, sizeof(short));
}

void show_long(long x)
{
    show_bytes((byte_pointer) &x, sizeof(long));
}

void show_double(double x)
{
    show_bytes((byte_pointer) &x, sizeof(double));
}



void show_int(int x)
{
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x)
{
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x)
{
    show_bytes((byte_pointer) &x, sizeof(void *));
}

void test_show_bytes(int val)
{
    int ival = val;
    float fval = (float) ival;
    int *pval = &ival;
    short int sval = ival;
    long int lval = ival;
    double dval = (double) ival;

    show_int(ival);
    show_float(fval);
    show_pointer(pval);
    show_short(sval);
    show_long(lval);
    show_double(dval);
}

int main(void)
{
    short sx = -12345;
    unsigned short usx = sx;
    unsigned uy = sx;
    int x = sx;
    unsigned ux = usx;


    test_show_bytes(12345);
    printf("sx = %d:\t", sx);
    show_bytes((byte_pointer) &sx, sizeof(short));
    printf("usx = %u:\t", usx);
    show_bytes((byte_pointer) &usx, sizeof(unsigned short));
    printf("x = %d:\t", x);
    show_bytes((byte_pointer) &x, sizeof(int));
    printf("ux = %u:\t", ux);
    show_bytes((byte_pointer) &ux, sizeof(unsigned));
    printf("uy = %u:\t", uy);
    show_bytes((byte_pointer) &uy, sizeof(unsigned));

    

    return 0;
}






