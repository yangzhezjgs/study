#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SWAP(a, b ,t)   \
    do {                \
        t temp = a;     \
        a = b;          \
        b = temp;       \
    } while (0)

#define PARENT(i) ((i - 1) / 2) 
#define LEFT(i) ((i) * 2 + 1)
#define RIGHT(i) ((i) * 2 + 2)

/* θ(lgn) */
void
max_heapify(int buf[], int size, int i)
{
    int largest, left, right;

    largest = i;
    left = LEFT(i);
    right = RIGHT(i);

    if (left <= size - 1 && buf[left] > buf[largest])
        largest = left;
    if (right <= size - 1 && buf[right] > buf[largest])
        largest = right;

    if (largest != i) {
        SWAP(buf[i], buf[largest], int);
        max_heapify(buf, size, largest);
    }
}

/* θ(nlgn) */
void
build_max_heap(int buf[], int size)
{
    int i;

    for (i = size / 2 - 1; i >= 0; i--)
        max_heapify(buf, size, i);
}

#define MAXSIZE 1024

typedef struct {
    int buf[MAXSIZE];
    int size;
} queue;

/* θ(nlgn) */
queue *
buid_max_priority_queue(int buf[], int size)
{
    queue *q;
    if (size > MAXSIZE) {
        fprintf(stderr, "heap overflow\n");
        return NULL;
    }
    
    q = malloc(sizeof(queue));
    memcpy(q, buf, sizeof(int) * size);
    q->size = size;
    build_max_heap(q->buf, q->size);

    return q;
}

/* θ(1) */
int
maximum(queue *q)
{
    return q->buf[0];
}

/* θ(lgn) */
int 
extract_max(queue *q)
{
    int max;

    if (q->size < 0) {
        fprintf(stderr, "heap underflow\n");
        return;
    }

    max = q->buf[0];
    q->size--;
    q->buf[0] = q->buf[q->size];
    max_heapify(q->buf, q->size, 0);

    return max;
}

/* θ(lgn) */
void
increase_key(queue *q, int i, int key)
{
    if (i < 0 || i >= q->size) {
        fprintf(stderr, "heap flow\n");
        return;
    }

    if (key < q->buf[i]) {
        fprintf(stderr, "new key is smaller than current key\n");
        return;
    }

    q->buf[i] = key;
    while (i > 0 && q->buf[PARENT(i)] < q->buf[i]) {
        SWAP(q->buf[PARENT(i)], q->buf[i], int);
        i = PARENT(i);
    }
}

/* θ(lgn) */
void
insert(queue *q, int key)
{
    if (q->size == MAXSIZE) {
        fprintf(stderr, "heap overflow\n");
        return;
    }

    q->buf[q->size] = INT32_MIN;
    q->size++;
    increase_key(q, q->size - 1, key);
}

/* θ(lgn) */
void
delete(queue *q, int i)
{
    if (i < 0 || i >= q->size) {
        fprintf(stderr, "out of range\n");
        return;
    }

    q->size--;
    q->buf[0] = q->buf[q->size];
    max_heapify(q->buf, q->size, 0);
}
