#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    heap_t *heap = reset(NULL, DESC_ORDER, &intOrderPolicy);
    if (heap == NULL) {
        printf("Deu ruim!\n");
        exit(-1);
    }
    int *v1 = (int *) malloc(sizeof(int));
    if (v1 == NULL)
        exit(-1);

    *v1 = 1;
    push(heap, v1);

    int *v2 = (int *) malloc(sizeof(int));
    if (v2 == NULL)
        exit(-1);

    *v2 = 4;
    push(heap, v2);

    int *v3 = (int *) malloc(sizeof(int));
    if (v3 == NULL)
        exit(-1);

    *v3 = 7;
    push(heap, v3);

    printf("%i\n", *((int *) pop(heap)));
    printf("%i\n", *((int *) pop(heap)));
    printf("%i\n", *((int *) pop(heap)));

    free(v1);
    free(v2);
    free(v3);
    free(heap);

    return 0;
}