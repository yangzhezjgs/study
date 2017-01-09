#include <stdlib.h>

typedef struct node_t {
    int key;
    struct node_t *prev;
    struct node_t *next;
} node_t;

typedef struct list_t {
    node_t *head;
    node_t *tail;
} list_t;

list_t *
make_list(void)
{
    list_t *list;

    list = malloc(sizeof(list_t));
    if (list == NULL)
        return NULL;

    list->head = list->tail = NULL;
    return list;
}
    
node_t *
list_search(list_t *l, int key)
{
    node_t *node;

    node = l->head;
    while (node != NULL && node->key != key)
        node = node->next;

    return node;
}

void
list_insert(list_t *l, node_t *x)
{
    x->next = l->head;
    if (l->head != NULL)
        l->head->prev = x;
    l->head = x;

    if (l->tail == NULL)
        l->tail = l->head;
}

void
list_delete(list_t *l, node_t *x)
{
    if (x->prev != NULL)
        x->prev->next = x->next;
    else
        l->head = x->next;

    if (x->next != NULL)
        x->next->prev = x->prev;
    else
        l->tail = x->prev;
}
