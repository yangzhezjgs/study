#ifndef LIST_H__
#define LIST_H__

typedef struct list_t *list_t;

struct list_t {
    list_t rest;
    void *first;
};

extern list_t list_append(list_t list, list_t tail);
extern list_t list_copy(list_t list);
extern list_t list_list(void *x, ...);
extern list_t list_pop(list_t list, void **x);
extern list_t list_push(list_t list, void *x);
extern list_t list_reverse(list_t list);
extern int list_length(list_t list);
extern void list_free(list_t *list);
extern void list_map(list_t list, void apply(void **x, void *cl), void *cl);
extern void **list_toarray(list_t list, void *end);

#endif
