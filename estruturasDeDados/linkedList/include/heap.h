#ifndef STDLIB_H
#include <stdlib.h>
#define STDLIB_H 1
#endif

#define ASC_ORDER -1
#define DESC_ORDER 1

typedef struct heapNode_t heapNode_t;
struct heapNode_t {
    void *value;
    heapNode_t *previous;
    heapNode_t *next;
};

typedef struct heap_t heap_t;
struct heap_t {
    heapNode_t *firstNode;
    heapNode_t *lastNode;
    int lenght;
    int order;
    int (*orderPolicy) (void *value1, void *value2);
};

heap_t *reset(heap_t *heap, int order, int (*orderPolicy) (void *value1, void *value2));
void clear(heap_t *heap);
void push(heap_t *heap, void *value);
void *pop(heap_t *heap);
int intOrderPolicy(void *value1, void *value2);
