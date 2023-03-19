#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    queue_t *queue = reset(NULL);
    int *v1 = (int *) malloc(sizeof(int));
    if (v1 == NULL)
        exit(-1);

    *v1 = 1;
    push(queue, v1);

    int *v2 = (int *) malloc(sizeof(int));
    if (v2 == NULL)
        exit(-1);

    *v2 = 4;
    push(queue, v2);

    int *v3 = (int *) malloc(sizeof(int));
    if (v3 == NULL)
        exit(-1);

    *v3 = 7;
    push(queue, v3);

    printf("%i\n", *((int *) pop(queue)));
    printf("%i\n", *((int *) pop(queue)));
    printf("%i\n", *((int *) pop(queue)));

    return 0;
}