#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char **CombinacoesDeLetras(char *digitos, int *tamanhoVetor);
int VerificarQuantidadeCombinacoes(char *digitos);
void ImprimirVetor(char **vetor, int n);

const char COMB_2[3] = {'a', 'b', 'c'};
const char COMB_3[3] = {'d', 'e', 'f'};
const char COMB_4[3] = {'g', 'h', 'i'};
const char COMB_5[3] = {'j', 'k', 'l'};
const char COMB_6[3] = {'m', 'n', 'o'};
const char COMB_7[4] = {'p', 'q', 'r', 's'};
const char COMB_8[3] = {'t', 'u', 'v'};
const char COMB_9[4] = {'w', 'x', 'y', 'z'};

int main() {
    char **combinacoes;
    int tamVetor;
    char *digitos = (char *) malloc(sizeof(char) * 50);

    printf("Dígitos: ");
    scanf("%s", digitos);
    
    combinacoes = CombinacoesDeLetras(digitos, &tamVetor);
    ImprimirVetor(combinacoes, tamVetor);

    free(digitos);
    free(combinacoes);
    return 0;
}

char **CombinacoesDeLetras(char *digitos, int *tamanhoVetor) {
    *(tamanhoVetor) = VerificarQuantidadeCombinacoes(digitos);
    int tamPalavra = strlen(digitos);
    
    char **combinacoes = (char **) malloc(sizeof(char *) * *(tamanhoVetor));
    for (int i = 0; i < *tamanhoVetor; i++) {
        *(combinacoes + i) = (char *) malloc(sizeof(char) * (tamPalavra + 1));
        for (int j = 0; j < tamPalavra; j++) {
            switch (*(digitos+j)) {
                case '2':
                    *(*(combinacoes + i) + j) = COMB_2[(i / ((int) pow(3, (tamPalavra - j - 1)))) % 3];
                    break;
                case '3':
                    *(*(combinacoes + i) + j) = COMB_3[(i / ((int) pow(3, (tamPalavra - j - 1)))) % 3];
                    break;
                case '4':
                    *(*(combinacoes + i) + j) = COMB_4[(i / ((int) pow(3, (tamPalavra - j - 1)))) % 3];
                    break;
                case '5':
                    *(*(combinacoes + i) + j) = COMB_5[(i / ((int) pow(3, (tamPalavra - j - 1)))) % 3];
                    break;
                case '6':
                    *(*(combinacoes + i) + j) = COMB_6[(i / ((int) pow(3, (tamPalavra - j - 1)))) % 3];
                    break;
                case '7':
                    *(*(combinacoes + i) + j) = COMB_7[(i / ((int) pow(4, (tamPalavra - j - 1)))) % 4];
                    break;
                case '8':
                    *(*(combinacoes + i) + j) = COMB_8[(i / ((int) pow(3, (tamPalavra - j - 1)))) % 3];
                    break;
                case '9':
                    *(*(combinacoes + i) + j) = COMB_9[(i / ((int) pow(4, (tamPalavra - j - 1)))) % 4];
                    break;
            }
        }
        *(*(combinacoes + i) + tamPalavra) = '\0';
    }

    return combinacoes;
}

int VerificarQuantidadeCombinacoes(char *digitos) {
    int quantCombinacoes = 1, i = 0;

    while(*(digitos+i) != '\0') {
        if ((*(digitos+i) == '7') || (*(digitos+i) == '9'))
            quantCombinacoes *= 4;
        else
            quantCombinacoes *= 3;
        i++;
    }

    return quantCombinacoes;
}

void ImprimirVetor(char **vetor, int n) {
    printf("[ ");
    for (int i = 0; i < (n-1); i++) {
        printf(" \"%s\" ,", *(vetor+i));
    }
    printf(" \"%s\" ]\n", *(vetor+n-1));
}