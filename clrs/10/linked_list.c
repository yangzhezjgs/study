#include <stdlib.h>

typedef struct node_t {
    int key;
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
    l->head = x;
    if (l->tail = NULL)
        l->tail = l->head;
}

/* 书上都假设一定能找到 */
void
list_delete(list_t *l, node_t *x)
{
    node_t *prev, *current;

    prev = NULL;
    current = l->head;
    while (current != NULL && current != x) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL)
        l->head = x->next;
    else
        prev->next = x->next;

    if (x->next == NULL)
        l->tail = prev;
}

/* θ(n) */
void
list_reverse(list_t *l, int n)
{
    node_t *prev, *current, *next;

    prev = NULL;
    current = l->head;
    while (current != NULL && n-- > 0) {
        next = current->next;
        current->next = prev;
        current = next;
        prev = current;
    }
}





