#ifndef STACK_H
#define STACK_H
#include <stdlib.h>

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

stack_t *stack_reset(stack_t *stack);
void stack_clear(stack_t *stack);
void stack_push(stack_t *stack, void *value);
void *pop(stack_t *stack);

#include "stack.h"

stack_t *stack_reset(stack_t *stack) {
    if (stack != NULL) {
        stack_clear(stack);
        free(stack);
    }

    stack_t *newStack = (stack_t *) malloc(sizeof(stack_t));
    if (newStack == NULL)
        return NULL;

    newStack->top = NULL;
    newStack->bottom = NULL;
    newStack->lenght = 0;

    return newStack;
}

void stack_clear(stack_t *stack) {
    if (stack == NULL)
        return;
    else if (stack->top == NULL)
        return;

    while(stack->top != NULL) {
        void *value = pop(stack);
        if (value != NULL)
            free(value);
    }
}

void stack_push(stack_t *stack, void *value) {
    if (stack == NULL)
        return;

    stackNode_t *newNode = (stackNode_t *) malloc(sizeof(stackNode_t));
    if (newNode == NULL)
        return;

    newNode->value = value;
    newNode->next = NULL;

    if (stack->top == NULL) {
        stack->top = newNode;
        stack->bottom = newNode;
        stack->lenght += 1;
        return;
    }

    newNode->next = stack->top;
    stack->top = newNode;
    stack->lenght += 1;
}

void *pop(stack_t *stack) {
    if (stack == NULL)
        return NULL;

    if (stack->top == NULL)
        return NULL;

    stackNode_t *topNode = stack->top;
    stack->top = topNode->next;
    stack->lenght -= 1;

    void *value = topNode->value;
    free(topNode);

    return value;
}

#endif