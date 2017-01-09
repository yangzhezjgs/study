#include <stdlib.h>

/* np = prev ^ next
 * a ^ a = 0, b ^ 0 = b
 * next = np ^ prev
 */
#define XOR(a, b) ((node_t *) ((unsigned long) (a) ^ (unsigned long) (b)))

typedef struct node_t {
    int key;
    struct node_t *np;
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
}

void
list_insert(list_t *l, node_t *x)
{
    x->np = XOR(NULL, l->head);
    if (l->head != NULL)
        l->head->np = XOR(l->head->np, x);
    l->head = x;

    if (l->tail == NULL)
        l->tail = l->head;
}

node_t *
list_search(list_t *l, int key)
{
    node_t *prev, *current, *next;

    prev = NULL;
    current = l->head;
    while (current != NULL && current->key != key) {
        next = XOR(prev, current->np);
        prev = current;
        current = next;
    }

    return current;
}

/* 只能按顺序搜索键值 θ(n) */
void
list_delete(list_t *l, int key)
{
    node_t *prev, *current, *next;

    prev = NULL;
    current = l->head;
    while (current != NULL && current->key != key) {
        next = XOR(prev, current->np);
        prev = current;
        current = next;
    }

    if (prev != NULL)
        prev->np = XOR(XOR(prev->np, current), next);
    else
        l->head = next;

    if (next != NULL)
        next->np = XOR(XOR(next->np, current), prev);
    else
        l->tail = prev;
}
