#ifndef STDLIB_H
#include <stdlib.h>
#define STDLIB_H 1
#endif

typedef struct stackNode_t stackNode_t;
struct stackNode_t {
    void *value;
    stackNode_t *next;
};

typedef struct stack_t stack_t;
struct stack_t {
    stackNode_t *top;
    stackNode_t *bottom;
    int lenght;
};

stack_t *reset(stack_t *stack);
void clear(stack_t *stack);
void push(stack_t *stack, void *value);
void *pop(stack_t *stack);
