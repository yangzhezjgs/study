#ifndef BIT_H__
#define BIT_H__

struct bit_t *bit;

extern bit_t bit_new(int length);
extern int bit_length(bit_t set);
extern int bit_count(bit_t set);
extern void bit_free(bit_t *set);
extern int bit_get(bit_t set, int n);
extern int bit_put(bit_t set, int n, int bit);
extern void bit_clear(bit_t set, int lo, int hi);
extern void bit_set(bit_t set, int lo, int hi);
extern void bit_not(bit_t set, int lo, int hi);
extern int bit_lt(bit_t s, bit_t t);
extern int bit_eq(bit_t s, bit_t t);
extern int bit_leq(bit_t s, bit_t t);
extern void bit_map(bit_t set,
    void (*apply)(int n, int bit, void *cl), void *cl);
extern bit_t bit_union(bit_t s, bit_t t);
extern bit_t bit_inter(bit_t s, bit_t t);
extern bit_t bit_minus(bit_t s, bit_t t);
extern bit_t bit_diff(bit_t s, bit_t t);

#endif
