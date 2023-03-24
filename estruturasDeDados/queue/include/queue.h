#ifndef STDLIB_H
#include <stdlib.h>
#define STDLIB_H 1
#endif

typedef struct queueNode_t queueNode_t;
struct queueNode_t {
    void *value;
    queueNode_t *next;
};

typedef struct queue_t queue_t;
struct queue_t {
    queueNode_t *firstNode;
    queueNode_t *lastNode;
    unsigned int lenght;
};

queue_t *reset(queue_t *queue);
void clear(queue_t *queue);
void *pop(queue_t *queue);
void push(queue_t *queue, void *value);