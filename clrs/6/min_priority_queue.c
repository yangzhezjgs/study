#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SWAP(a, b, t)   \
    do {                \
        t temp = a;     \
        a = b;          \
        b = temp;       \
    } while (0)         \

#define PARENT(i) (((i) - 1) / 2)
#define LEFT(i) ((i) * 2 + 1)
#define RIGHT(i) ((i) * 2 + 2)

#define MAXSIZE 1024
typedef struct queue {
    int buf[MAXSIZE];
    int size;
} queue;

/* θ(n) */
queue *
build_min_priority_queue(int buf[], int size)
{
    queue *q;

    if (size > MAXSIZE) {
        fprintf(stderr, "heap overflow\n");
        return NULL;
    }

    q = malloc(sizeof(queue));
    memcpy(q, buf, sizeof(int) * size);
    q->size = size;
    build_min_heap(q->buf, q->size);

    return q;
}

/* θ(1) */
int
minimum(queue *q)
{
    return q->buf[0];
}

/* θ(lgn) */
int
extract_min(queue *q)
{
    int min;

    if (q->size < 0) {
        fprintf(stderr, "heap underflow\n");
        return;
    }

    min = q->buf[0];
    q->size--;
    q->buf[0] = q->buf[q->size];
    min_heapify(q->buf, q->size, 0);

    return min;
}

/* θ(lgn) */
void
decrease_key(queue *q, int i, int key)
{
    if (i < 0 || i >= q->size) {
        fprintf(stderr, "heap flow\n");
        return;
    }

    if (key > q->buf[i]) {
        fprintf(stderr, "new key is larger than current key\n");
        return;
    }

    while (i > 0 && q->buf[PARENT(i)] > key) {
        q->buf[i] = q->buf[PARENT(i)];
        i = PARENT(i);
    }
    q->buf[i] = key;
}

/* θ(lgn) */
void
insert(queue *q, int key)
{
    if (q->size == MAXSIZE) {
        fprintf(stderr, "heap overflow\n");
        return;
    }

    q->buf[q->size] = INT32_MAX;
    q->size++;
    decrease_key(q, q->size - 1, key);
}
