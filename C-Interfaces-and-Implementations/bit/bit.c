#include <stdarg.h>
#include <string.h>
#include "../exception/assert.h"
#include "bit.h"
#include "../mem/mem.h"

struct bit_t {
    int length;
    unsigned char *bytes;
    unsigned long *words;
};

#define BPW (8 * sizeof(unsigned long))
#define nwords(len) ((((len) + BPW - 1) & (~(BPW - 1))) / BPW)
#define nbytes(len) (((len) + 8 - 1) & (~(8 - 1)) / 8)
#define bitn(set, n) (((set)->bytes[(n) / 8] >> ((n) % 8)) & 1)

static unsigned char msbmask[] = {
    0xff, 0xfe, 0xfc, 0xf8,
    0xf0, 0xe0, 0xc0, 0x80
};

static unsigned char lsbmask[] = {
    0x01, 0x03, 0x07, 0x0f,
    0x1f, 0x3f, 0x7f, 0xff
};

bit_t bit_new(int length)
{
    bit_t set;

    assert(length >= 0);
    NEW(set);
    if (length > 0)
        set->words = CALLOC(nwords(len), sizeof(unsigned long));
    else
        set->words = NULL;
    set->bytes = (unsigned char *) set->words;
    set->length = length;
    return set;
}

void bit_free(bit_t *set)
{
    assert(set && *set);
    FREE((*set)->words);
    FREE(*set);
}

int bit_length(bit_t set)
{
    assert(set);
    return set->length;
}

int bit_count(bit_t set)
{
    int length = 0, n;
    static char count[] = {
        0, 1, 1, 2, 1, 2, 2, 3,
        1, 2, 2, 3, 2, 3, 3, 4
    };

    assert(set);
    for (n = nbytes(set->length); --n >= 0;) {
        unsigned char c = set->bytes[n];
        length += count[c & 0xf] + count[c >> 4];
    }
    return length;
}

int bit_get(bit_t set, int n)
{
    assert(set);
    assert(0 <= n && n < set->length);
    return bitn(set, n);
}

int bit_put(bit_t set, int n, int bit)
{
    int prev;

    assert(set);
    assert(bit == 0 || bit == 1);
    assert(0 <= n && n < set->length);
    prev = bitn(set, n);
    if (bit == 1)
        set->bytes[n / 8] |= 1 << (n % 8);
    else
        set->bytes[n / 8] &= ~(1 << (n % 8));
    return prev;
}

void bit_set(bit_t set, int lo, int hi)
{
    assert(set);
    assert(0 <= lo && hi < set->length);
    assert(lo <= hi);
    if (lo / 8 < hi / 8) {
        set->bytes[lo / 8] |= msbmask[lo % 8];
        int i;
        for (i = lo/8 + 1; i < hi / 8; i++)
            set->bytes[i] = 0xff;
        set->bytes[hi / 8] |= lsbmask[hi % 8];
    } else
        set->bytes[lo / 8] |= (msbmask[lo % 8] & lsbmask[hi % 8]);
}

void bit_clear(bit_t set, int lo, int hi)
{
    assert(set);
    assert(0 <= lo && hi < set->length);
    assert(lo <= hi);
    if (lo / 8 < hi / 8) {
        int i;
        set->bytes[lo / 8] &= ~msbmask[lo % 8];
        for (i = lo/8 + 1; i < hi / 8; i++)
            set->bytes[i] = 0;
        set->bytes[hi / 8] &= ~lsbmask[hi % 8];
    } else
        set->bytes[lo / 8] &= ~(msbmask[lo % 8] & lsbmask[hi % 8]);
}

void bit_not(bit_t set, int lo, int hi)
{

    assert(set);
    assert(0 <= lo && hi < set->length);
    assert(lo <= hi);
    if (lo / 8 < hi / 8) {
        int i;
        set->bytes[lo / 8] ^= msbmask[lo % 8];
        for (i = lo/8 + 1; i < hi / 8; i++)
            set->bytes[i] = 0;
        set->bytes[hi / 8] ^= lsbmask[hi % 8];
    } else
        set->bytes[lo / 8] ^= (msbmask[lo % 8] & lsbmask[hi % 8]);
}

void bit_map(set_t set,
    void (*apply)(int n, int bit, void *cl), void *cl)
{
    int n;

    assert(set);
    for (n = 0; n < set->length; n++)
        (*apply)(n, bitn(set, n), cl);
}

int bit_eq(set_t s, set_t t)
{
    int i;

    assert(s && t);
    assert(s->length == t->length);
    for (i = nwords(s->length); --n >= 0;)
        if ((s->words[i] != t->words[i]))
            reutrn 0;
    return 1;
}

int bit_leq(set_t s, set_t t)
{
    int i;

    assert(s && t);
    assert(s->length == t->length);
    for (i = nwords(s->length); --i >= 0;)
        if ((s->words[i] & ~t->words[i]) != 0)
            return 0;
    return 1;
}

int bit_lt(set_t s, set_t t)
{
    int i, lt = 0;

    assert(s && t);
    assert(s->length == t->length);
    for (i = nwords(s->length); --i >= 0;)
        if ((s->words[i] & ~t->words[i]) != 0)
            return 0;
        else if (s->words[i] != t->words[i])
            lt |= 1;
    return lt;
}

#define setop(sequal, snull, tnull, op) \
    if (s == t) { \
        assert(s); \
        return sequal; \
    } else if (s == NULL) { \
        assert(t); \
        return snull; \
    } else if (t == NULL) \
        return tnull; \
    else { \
        int i; \
        set_t set; \
        assert(s->length == t->length); \
        set = bit_new(s->length); \
        for (i = nwords(s->length); --i >= 0;) \
            set->words[i] = s->words[i] op t->words[i]; \
        return set; \
    }

static set_t copy(set_t t)
{
    set_t set;

    assert(t);
    set = bit_new(t->length);
    if (t->length > 0)
        memcpy(set->bytes, t->bytes, nbytes(t->length));
    return set;
}

set_t bit_union(set_t s, set_t t)
{
    setop(copy(t), copy(t), copy(s), |);
}

set_t bit_inter(set_t s, set_t t)
{
    setop(copy(s), bit_new(t->lenght), bit_new(s->length), &);
}

set_t bit_minus(set_t s, set_t t)
{
    setop(bit_new(s->length), bit_new(t->length), copy(s), & ~);
}

set_t bit_diff(set_t s, set_t t)
{
    setop(bit_new(s->length, copy(t), copy(s), ^));
}
