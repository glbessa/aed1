#include <stdio.h>
#include <stdlib.h>

enum opcoes_t {
    INSERIR_VALOR=1,
    CONSULTAR_VALOR,
    SAIR
};

int main() {
    int *tamanhoDaMemoria = (int *) malloc(sizeof(int));
    *tamanhoDaMemoria = 0;
    short *opcaoEscolhida = (short *) malloc(sizeof(short));
    *opcaoEscolhida = 0;
    int *memoria = NULL;
    int *pos = (int *) malloc(sizeof(int));

    printf("Tamanho da memoria: ");
    scanf("%d", tamanhoDaMemoria);

    memoria = (int *) malloc(sizeof(int) * *tamanhoDaMemoria);

    do {
        printf("\n1) INSERIR VALOR\n");
        printf("2) CONSULTAR VALOR\n");
        printf("3) SAIR\n");

        scanf("%hd", opcaoEscolhida);

        switch(*opcaoEscolhida) {
            case INSERIR_VALOR:
                *pos = 0;

                printf("Posicao a ser inserido o valor: ");
                scanf("%i", pos);

                printf("Valor a ser inserido: ");
                scanf("%i", (memoria + *pos));

                break;

            case CONSULTAR_VALOR:
                *pos = 0;

                printf("Posicao a ser consultada: ");
                scanf("%i", pos);

                printf("Valor na posicao %i: %i\n", *pos, *(memoria + *pos));

                break;
        }
    } while (*opcaoEscolhida != SAIR);

    free(memoria);
    free(tamanhoDaMemoria);
    free(opcaoEscolhida);
    free(pos);

    return 0;
}