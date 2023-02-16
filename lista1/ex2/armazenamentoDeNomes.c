/**********************************************************************************
 * Exercício 2 - Lista 1                                                          *
 *                                                                                *
 * Faça um programa que armazena nomes em uma mesma string, que deve crescer ou   *
 * diminuir conforme os nomes forem colocados ou retirados. Deve apresentar o se- *
 * guinte menu:                                                                   *
 * 1) Adicionar nome                                                              *
 * 2) Remover nome                                                                *
 * 3) Listar                                                                      *
 * 4) Sair                                                                        *
 *                                                                                *
 **********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ImprimirMenu();
char *AdicionarNome(char *nomes, char *nome);
char *RemoverNome(char *nomes, int indice);
void ListarNomes(char *nomes);

enum opcoes_t {
    ADICIONAR_NOME = 1,
    REMOVER_NOME,
    LISTAR,
    SAIR
}; // enum para facilitar o uso do menu

int main(int argc, char **argv) {
    int opcaoEscolhida;

    char *nomes = (char *) malloc(sizeof(char) * 1); // aloca espaco para a string
    *(nomes) = '\0'; // armazena \0 na string vazia

    char *nome = (char *) malloc(sizeof(char) * 50);

    do {
        ImprimirMenu();

        printf(">> ");
        scanf("%i", &opcaoEscolhida);

        switch(opcaoEscolhida) {
            // verifica a opcao escolhida entre as acoes disponiveis
            case ADICIONAR_NOME:
                printf(">> ");
                scanf("%s", nome);

                nomes = AdicionarNome(nomes, nome);
                break;
            case REMOVER_NOME:
                int indice;
                printf(">> ");
                scanf("%i", &indice);

                nomes = RemoverNome(nomes, indice);
                break;
            case LISTAR:
                ListarNomes(nomes);
                break;
        }
    } while (opcaoEscolhida != SAIR);

    free(nome); // libera da memoria a string nome
    free(nomes); // libera da memoria a string nomes
}

/*
===============================================
ImprimirMenu

    Imprime o menu de ações que podem ser 
    executadas
===============================================
*/
void ImprimirMenu() {
    printf("\n==================\n");
    printf("1) Adicionar nome\n");
    printf("2) Remover nome\n");
    printf("3) Listar\n");
    printf("4) Sair\n");
    printf("==================\n");
}

/*
===============================================
AdicionarNome

    Adiciona um nome aos nomes armazenados

    Retorna o ponteiro para a lista de nomes 
    realocado
===============================================
*/
char *AdicionarNome(char *nomes, char *nome) {
    int tam_nomes = strlen(nomes);
    int tam_nome = strlen(nome);

    char *buff = (char *) realloc(nomes, sizeof(char) * (tam_nomes + tam_nome + 2)); // novo ponteiro para onde a string nomes sera armazenada com o tamanho adicional
    //                                                                          + 2 caracteres a mais, o \0 e o delimitador
    if (buff == NULL) {
        // verifica se houve algum erro
        free(nomes);
        printf("Memória insuficiente.");
        exit(-1);
    }

    *(buff+tam_nomes) = '-'; // adiciona um delimitador ao final da string de nomes

    for (int i = 1; i <= tam_nome; i++) {
        *(buff + tam_nomes + i) = *(nome + i - 1); // adiciona cada caracter do novo nome para a string de nomes
    }

    *(buff + tam_nomes + tam_nome + 1) = '\0'; // adiciona \0 ao final da string de nomes

    return buff;
}

/* 
===============================================
RemoverNome

    Remove um nome que esta armazenado no 
    índice informado

    Retorna o ponteiro para a lista de nomes
    realocado
===============================================
*/
char *RemoverNome(char *nomes, int indice) {
    int tam_nomes = strlen(nomes);

    int i = 0; // contador de posicoes de caracter
    int posInicial, posFinal; // posicao inicial e final do nome a ser removido
    int counter = 0; // contador de delimitadores
    while (counter < indice) {
        // incrementa o i enquanto nao chega na posicao certa do nome a ser removido
        if (nomes[i] == '-')
            counter++;
        else if (nomes[i] == '\0')
            return nomes; // verifica se a string ja acabou e nao altera nomes
        i++;
    }

    posInicial = i - 1; // posicao inicial = posicao em que esta o delimitador do nome a ser removido

    while (nomes[i] != '\0') {
        // incrementa i ate encontrar o proximo delimitador ou o final da string
        if (nomes[i] == '-')
            break;
        i++;
    }

    posFinal = i; // posicao final é posicao em que anterior ao delimitador da proxima string ou o final da string
    
    while (nomes[i] != '\0') {
        nomes[posInicial + (i - posFinal)] = nomes[i]; // desloca os nomes posteriores para posicao inicial
        i++;
    }

    nomes[posInicial + (i - posFinal)] = '\0'; // adiciona \0 ao final da string
    
    int tam_removido = posFinal - posInicial - 1; // calcula o tamanho do nome removido
    char *buff = (char *) realloc(nomes, sizeof(char) * (tam_nomes - tam_removido + 2)); // realoca a string com novo armazenamento

    return buff;
}

/*
===============================================
ListarNomes

    Lista todos os nomes armazenados
===============================================
*/
void ListarNomes(char *nomes) {
    int i = 0;
    int counter = 1;
    printf("\n----------- Nomes -----------");
    while (nomes[i] != '\0') {
        if (i == 0)
            printf("\n1 - "); // imprime o indice do primeiro nome
        else if (nomes[i] == '-' && i != 0)
            printf("\n%i - ", ++counter); // imprime o indice de cada nome
        else
            printf("%c", nomes[i]); // imprime caracter por caracter do nome
        i++;
    }
    printf("\n-----------------------------");
}