#include <stdio.h>
#include "../utils/vetores.h"

#define TAM_ARRAY 1000

int main() {
    int *array = CasoAleatorio(TAM_ARRAY);

    ImprimirVetor(array, TAM_ARRAY);

    int temp, i, j;
    for (i = 1; i < TAM_ARRAY; i++) {
        temp = *(array + i);
        j = i - 1;
        
        while ((j >= 0) && (temp < *(array + j))) {
            *(array + j + 1) = *(array + j);
            j--;
        }

        *(array + j + 1) = temp;

        /*
        for (int j = i - 1; j >= 0; j--) {
            if (temp < *(array + j)) {
                *(array + j + 1) = *(array + j);
                *(array + j) = temp;
            } else {
                break;
            } 
        }
        */
        
    }
    
    ImprimirVetor(array, TAM_ARRAY);

    free(array);

    return 0;
}