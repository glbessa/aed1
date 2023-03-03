#include <stdio.h>
#include <stdlib.h>

int JudgeCircle(char *moves);

int main() {
    char *movimentos = (char *) malloc(sizeof(char) * 20001); // o tamanho máximo de entrada é 2 * 10 ^ 4
    if (movimentos == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(-1);
    }

    printf("Movimentos: ");
    scanf("%s", movimentos);

    if (*movimentos == '\0') {
        free(movimentos);
        printf("Nenhum movimento informado!");
        exit(0); // acaba o programa caso ele não entre com nenhum movimento, já que o mínimo de movimentos é 1
    }

    if (JudgeCircle(movimentos))
        printf("verdadeiro\n");
    else
        printf("falso\n");

    free(movimentos);
    
    return 0;
}

/*
===============================================
JudgeCircle (char *moves)

    Argumentos:
    - moves: cadeira de caracteres com todos
      os movimentos feitos pelo robô

    Retorno: retorna verdadeiro caso o robô
    faça uma sequência de movimentos em que
    ele acabe voltando para o mesmo lugar de
    onde saiu

===============================================
*/
int JudgeCircle(char *moves) {
    int xPos = 0;
    int yPos = 0;

    while (*moves != '\0') {
        switch (*moves) {
            case 'R':
                xPos++;
                break;
            case 'L':
                xPos--;
                break;
            case 'U':
                yPos++;
                break;
            case 'D':
                yPos--;
                break;
        }

        moves++; // vai incrementando o ponteiro para que aponte para o próximo caracter
    }

    if (xPos == 0 && yPos == 0)
        return 1; // qualquer número diferente de 0 significa verdadeiro

    return 0; // retorna 0 que significa falso
}