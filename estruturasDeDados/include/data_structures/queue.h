#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

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

queue_t *reset(queue_t *queue) {
    if (queue != NULL) {
        clear(queue);
        free(queue);
    }

    queue_t *newQueue = (queue_t *) malloc(sizeof(queue_t));
    newQueue->firstNode = NULL;
    newQueue->lastNode = NULL;
    newQueue->lenght = 0;

    return newQueue;
}

void clear(queue_t *queue) {
    if (queue == NULL)
        return;
    else if (queue->firstNode == NULL)
        return;

    while(queue->firstNode != NULL) {
        void *value = pop(queue);
        if (value != NULL)
            free(value);
    }
}

void *pop(queue_t *queue) {
    if (queue == NULL)
        return NULL;
    else if (queue->firstNode == NULL)
        return NULL;

    queueNode_t *firstNode = queue->firstNode;
    void *value = queue->firstNode->value;

    queue->firstNode = firstNode->next;
    queue->lenght -= 1;
    free(firstNode);

    return value;
}

void push(queue_t *queue, void *value) {
    if (queue == NULL)
        return;
    
    queueNode_t *node = (queueNode_t *) malloc(sizeof(queueNode_t));
    node->value = value;

    if (queue->firstNode == NULL) {
        queue->firstNode = node;
        queue->lastNode = node;
        queue->lenght += 1;
        return;
    }

    queue->lastNode->next = node;
    queue->lastNode = node;
    queue->lenght += 1;
}

#endif