#include <string.h>
#include <limits.h>
#include "../exception/assert.h"
#include "../mem/mem.h"
#include "atom.h"

#define NELEMS(x)  ((sizeof(x)) / (sizeof((x)[0])))

static struct atom
{
    struct atom *link;
    int len;
    char str[];
} *buckets[2048];

const char *atom_string(const char *str)
{
    assert(str);
    return atom_new(str, strlen(str));
}

const char *atom_int(long n)
{
    char str[44];
    char *s = str + sizeof(str);
    unsigned long m;

    *--s = '\0';
    if (n == LONG_MIN)
        m = LONG_MAX + 1UL;
    else if (n < 0)
        m = -n;
    else
        m = n;
    do {
        *--s = m % 10 + '0';
    } while ((m /= 10) > 0);
    if (n < 0)
        *--s = '-';
    return atom_new(s, (str + sizeof(str) - s);
}

const char *atom_new(const char *str, int length)
{
    unsigned long h;
    int i;
    struct atom *p;

    assert(str);
    assert(len >= 0);
    /* h = hash(str) */
    h %= NELEMS(buckets);
    for (p = buckets[h]; p; p = p->link) {
        if (len == p->len) {
            for (i = 0; i < len && p->str[i] == str[i];)
                i++;a
            if (i == len)
                return p->str;
        }
    }

    p = ALLOC(sizeof(*p) + len + 1);
    p->len = len;
    if (len > 0)
        memcpy(p->str, str, len);
    p->str[len] = '\0';
    p->link = buckets[h];
    buckets[h] = p;
}

int atom_length(const char *str)
{
    struct atom *p;
    int i;

    assert(str);
    for (i = 0; i < NELEMS(buckets); i++)
        for (p = buckets[i]; p; p = p->link)
            if (p->str == str)
                return p->len;
    assert(0);
    return 0;
}
