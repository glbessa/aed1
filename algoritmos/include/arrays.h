#ifndef ARRAYS_H
#define ARRAYS_H

#include <stdlib.h>
#include <stdio.h>

typedef enum {
    CHAR,
    INT8,
    INT16,
    INT32,
    INT64,
    FLOAT32,
    FLOAT64,
    VOID,
    VOID_PTR
} TYPE;

typedef struct ndarray ndarray;
struct ndarray {
    void *array;
    int *shape;
    int shapeLength;
    TYPE type;
};

ndarray *CreateNdarray(int *shape, int shapeLength, TYPE type) {
    ndarray *newArray = (ndarray *) malloc(sizeof(ndarray));
    if (!newArray) {
        perror("Error while allocating memory to new array");
        exit(-1);
    }

    size_t arraySize = 1;
    for (int i = 0; i < shapeLength; i++) {
        arraySize *= shape[i];
    }

    switch (type) {
        case CHAR:
        case INT8:
        case VOID_PTR:
            arraySize *= 1;
            break;
        case INT16:
            arraySize *= 2;
            break;
        case INT32:
        case FLOAT32:
            arraySize *= 4;
            break;
        case INT64:
        case FLOAT64:
            arraySize *= 8;
            break;
    }

    newArray->array = (void *) malloc(arraySize);
    if (!newArray->array) {
        perror("Error while allocating memory to new array");
        exit(-1);
    }

    newArray->shape = shape;
    newArray->shapeLength = shapeLength;
    newArray->type = type;

    return newArray;
}

#endif