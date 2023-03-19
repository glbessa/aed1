#include "stack.h"

stack_t *reset(stack_t *stack) {
    if (stack != NULL) {
        clear(stack);
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

void clear(stack_t *stack) {
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

void push(stack_t *stack, void *value) {
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