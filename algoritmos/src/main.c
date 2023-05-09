#include <stdio.h>
#include <stdlib.h>
#include "algorithms.h"

int main() {
    int n = 5000;
    int *array = RandomCase(n);

    PrintArray(array, n);

    HeapSort(array, n);

    PrintArray(array, n);

    free(array);
    return 0;
}