#ifndef SET_H__
#define SET_H__

typedef struct set_t *set_t;

extern set_t set_new(int hint,
    int (*cmp)(const void *x, const void *y),
    unsigned hash(const void *x));
extern void set_free(set_t *set);
extern int set_length(set_t set);
extern int set_member(set_t set, const void *member);
extern void set_put(set_t set, const void *member);
extern void *set_remove(set_t set, const void *member);
extern void set_map(set_t set,
    void (*apply)(const void *member, void *cl), void *cl);
extern void **set_toarray(set_t set, void *end);
extern set_t set_union(set_t s, set_t t);
extern set_t set_inter(set_t s, set_t t);
extern set_t set_minus(set_t s, set_t t);
extern set_t set_diff(set_t s, set_t t);

#endif

