#include <stdlib.h>

typedef struct node_t {
    int key;
    struct node_t *next;
} node_t;

typedef struct list_t {
    node_t *nil;
} list_t;

list_t *
make_list(void)
{
    list_t *list;

    list = malloc(sizeof(list_t));
    if (list == NULL)
        return NULL;

    list->nil->next = list->nil;
    return list;

}

/* θ(n) */
node_t *
list_search(list_t *l, int key)
{
    node_t *node;

    node = l->nil->next;
    while (node != l->nil && node->key != key)
        node = node->next;

    return node;
}

/* θ(1) */
void
list_insert(list_t *l, node_t *x)
{
    x->next = l->nil->next;
    l->nil->next = x;
}

/* θ(n) */
void
list_delete(list_t *l, node_t *x)
{
    node_t *prev, *node;

    prev = l->nil;
    node = l->nil->next;
    while (node != l->nil && node != x) {
        prev = node;
        node = node->next;
    }

    prev->next = node->next;
}
