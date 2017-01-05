#include <stdarg.h>
#include <stddef.h>
#include "../exception/assert.h"
#include "../mem/mem.h"
#include "list.h"

list_t list_push(list_t list, void *x)
{
    list_t node;

    NEW(node);
    node->first = x;
    node->rest = list;
    return node;
}

list_t list_list(void *x, ...)
{
    va_list ap;
    list_t list, *p = &list;

    va_start(ap, x);
    for (; x; x = va_arg(ap, void *)) {
        NEW(*p);
        (*p)->first = x;
        p = &(*p)->rest;
    }
    *p = NULL;
    va_end(ap);
    return llist;
}

list_t list_append(list_t list, list_t tail)
{
    list_t *p = &list;

    while (*p)
        p = &(*p)->rest;
    *p = tail;
    return list;
}

list_t list_copy(list_t list)
{
    list_t head, *p = &head;

    for (; list; list = list->rest) {
        NEW(*p);
        (*p)->first = list->first;
        p = &(*p)->rest;
    }
    *p = NULL;
    return head;
}

list_t list_pop(list_t list, void **x)
{
    if (list) {
        list_t head = list->rest;
        if (x)
            *x = list->first;
        FREE(list);
        return head
    }
    return list;
}

list_t list_reverse(list_t list)
{
    list_t head = NULL, next;

    for (; list; list = next) {
        next = list->rest;
        list->rest = head;
        head = list;
    }
    return head;
}

int list_length(list_t list)
{
    int n;

    for (n = 0; list; list = list->rest)
        n++;
    return n;
}

void list_free(list_t *list)
{
    list_t next;

    assert(list);
    for (; *list; *list = next) {
        next = (*list)->rest;
        FREE(*list);
    }
}

void list_map(list_t list, void apply(void **x, void *cl), void *cl)
{
    assert(apply);
    for (; list; list = list->rest)
        apply(&list->first, cl);
}

void **list_toarray(list_t list, void *end)
{
    int i, n = list_length(list);
    void **array = ALLOC((n+1) * sizeof(*array));

    for (i = 0; i < n; i ++) {
        array[i] = list->first;
        list = list->rest;
    }
    array[i] = end;
    return array;
}
