#include "vetores.h"

int *PiorCaso(int n) {
    int *array = (int *) malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        *(array + i) = n - i;
    }

    return array;
}

int *MelhorCaso(int n) {
    int *array = (int *) malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        *(array + i) = i;
    }

    return array;
}

int *CasoAleatorio(int n) {
    int *array = (int *) malloc(sizeof(int) * n);

    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        *(array + i) = rand() % n;
    }

    return array;
}

void ImprimirVetor(int *vetor, int n) {
    for (int i = 0; i < n; i++){
        printf("%i\n", *(vetor+i));
    }
}