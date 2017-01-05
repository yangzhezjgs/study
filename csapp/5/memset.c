
void *basic_memset(void *s, int c, size_t n)
{
    size_t cnt = 0;
    unsigned char *schar = s;
    while (cnt < n) {
        *schar++ = (unsigned char) c;
        cnt ++;
    }
    return s;
}

void memset(void *s, int c, size_t n)
{
    size_t k = sizeof(unsigned long);
    unsigned char *schar = s;
    unsigned long *lchar;
    unsigned long lc;
    int i;
    for (i = 0; i < k; i++) {
        lc += (c & 0xff) << (i << 3);
    }

    while (((unsigned) schar % k) && n) {
        *schar++ = (unsigned char) c;
        n--;
    }

    lchar = (unsigned long *) schar;

    while (n >= k) {
        *lchar = lc;
        n -= k;
    }

    schar = (unsigned char *) lchar;
    while (n) {
        *lchar++ = (unsigned char) c;
        n--;
    }
    return s;
}




