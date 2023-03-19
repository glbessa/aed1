#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    stack_t *stack = reset(NULL);
    if (stack == NULL) {
        printf("Deu ruim!\n");
        exit(-1);
    }
    int *v1 = (int *) malloc(sizeof(int));
    if (v1 == NULL)
        exit(-1);

    *v1 = 1;

    int *v2 = (int *) malloc(sizeof(int));
    if (v2 == NULL)
        exit(-1);

    *v2 = 4;

    int *v3 = (int *) malloc(sizeof(int));
    if (v3 == NULL)
        exit(-1);

    *v3 = 7;

    push(stack, v3);
    push(stack, v2);
    push(stack, v1);

    printf("%i\n", *((int *) pop(stack)));
    printf("%i\n", *((int *) pop(stack)));
    printf("%i\n", *((int *) pop(stack)));

    free(v1);
    free(v2);
    free(v3);
    free(stack);

    return 0;
}