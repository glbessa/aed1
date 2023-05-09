#ifndef HEAP_H
#include <stdlib.h>

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

heap_t *reset(heap_t *heap, int order, int (*orderPolicy) (void *value1, void *value2)) {
    if (order != ASC_ORDER && order != DESC_ORDER)
        return NULL;
    if (orderPolicy == NULL)
        return NULL;

    if (heap != NULL) {
        clear(heap);
        free(heap);
    }

    heap_t *newHeap = (heap_t *) malloc(sizeof(heap_t));
    if (newHeap == NULL)
        return NULL;

    newHeap->firstNode = NULL;
    newHeap->lastNode = NULL;
    newHeap->lenght = 0;
    newHeap->order = order;
    newHeap->orderPolicy = orderPolicy;

    return newHeap;
}

void clear(heap_t *heap) {
    if (heap == NULL)
        return;
    else if (heap->firstNode == NULL)
        return;

    while(heap->firstNode != NULL) {
        void *value = pop(heap);
        if (value != NULL)
            free(value);
    }
}

void push(heap_t *heap, void *value) {
    if (heap == NULL)
        return;

    heapNode_t *newNode = (heapNode_t *) malloc(sizeof(heapNode_t));
    if (newNode == NULL)
        return;

    newNode->value = value;
    newNode->next = NULL;
    newNode->previous = NULL;

    if (heap->firstNode == NULL && heap->lastNode == NULL) {
        heap->firstNode = newNode;
        heap->lastNode = newNode;
        heap->lenght += 1;
        return;
    }

    heapNode_t *nodeCmp = heap->firstNode;
    if (!((*(heap->orderPolicy))(newNode->value, nodeCmp->value) != heap->order)) {
        nodeCmp->previous = newNode;
        newNode->next = nodeCmp;
        heap->firstNode = newNode;
        heap->lenght += 1;
        return;
    }

    while((*(heap->orderPolicy))(newNode->value, nodeCmp->value) != heap->order) {
        if (nodeCmp->next == NULL) {
            heap->lastNode = newNode;
            break;
        }
        nodeCmp = nodeCmp->next;
    }

    nodeCmp->next = newNode;
    newNode->previous = nodeCmp;
    heap->lenght += 1;
}

void *pop(heap_t *heap) {
    if (heap == NULL)
        return NULL;
    if (heap->firstNode == NULL)
        return NULL;

    heapNode_t *firstNode = heap->firstNode;
    if (firstNode->next != NULL)
        firstNode->next->previous = NULL;
    heap->firstNode = firstNode->next;
    heap->lenght -= 1;

    void *value = firstNode->value;
    free(firstNode);

    return value;
}

/*
IMPLEMENT THIS TEMPLATE FUNCTION IF YOU WANT A DIFFERENT ORDER
RETURN 0 IF THEY ARE AT THE SAME POSITION
RETURN -1 IF value1 IS BEFORE value2
RETURN 1 IF value1 IS AFTER value2
*/
int intOrderPolicy(void *value1, void *value2) {
    int *v1 = (int *) value1;
    int *v2 = (int *) value2;

    if (*v1 < *v2)
        return -1;
    else if (*v1 > *v2)
        return 1;
    
    return 0;
}

#endif
