/**********************************************************************************
 * Agenda                                                                         *
 *                                                                                *
 *                                                                                *
 *                                                                                *
 **********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASC_ORDER 1
#define NAME_LENGTH 9
#define PHONE_LENGTH 18 

// Sentinel structure
// void **sentinel
// *(sentinel + 0) => int *length
// *(sentinel + 1) => void **firstNode
// *(sentinel + 2) => void **lastNode

// Node structure
// void **node
// *(node + 0) => char *name
// *(node + 1) => short *age
// *(node + 2) => char *phone
// *(node + 3) => void **previousNode
// *(node + 4) => void **nextNode

void InitializeNameAgePhone(char **name, short **age, char **phone);
void PrintMenu();
void PrintInfo(char *name, short *age, char *phone);
void **Reset(void **sentinel);
void Clear(void **sentinel);
void Push(void **sentinel, char *name, short *age, char *phone);
void Pop(void **sentinel, char **name, short **age, char **phone);
void RemoveByName(void ***sentinel, char *targetName);
void List(void ***sentinel);

void **GetFirstNode(void **sentinel);
int *GetLength(void **sentinel);
void SetLength(void **sentinel, int *length);
void IncrementLength(void **sentinel);
void DecrementLength(void **sentinel);
void **GetFirstNode(void **sentinel);
void SetFirstNode(void **sentinel, void **node);
void **GetLastNode(void **sentinel);
void SetLastNode(void **sentinel, void **node);
char *GetNodeName(void **node);
void SetNodeName(void **node, char *name);
short *GetNodeAge(void **node);
void SetNodeAge(void **node, short *age);
char *GetNodePhone(void **node);
void SetNodePhone(void **node, char *phone);
void **GetPreviousNode(void **node);
void SetPreviousNode(void **node, void **prevNode);
void **GetNextNode(void **node);
void SetNextNode(void **node, void **nextNode);

int main(int argc, char **argv) {
    void **sentinel = Reset(NULL); // Initializing heap

    char *name, *phone;
    short *age;

    InitializeNameAgePhone(&name, &age, &phone);

    short *option = (short *) malloc(sizeof(short));
    if (option == NULL) {
        free(name);
        free(age);
        free(phone);
        printf("Not enough memory :(\n");
        exit(-1);
    }
    *option = 5;

    do {
        PrintMenu();
        printf(">> ");
        scanf("%hi", option);
        scanf("%*c");

        switch (*option)
        {
            case 1:
                // Routine to add an entry to the agenda
                printf("Name: ");
                scanf("%[^\n]*c", name);

                printf("Age: ");
                scanf("%hi", age);
                scanf("%*c");
                fflush(stdin);

                printf("Phone: ");
                scanf("%[^\n]*c", phone);

                Push(sentinel, name, age, phone);
                break;

            case 2:
                // Routine to list all agenda entries
                if (*GetLength(sentinel) <= 0) {
                    printf("Empty agenda!\n");
                    break;
                }

                List(&sentinel);
                break;

            case 3:
                // Routine to remove the agenda first entry
                if (*GetLength(sentinel) <= 0) {
                    printf("Empty agenda!\n");
                    break;
                }

                free(name);
                free(age);
                free(phone);

                Pop(sentinel, &name, &age, &phone); // Problem here solved
                PrintInfo(name, age, phone);

                free(name);
                free(age);
                free(phone);

                InitializeNameAgePhone(&name, &age, &phone);

                break;

            case 4:
                // Routine to remove all entries with the informed name
                if (*GetLength(sentinel) <= 0) {
                    printf("Empty agenda!\n");
                    break;
                }

                scanf("%9s", name);
                RemoveByName(&sentinel, name);
                break;
        }

    } while (*option != 5);

    // Freeing dynamically alocated memory
    free(option);
    free(name);
    free(age);
    free(phone);

    // Freeing dynamically allocated data structure
    Clear(sentinel);
    free(*sentinel);
    free(sentinel);

    return 0;
}

// ---------------------------------------------------------
// Lasy functions ------------------------------------------

void InitializeNameAgePhone(char **name, short **age, char **phone) {
    if (name == NULL || age == NULL || phone == NULL) {
        printf("Please, contact the developer!\n");
        exit(-1);
    }
    
    *name = (char *) malloc(sizeof(char) * (NAME_LENGTH + 1));
    if (*name == NULL) {
        printf("Not enough memory :(\n");
        exit(-1);
    }

    *age = (short *) malloc(sizeof(short));
    if (*age == NULL) {
        free(*name);
        printf("Not enough memory :(\n");
        exit(-1);
    }

    *phone = (char *) malloc(sizeof(char) * (PHONE_LENGTH + 1));
    if (*phone == NULL) {
        free(*name);
        free(*age);
        printf("Not enough memory :(\n");
        exit(-1);
    }
}


// ----------------------------------------------------------
// CLI functions --------------------------------------------

void PrintMenu() {
    printf("=========================\n");
    printf("1) Add entry\n");
    printf("2) List all entries\n");
    printf("3) Remove first entry\n");
    printf("4) Remove entries by name\n");
    printf("5) Exit\n");
    printf("=========================\n");
}

void PrintHeader(char *borderChar) {
    printf("-----------------------------------\n");
    printf("|   Name   | Age |      Phone     |\n");
    printf("-----------------------------------\n");
}

void PrintInfo(char *name, short *age, char *phone) {
    int *nameLen = (int *) malloc(sizeof(int));
    if (nameLen == NULL)
        return;
    *nameLen = strlen(name);

    char *ageStr = (char *) malloc(sizeof(char) * 6);
    if (ageStr == NULL) {
        free(nameLen);
        return;
    }
    sprintf(ageStr, "%hi", *age);

    int *ageLen = (int *) malloc(sizeof(int));
    if (ageLen == NULL) {
        free(nameLen);
        free(ageStr);
        return;
    }
    *ageLen = strlen(ageStr);

    int *phoneLen = (int *) malloc(sizeof(int));
    if (phoneLen == NULL) {
        free(nameLen);
        free(ageStr);
        free(ageLen);
        return;
    }
    *phoneLen = strlen(phone);

    int *borderLen = (int *) malloc(sizeof(int));
    if (borderLen == NULL) {
        free(nameLen);
        free(ageStr);
        free(ageLen);
        free(phoneLen);
        return;
    }
    *borderLen = (10 + *nameLen + *phoneLen + *ageLen);

    char *border = (char *) malloc(sizeof(char) * (*borderLen + 1));
    if (border == NULL) {
        free(nameLen);
        free(ageStr);
        free(ageLen);
        free(phoneLen);
        free(borderLen);
        return;
    }

    memset(border, '-', *borderLen);
    *(border + *borderLen) = '\0';

    printf("%s\n", border);
    printf("| %s | %hi | %s |\n", name, *age, phone);
    printf("%s\n", border);

    free(nameLen);
    free(ageStr);
    free(ageLen);
    free(phoneLen);
    free(borderLen);
    free(border);
}

// ----------------------------------------------------------
// Extended Heap functions ----------------------------------

void List(void ***sentinel) {
    void **newSentinel = Reset(NULL);

    char *name;
    short *age;
    char *phone;

    PrintHeader(NULL);

    while (*GetLength(*sentinel) > 0 && GetFirstNode(*sentinel) != NULL) {
        Pop(*sentinel, &name, &age, &phone);
        Push(newSentinel, name, age, phone);

        PrintInfo(name, age, phone);

        free(name);
        free(age);
        free(phone); // double free
    }

    free(**sentinel);
    free(*sentinel);

    *sentinel = newSentinel;
}

void RemoveByName(void ***sentinel, char *targetName) {
    void **newSentinel = Reset(NULL);

    char *name;
    short *age;
    char *phone;   

    while (*GetLength(*sentinel) > 0 && GetFirstNode(*sentinel) != NULL) {
        Pop(*sentinel, &name, &age, &phone);

        if (strcmp(name, targetName) != 0) {
            Push(newSentinel, name, age, phone);
        }

        free(name);
        free(age);
        free(phone);
    }

    free(**sentinel);
    free(*sentinel);

    *sentinel = newSentinel;
}

// ------------------------------------------------------------
// Heap functions ---------------------------------------------

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
        free(newSentinel);
        exit(-1);
    }
    *length = 0;

    SetLength(newSentinel, length); // heap length
    SetFirstNode(newSentinel, NULL); // first node
    SetLastNode(newSentinel, NULL); // last node

    return newSentinel;
}

void Clear(void **sentinel) {
    char *name;
    short *age;
    char *phone;
    while (*GetLength(sentinel) > 0 && GetFirstNode(sentinel) != NULL) {
        Pop(sentinel, &name, &age, &phone);
        free(name);
        free(age);
        free(phone);
    }
}

void Push(void **sentinel, char *name, short *age, char *phone) {
    if (sentinel == NULL || name == NULL || age == NULL || phone == NULL)
        return;

    void **node = (void **) malloc(sizeof(void *) * 5);
    if (node == NULL)
        return;

    char *nodeName, *nodePhone;
    short *nodeAge;

    InitializeNameAgePhone(&nodeName, &nodeAge, &nodePhone);
    
    strcpy(nodeName, name);
    SetNodeName(node, nodeName);
    
    *nodeAge = *age;
    SetNodeAge(node, nodeAge);

    strcpy(nodePhone, phone);
    SetNodePhone(node, nodePhone);

    SetPreviousNode(node, NULL);
    SetNextNode(node, NULL);

    void **tempNode = GetFirstNode(sentinel);
    if (tempNode == NULL) {
        // Identify that this is heap first node
        SetFirstNode(sentinel, node);
        SetLastNode(sentinel, node);
        
        IncrementLength(sentinel);
        return;
    }

    while (strcmp(GetNodeName(node), GetNodeName(tempNode)) >= ASC_ORDER) {
        // While new node name is alphabetically after tempNode name...
        if (GetNextNode(tempNode) == NULL) {
            // Check if there isn't more nodes in the heap and adding at the end of the heap
            SetNextNode(tempNode, node);
            SetLastNode(sentinel, node);
            SetPreviousNode(node, tempNode);
    
            // Increment length
            IncrementLength(sentinel);
            return;
        }

        tempNode = GetNextNode(tempNode);
    }

    if (GetFirstNode(sentinel) == tempNode)
        SetFirstNode(sentinel, node);
    else
        SetNextNode(GetPreviousNode(tempNode), node);

    SetPreviousNode(node, GetPreviousNode(tempNode));
    SetPreviousNode(tempNode, node);
    SetNextNode(node, tempNode);

    // Increment length
    IncrementLength(sentinel);
}

void Pop(void **sentinel, char **name, short **age, char **phone) {
    if (sentinel == NULL)
        return;

    void **firstNode = GetFirstNode(sentinel);
    if (firstNode == NULL)
        return;

    *(name) = GetNodeName(firstNode);
    *(age) = GetNodeAge(firstNode);
    *(phone) = GetNodePhone(firstNode);

    void **nextNode = GetNextNode(firstNode);

    if (nextNode != NULL) {
        SetNextNode(firstNode, NULL);
        SetPreviousNode(nextNode, NULL);
        SetFirstNode(sentinel, nextNode);
    }
    else {
        // If there isn't more node in the heap
        SetFirstNode(sentinel, NULL);
        SetLastNode(sentinel, NULL);
    }

    DecrementLength(sentinel);
    free(firstNode);
}

// ---------------------------------------------------
// Sentinel functions --------------------------------

int *GetLength(void **sentinel) {
    int *length = (int *) *sentinel;
    return length;
}

void SetLength(void **sentinel, int *length) {
    *sentinel = length;
}

void IncrementLength(void **sentinel) {
    int *len = (int *) *sentinel;
    *len = *len + 1;
}

void DecrementLength(void **sentinel) {
    int *len = (int *) *sentinel;
    *len = *len - 1;
}

void **GetFirstNode(void **sentinel) {
    return *(sentinel + 1);
}

void SetFirstNode(void **sentinel, void **node) {
    *(sentinel + 1) = node;
}

void **GetLastNode(void **sentinel) {
    return *(sentinel + 2);
}

void SetLastNode(void **sentinel, void **node) {
    *(sentinel + 2) = node;
}

// -----------------------------------------------------
// Node functions --------------------------------------

char *GetNodeName(void **node) {
    return (char *) *node;
}

void SetNodeName(void **node, char *name) {
    *(node) = name;
}

short *GetNodeAge(void **node) {
    return (short *) *(node + 1);
}

void SetNodeAge(void **node, short *age) {
    *(node + 1) = age;
}

char *GetNodePhone(void **node) {
    return (char *) *(node + 2);
}

void SetNodePhone(void **node, char *phone) {
    *(node + 2) = phone;
}

void **GetPreviousNode(void **node) {
    return *(node + 3);
}

void SetPreviousNode(void **node, void **prevNode) {
    *(node + 3) = prevNode;
}

void **GetNextNode(void **node) {
    return *(node + 4);
}

void SetNextNode(void **node, void **nextNode) {
    *(node + 4) = nextNode;
}

// ------------------------------------------------------