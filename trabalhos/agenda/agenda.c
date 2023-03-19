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

#define ASC_ORDER 1
#define DESC_ORDER -1
#define NAME_LENGTH 9
#define PHONE_LENGTH 15 // +55053984655136\0

// **sentinel => *len **begin **end
// **nodes => *name *age *phone *prev *next
// heap => ordered queue

void PrintMenu();
void **Reset(void **sentinel);
void Clear(void **sentinel);
void Push(void **sentinel, char *name, short *age, char *phone);
void Pop(void **sentinel, char **name, short **age, char **phone);
void List(void **sentinel);

int main(int argc, char **argv) {
    void **sentinel = Reset(NULL);
    char **name = (char **) malloc(sizeof(char *));
    if (name == NULL) {
        printf("Not enough memory :(\n");
        exit(-1);
    }
    *name = (char *) malloc(sizeof(char) * (NAME_LENGTH + 1));
    if (*name == NULL) {
        printf("Not enough memory :(\n");
        exit(-1);
    }

    short **age = (short **) malloc(sizeof(short *));
    if (age == NULL) {
        printf("Not enough memory :(\n");
        exit(-1);
    }
    *age = (short *) malloc(sizeof(short));
    if (*age == NULL) {
        printf("Not enough memory :(\n");
        exit(-1);
    }

    char **phone = (char **) malloc(sizeof(char *));
    if (phone == NULL) {
        printf("Not enough memory :(\n");
        exit(-1);
    }
    *phone = (char *) malloc(sizeof(char) * (PHONE_LENGTH + 1));
    if (*phone == NULL) {
        printf("Not enough memory :(\n");
        exit(-1);
    }

    short *option = (short *) malloc(sizeof(short));
    if (option == NULL) {
        printf("Not enough memory :(\n");
        exit(-1);
    }
    *option = 4;

    do {
        scanf("%hi", option);

        switch (*option)
        {
            case 1:
                printf("Name: ");
                scanf("%9s", *name);

                printf("Age: ");
                scanf("%hi", *age);

                printf("Phone: ");
                scanf("%15s", *phone);

                Push(sentinel, *name, *age, *phone);
                break;
            case 2:
                Pop(sentinel, name, age, phone);

                printf("Name: %s\nAge: %hi\nPhone: %s\n", *name, *(*age), *phone);

                free(*name);
                free(*age);
                free(*phone);

                *name = (char *) malloc(sizeof(char) * (NAME_LENGTH + 1));
                if (*name == NULL) {
                    printf("Not enough memory :(\n");
                    exit(-1);
                }

                *age = (short *) malloc(sizeof(short));
                if (*age == NULL) {
                    printf("Not enough memory :(\n");
                    exit(-1);
                }

                *phone = (char *) malloc(sizeof(char) * (PHONE_LENGTH + 1));
                if (*phone == NULL) {
                    printf("Not enough memory :(\n");
                    exit(-1);
                }

                break;
            case 3:
                List(sentinel);
                break;
        }

    } while (*option != 4);

    free(option);
    free(*name);
    free(name);
    free(*age);
    free(age);
    free(*phone);
    free(phone);
    Clear(sentinel);
    free(*sentinel);
    free(sentinel);

    return 0;
}

void PrintMenu() {
    printf("\n==================\n");
    printf("1) Adicionar pessoa\n");
    printf("2) Remover pessoa\n");
    printf("3) Listar\n");
    printf("4) Sair\n");
    printf("==================\n");
}

void PrintInfo() {
    
}

void **Reset(void **sentinel) {
    if (sentinel != NULL) {
        Clear(sentinel);
        free(*sentinel); // dinamically allocated length
        free(sentinel);
    }

    void **newSentinel = (void **) malloc(sizeof(void *) * 3); // allocating
    if (newSentinel == NULL) {
        printf("Not enough memory :(\n");
        exit(-1);
    }

    int *length = (int *) malloc(sizeof(int));
    if (length == NULL) {
        printf("Not enough memory :(\n");
        exit(-1);
    }

    *length = 0;

    *(newSentinel) = length;   // heap length
    *(newSentinel + 1) = NULL; // first node
    *(newSentinel + 2) = NULL; // last node

    return newSentinel;
}

void Clear(void **sentinel) {
    int *length = (int *) *(sentinel);
    while (*length > 0) {
        char **name = (char **) malloc(sizeof(char *));
        short **age = (short **) malloc(sizeof(short *));
        char **phone = (char **) malloc(sizeof(char *));
        Pop(sentinel, name, age, phone);
        free(*name);
        free(name);
        free(*age);
        free(age);
        free(*phone);
        free(phone);
    }
}

void Push(void **sentinel, char *name, short *age, char *phone) {
    if (sentinel == NULL)
        return;
    else if (name == NULL)
        return;
    else if (age == NULL)
        return;
    else if (phone == NULL)
        return;

    void **node = (void *) malloc(sizeof(void *) * 5);
    if (node == NULL) {
        printf("Not enough memory :(\n");
        exit(-1);
    }

    char *nodeName = (char *) malloc(sizeof(char) * (NAME_LENGTH + 1));
    strcpy(nodeName, name);
    *(node) = nodeName;

    short *nodeAge = (short *) malloc(sizeof(short));
    *nodeAge = *age;
    *(node + 1) = nodeAge;

    char *nodePhone = (char *) malloc(sizeof(char) * (PHONE_LENGTH + 1));
    strcpy(nodePhone, phone);
    *(node + 2) = nodePhone;

    *(node + 3) = NULL;
    *(node + 4) = NULL;

    void **tempNode = *(sentinel + 1);
    if (tempNode == NULL) {
        *(sentinel + 1) = node; // first node
        *(sentinel + 2) = node; // last node
        
        int *length = (int *) *(sentinel);
        *(length) = *(length) + 1;

        return;
    }

    void **prevNode = tempNode;

    while (strcmp(*(node), *(tempNode)) == ASC_ORDER) {
        if (*(tempNode + 4) == NULL) {
            *(tempNode + 4) = node; // tempNode next node
            *(sentinel + 2) = node; // sentinel last node
            *(node + 3) = tempNode; // node prev node
    
            int *length = (int *) *(sentinel);
            *(length) = *(length) + 1;

            return;
        }

        tempNode = *(tempNode + 4);
    }

    *(node + 3) = *(tempNode + 3);
    *(tempNode + 3) = node;
    *(node + 4) = tempNode;
    
    int *length = (int *) *(sentinel);
    *(length) = *(length) + 1;
}

void Pop(void **sentinel, char **name, short **age, char **phone) {
    if (sentinel == NULL)
        return;

    void **firstNode = *(sentinel + 1);
    if (firstNode == NULL)
        return;

    *(name) = (char *) *(firstNode);
    *(age) = (short *) *(firstNode + 1);
    *(phone) = (char *) *(firstNode + 2);

    if (*(firstNode + 4) != NULL) {
        void **nextNode = *(firstNode + 4);
        *(nextNode + 3) = NULL;     // previuous node
        *(sentinel + 1) = nextNode;
    }
    else {
        *(sentinel + 1) = NULL; // first node
        *(sentinel + 2) = NULL; // last node
    }

    int *length = (int *) *(sentinel);
    *(length) = *(length) - 1;
    free(firstNode);
}

void List(void **sentinel) {

}