#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *buf;
    int head;
    int tail;
    int length;
} queue_t;

queue_t *
make_queue(int length)
{
    queue_t *queue;
    queue = malloc(sizeof(queue_t));
    if (queue == NULL)
        return NULL;

    queue->buf = malloc(sizeof(int) * length);
    if (queue->buf == NULL) {
        free(queue);
        return NULL;
    }

    queue->head = queue->tail = 0;
    queue->length = length;

    return queue;
}

int
queue_empty(queue_t *q)
{
    return (q->head == q->tail);
}

int
queue_full(queue_t *q)
{
    return (q->head == (q->tail + 1) / q->length);
}

void
enqueue_head(queue_t *q, int x)
{
    if (queue_full(q)) {
        fprintf(stderr, "queue overflow\n");
        return;
    }

    q->head = (--q->head < 0) ? (q->length - 1) : q->head;
    q->buf[q->head] = x;
}

void
enqueue_tail(queue_t *q, int x)
{
    if (queue_full(q)) {
        fprintf(stderr, "queue overflow\n");
        return;
    }

    q->buf[q->tail] = x;
    q->tail = (q->tail + 1) % q->length;
}

int
dequeue_head(queue_t *q)
{
    int x;

    if (queue_empty(q)) {
        fprintf(stderr, "queue underflow\n");
        return;
    }
    
    x = q->buf[q->head];
    q->head = (q->head + 1) % q->length;

    return x;
}
    
int
dequeue_tail(queue_t *q)
{
    if (queue_empty(q)) {
        fprintf(stderr, "queue underflow\n");
        return;
    }

    q->tail = (--q->tail < 0) ? q->length - 1 : q->tail;
    return q->buf[q->tail];
}

/* 队列实现栈 */
typedef struct {
    queue_t *q1;
    queue_t *q2;
    queue_t *en;
} stack_t;

stack_t *
make_stack(int length)
{
    stack_t *stack;
    stack = malloc(sizeof(stack_t));
    if (stack == NULL)
        return NULL;

    stack->q1 = make_queue(length);
    if (stack->q1 == NULL) {
        free(stack);
        return NULL;
    }

    stack->q2 = make_queue(length);
    if (stack->q2 == NULL) {
        free_queue(stack->q1);
        free(stack);
        return NULL;
    }

    stack->en = stack->q1;
    return stack;
}

void
push(stack_t *s, int x)
{
    enqueue_tail(s->en, x);
}

int
pop(stack_t *s)
{
    queue_t *another;

    if (queue_empty(s->en)) {
        fprintf(stderr, "stack underflow\n");
        return -1;
    }

    another = (s->en == s->q1) ? s->q2 : s->q1;
    /* 不包括最后一个元素 */
    s->en->tail = (--s->en->tail < 0) ? s->en->length - 1 : s->en->tail;
    while (!queue_empty(s->en))
        enqueue_tail(another, dequeue_head(s->en));

    /* 返回最后一个元素 */
    s->en->tail = (s->en->tail + 1) % s->en->length;
    return dequeue_head(s->en);
}
