#line 141 "bits.c"
int bitAnd(int x, int y) {
    return ~((~x) |( ~y));
#line 1 "<command-line>"
#include "/usr/include/stdc-predef.h"
#line 143 "bits.c"
}
#line 152
int getByte(int x, int n) {
#line 160
    return (x >>( n << 3)) & 0xff;

}
#line 171
int logicalShift(int x, int n) {
    int mask;
    mask = ~((1 << 31 >> n) << 1);
    return (x >> n) & mask;
}
#line 183
int bitCount(int x) {
    int mask1;int mask2;int mask3;int mask4;int mask5;

    mask1 = 0x55;
    mask1 |= mask1 << 8;
    mask1 |= mask1 << 16;
    x =( x & mask1) +(( x >> 1) & mask1);

    mask2 = 0x33;
    mask2 |= mask2 << 8;
    mask2 |= mask2 << 16;
    x =( x & mask2) +(( x >> 2) & mask2);

    mask3 = 0x0f;
    mask3 |= mask3 << 8;
    mask3 |= mask3 << 16;
    x =( x & mask3) +(( x >> 4) & mask3);

    mask4 = 0xff;
    mask4 |= mask4 << 16;
    x =( x & mask4) +(( x >> 8) & mask4);

    mask5 = 0xff;
    mask5 |= mask5 << 8;
    x =( x & mask5) +(( x >> 16) & mask5);

    return x;
#line 213
}
#line 221
int bang(int x) {
  return (((~x + 1) | x) >> 31) + 1;
}
#line 230
int tmin(void) {
  return 1 << 31;
}
#line 242
int fitsBits(int x, int n) {
  return !((x <<( ~n + 33) >>( ~n + 33)) ^ x);
}
#line 253
int divpwr2(int x, int n) {
    return (x +((( 1 << n) + ~0) &( x >> 31))) >> n;
}
#line 263
int negate(int x) {
  return ~x + 1;
}
#line 273
int isPositive(int x) {
  return !(x >> 31) ^ !x;
}
#line 283
int isLessOrEqual(int x, int y) {
    int sign_x=(  x >> 31) & 1;
    int sign_y=(  y >> 31) & 1;

    return (sign_x & !sign_y) |( !(sign_x ^ sign_y) & !((y + ~x + 1) >> 31));
}
#line 296
int ilog2(int x) {
    int mask1;int mask2;int mask3;int mask4;int mask5;

    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;

    mask1 = 0x55;
    mask1 |= mask1 << 8;
    mask1 |= mask1 << 16;
    x =( x & mask1) +(( x >> 1) & mask1);

    mask2 = 0x33;
    mask2 |= mask2 << 8;
    mask2 |= mask2 << 16;
    x =( x & mask2) +(( x >> 2) & mask2);

    mask3 = 0x0f;
    mask3 |= mask3 << 8;
    mask3 |= mask3 << 16;
    x =( x & mask3) +(( x >> 4) & mask3);

    mask4 = 0xff;
    mask4 |= mask4 << 16;
    x =( x & mask4) +(( x >> 8) & mask4);

    mask5 = 0xff;
    mask5 |= mask5 << 8;
    x =( x & mask5) +(( x >> 16) & mask5);

    return x + ~0;
}
#line 341
unsigned float_neg(unsigned uf) {
    if (uf << 1 > 0xff000000) 
        return uf;
    return (1 << 31) ^ uf;


}
#line 357
unsigned float_i2f(int x) {
    unsigned sign=  0;unsigned exp;unsigned frac;unsigned tail;
    if (x == 0) 
        return 0;

    if (x < 0) {
        sign = 1;
        x = -x;
    }

    frac = x;

    for (exp = 31 + 127; !(frac & 0x80000000); exp--) 
        frac <<= 1;
    tail = frac & 0xff;
    frac >>= 8;

    if ((tail > 0x80) ||(( tail == 0x80) &&( frac & 1))) 
        frac++;
    if (frac == 0x01000000) 
        exp++;

    frac &= 0x7fffff;

    return (sign << 31) |( exp << 23) |frac;
}
#line 394
unsigned float_twice(unsigned uf) {
    unsigned sign=  uf >> 31;
    unsigned exp=(  uf >> 23) & 0xff;
    unsigned frac=  uf & 0x7fffff;

    switch (exp) {
    case 0: 
        frac <<= 1;
        if (frac & 0x800000) 
            exp = 1;
        frac &= 0x7fffff;
        break;
    case 0xfe: 
        exp = 0xff;
        frac = 0;
        break;
    case 0xff: 
        break;
    default: 
        exp++;
        break;
    }

    return (sign << 31) |( exp << 23) | frac;
}
