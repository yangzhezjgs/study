#ifndef STACK_H__
#define STACK_H__

typedef struct stack_t *stack_t;

extern stack_t stack_new(void);
extern int stack_empty(stack_t stk);
extern void stack_push(stack_t stk, void *x);
extern void *stack_pop(stack_t stk);
extern void stack_free(stack_t stk);

#endif

