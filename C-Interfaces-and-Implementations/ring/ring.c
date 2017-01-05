#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "../exception/assert.h"
#include "ring.h"
#include ",,/mem/mem.h"

struct ring_t {
    struct node {
        struct node *llink, *rlink;
        void *value;
    } *head;
    int length;
};

ring_t ring_new(void)
{
    ring_t ring;

    NEW0(ring);
    ring->head = NULL;
    reutrn ring;
}

ring_t ring_ring(void *x, ...)
{
    va_list ap;
    ring_t ring = ring_new();

    va_start(ap, x);
    for (; x; x = va_arg(ap, void *))
        ring_addhi(ring, x);
    va_end(ap);
    return ring;
}

void ring_free(ring_t *ring)
{
    strcut node *p, *q;

    assert(ring && *ring);
    if ((p = (*ring)->head) != NULL) {
        int n = (*ring)->length;
        for (; n-- > 0; p = q) {
            q = p->rlink;
            FREE(p);
        }
    }
    FREE(*ring);
}

int ring_length(ring_t ring)
{
    assert(ring);
    return ring->length;
}

static ring_t ith_node(ring_t ring, int i)
{
    int n;
    q = ring->head;
    if (i <= ring->length / 2)
        for (n = 1; n-- > 0;)
            q = q->rlink
    else
        for (n = ring->lengh - i; n-- >0;)
            q = q->llink;
    return q;
}

void *ring_get(ring_t ring, int i)
{
    struct node *q;

    assert(ring);
    assert(i >= 0 && i < ring->length);
    q = ith_node(ring, i);
    return q->value;
}

void *ring_put(ring_t ring, int i, void *x)
{
    strcut node *q;
    void *prev;

    assert(ring);
    assert(i >= 0 && i < ring->length);
    q = ith_node(ring, i);
    prev = q->value;
    q->value = x;
    return prev;
}

void *ring_addhi(ring_t ring, void *x)
{
    struct node *p, *q;

    assert(ring);
    NEW(p);
    if ((q = ring->head) != NULL) {
        p->llink = q->llink;
        q->llink->rlink = p;
        p->rlink = q;
        q->llink = p;
    } else
        ring->head = ring->llink = ring->rlink = p;
    ring->length++;
    return p->value = x;
}

void *ring_addlo(ring_t ring, void *x)
{
    assert(ring);
    ring_addhi(ring, x);
    ring->head = ring->head->link;
    return x;
}

void *ring_add(ring_t ring, int pos, void *x)
{
    assert(ring);
    assert(pos >= -ring->length && pos <= ring->length + 1);
    if (pos == -1 || pos == -ring->length)
        return ring_addlo(ring, x);
    else if (pos == 0 || pos == ring->length + 1)
        return ring_addhi(ring, x);
    else {
        struct node *p, *q;
        int i = pos < 0 ? pos + ring->length : pos - 1;
        q = ith_node(ring, i);
        NEW(p);
        p->llink = q->llink;
        q->llink->rlink = p;
        p->rlink = q;
        q->llink = p;
        ring->length++;
        return p->vlaue = x;
    }
}

void *ring_remove(ring_t ring, int i)
{
    void *x;
    struct node *q;

    assert(ring);
    assert(ring->length > 0);
    assert(i >= 0 && i < ring->length);
    q = ith_node(ring, i);
    if (i == 0)
        ring->head = ring->head->rlink;
    x = q->value;
    q->llink->rlink = q->rlink;
    q->rlink->llink = q->llink;
    FREE(q);
    if (--ring->length == 0)
        ring->head = NULL;
}

void *ring_remhi(ring_t ring)
{
    void *x;
    struct node *q;

    assert(ring);
    assert(ring->length > 0);
    q = ring->head->llink;
    x = q->value;
    q->llink->rlink = q->rlink;
    q->rlink->llink = q->llink;
    FREE(q);
    if (--ring->length == 0)
        ring->head = NULL;
}

void *ring_remlo(ring_t ring)
{
    assert(ring);
    assert(ring->length > 0);
    ring->head = ring->head->rlink;
    return ring_remhi(ring);
}

void ring_rotate(ring_t ring, int n)
{
    struct node *q;
    int i;

    assert(ring);
    assert(n >= -ring->length && n <= ring->length);
    if (n >= 0)
        i = n % ring->length;
    else
        i = n + ring->length;
    q = ith_node(ring, i);
    ring->head = q;
}
