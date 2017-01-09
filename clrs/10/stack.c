#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *buf;
    int top;
    int length;
} stack_t;

stack_t *
make_stack(int length)
{
    stack_t *stack;
    stack = malloc(sizeof(stack_t));
    if (stack == NULL)
        return NULL;

    stack->buf = malloc(sizeof(int) * length);
    if (stack->buf == NULL) {
        free(stack);
        return NULL;
    }

    stack->top = -1;
    stack->length = length;
    return stack;
}

void
free_stack(stack_t *s)
{
    free(s->buf);
    free(s);
}

int
stack_empty(stack_t *s)
{
    return (s->top == -1);
}

int
stack_full(stack_t *s)
{
    return (s->top == s->length - 1);
}

void
push(stack_t *s, int x)
{
    if (stack_full(s)) {
        fprintf(stderr, "stack overflow\n");
        return;
    }

    s->buf[++s->top] = x;
}

int
pop(stack_t *s)
{
    if (stack_empty(s)) {
        fprintf(stderr, "stack underflow\n");
        return -1;
    }
    
    return s->buf[s->top--];
}

/* 栈实现队列 
 * 每次入栈出栈顺序相反，两次就相同
 */
typedef struct {
    stack_t *en;
    stack_t *de;
} queue_t;

queue_t *
make_queue(int length)
{
    queue_t *queue;
    queue = malloc(sizeof(queue_t));
    if (queue == NULL)
        return NULL;

    queue->en = make_stack(length);
    if (queue->en == NULL) {
        free(queue);
        return NULL;
    }

    queue->de = make_stack(length);
    if (queue->de == NULL) {
        free_stack(queue->en);
        free(queue);
        return NULL;
    }

    return queue;
}

void
free_queue(queue_t *q)
{
    free_stack(q->en);
    free_stack(q->de);
    free(q);
}

void
enqueue(queue_t *q, int x)
{
    push(q->en, x);
}

int
dequeue(queue_t *q)
{
    if (stack_empty(q->de))
        while (!stack_empty(q->en))
            push(q->de, pop(q->en));

    /* 都为空也正确 */
    return pop(q->de);
}



