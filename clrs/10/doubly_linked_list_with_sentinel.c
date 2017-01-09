#include <stdlib.h>

typedef struct node_t {
    int key;
    struct node_t *prev;
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

    list->nil = malloc(sizeof(node_t));
    if (list->nil == NULL) {
        free(list);
        return NULL;
    }

    list->nil->prev = list->nil->next =  list->nil;
    list->nil->key = 0;

    return list;
}

node_t *
list_search(list_t *l, int key)
{
    node_t *node;

    node = l->nil->next;
    while (node != l->nil && node->key != key)
        node = node->next;

    return node;
}

node_t *
list_search2(list_t *l, int key)
{
    node_t *node;

    /* 到最后要终止 */
    l->nil->key = key;
    node = l->nil->next;

    while (node->key != key)
        node = node->next;

    return node;
}

void
list_insert(list_t *l, node_t *x)
{
    x->next = l->nil->next;
    l->nil->next->prev = x;
    l->nil->next = x;
    x->prev = l->nil;
}

void
list_delete(list_t *l, node_t *x)
{
    x->prev->next = x->next;
    x->next->prev = x->prev;
}
