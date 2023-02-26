/**********************************************************************************
 * Exercício 3 - Lista 2                                                          *
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

#define END_STR '\0'
#define COD_PAIS "055"
#define DDD "053"
#define TAM_TEL 15

void ImprimirMenu();
char *AdicionarPessoa(void *pBuffer, char *nome, unsigned char *idade, unsigned long *tel) ;
char *RemoverPessoa(char *nomes, int indice);
void ListarAgenda(void *pBuffer);

enum opcoes_t {
    ADICIONAR_PESSOA = 1,
    REMOVER_PESSOA,
    LISTAR,
    SAIR
}; // Enum para facilitar o uso do menu

union {
    struct {
        char c0;
        char c1;
        char c2;
        char c3;
        char c4;
        char c5;
        char c6;
        char c7;
    };
    long resultado;
} concatenador;


int main(int argc, char **argv) {
    short *opcaoEscolhida = (short *) malloc(sizeof(short));

    void *pBuffer = (void *) malloc(sizeof(char) * 1); // aloca espaco para a string
    char *pBufferMod = (char *) pBuffer;
    *(pBufferMod) = END_STR; // armazena \0 na string vazia

    char *nome = (char *) malloc(sizeof(char) * 50);
    unsigned char *idade = (unsigned char *) malloc(sizeof(unsigned char)); // Aloca espaco para um numero de 0 ate 256
    unsigned long *tel = (unsigned long *) malloc(sizeof(unsigned long)); // Aloca espaco para 3 digitos do pais (55), 3 digitos do ddd (053), 9 digitos do numero e o fim da string

    do {
        ImprimirMenu();

        printf(">> ");
        scanf("%hi", opcaoEscolhida);

        switch(*opcaoEscolhida) {
            // verifica a opcao escolhida entre as acoes disponiveis
            case ADICIONAR_PESSOA:
                printf("Nome: ");
                scanf("%s", nome);

                printf("Idade: ");
                scanf("%hhd", idade);

                printf("Telefone (somente números): ");
                scanf("%lu", tel);

                pBuffer = AdicionarPessoa(pBuffer, nome, idade, tel);
                break;
            case REMOVER_PESSOA:
                int indice;
                printf(">> ");
                scanf("%i", &indice);

                pBuffer = RemoverPessoa(pBuffer, indice);
                break;
            case LISTAR:
                ListarAgenda(pBuffer);
                break;
        }
    } while (*(opcaoEscolhida) != SAIR);

    free(nome); // libera da memoria a string nome
    free(idade);
    free(tel);
    free(pBuffer); // libera da memoria a string nomes
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
    printf("1) Adicionar pessoa\n");
    printf("2) Remover pessoa\n");
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
char *AdicionarPessoa(void *pBuffer, char *nome, unsigned char *idade, unsigned long *tel) {
    int tamNome = strlen(nome);

    unsigned long tamPBuffer = 1;
    unsigned long tamBuff = tamPBuffer + (tamNome + 1) * sizeof(char) + sizeof(*idade) + sizeof(*tel);
    void *buff = (void *) realloc(pBuffer, tamBuff); // novo ponteiro para onde a string nomes sera armazenada com o tamanho adicional
    char *buffMod = (char *) buff;

    if (buff == NULL) {
        // verifica se houve algum erro
        free(nome);
        free(idade);
        free(tel);
        free(pBuffer);
        printf("Memória insuficiente.");
        exit(-1);
    }

    *(buffMod + tamPBuffer - 1) = '|'; // Adiciona um delimitador para cada bloco de informações (nome, idade, telefone)

    for (int i = 0; i < tamNome; i++) {
        *(buffMod + (tamPBuffer - 1) + 1 + i) = *(nome + i); // adiciona cada caracter do novo nome para a string de nomes
    }

    *(buffMod + (tamPBuffer - 1) + tamNome + 1) = '/'; // Separa o nome do resto das informações
    *(buffMod + (tamPBuffer - 1) + tamNome + 2) = *idade;

    for (int i = 0; i < sizeof(*tel); i++) {
        *(buffMod + (tamPBuffer - 1) + tamNome + 3 + i) = *(((char *) tel) + i);
    }

    *(buffMod + tamBuff - 1) = '!'; // adiciona \0 ao final da string de nomes

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
char *RemoverPessoa(char *nomes, int indice) {
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
void ListarAgenda(void *pBuffer) {
    int i = 0;
    int counter = 1;
    char *pBufferMod = (char *) pBuffer;

    printf("\n----------- Agenda -----------");
    while (pBufferMod[i] != '!') {
        if (pBufferMod[i++] == '|') {
            printf("\n%i - ", counter++);
            while (pBufferMod[i] != '/') {
                printf("%c", pBufferMod[i]);
                i++;
            }
            printf(" - %hhd - ", pBufferMod[++i]);
            concatenador.c0 = pBufferMod[++i];
            concatenador.c1 = pBufferMod[++i];
            concatenador.c2 = pBufferMod[++i];
            concatenador.c3 = pBufferMod[++i];
            concatenador.c4 = pBufferMod[++i];
            concatenador.c5 = pBufferMod[++i];
            concatenador.c6 = pBufferMod[++i];
            concatenador.c7 = pBufferMod[++i];
            printf("%lu", concatenador.resultado);
        }
        i++;
    }
    printf("\n-----------------------------");
}

void padronizarTelefone(char *tel) {
    char *tresDigitos = (char *) malloc(sizeof(char) * 4);
    *tresDigitos = *tel;
    *(tresDigitos + 1) = *(tel + 1);
    *(tresDigitos + 2) = *(tel + 2);

    if (tresDigitos != COD_PAIS) {
        // Verifica se o telefone nao inicia com o codigo do pais

        if (tresDigitos != DDD) {
            // Verifica se o telefon nao inicia com o codigo da regiao (DDD)
            int i = TAM_TEL - 6;
            while (i >= 0) {
                *(tel+i+6) = *(tel+i);
                i--;
            }

            *(tel) = '+';
            *(tel+1) = '5';
            *(tel+2) = '5';
            *(tel+3) = '0';
            *(tel+4) = '5';
            *(tel+5) = '3';
        } else {
            // Executado caso o ddd ja estiver presente

            int i = TAM_TEL - 3;
            while (i >= 3) {
                // Move todos os numeros 3 posicoes para frente ate a 3 posicao do vetor
                *(tel+i+3) = *(tel+i);
                i--;
            }

            *(tel+3) = '0';
            *(tel+4) = '5';
            *(tel+5) = '3';
        }
    }

    free(tresDigitos);
}