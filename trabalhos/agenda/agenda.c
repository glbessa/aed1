#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define ASC_ORDER -1
#define DESC_ORDER 1
#define NAME_LENGTH 9
#define AGE_LENGTH 5 // Maximum value length that a short can store
#define PHONE_LENGTH 18

static void *dontForgetMe = NULL; // Used only in FreePBufferOnExit()

// pBuffer structure
// void *pBuffer
// 0 => int heapLength
// 1 => int (*orderPolicy) (void *node1, void *node2)
// 2 => int order
// 3 => void *firstNode
// 4 => void *lastNode
// 5 => short option
// 6 => char *name
// 7 => short age
// 8 => char *phone
// 9 => int tempHeapLength
// 10 => int (*orderTempHeapPolicy) (void *node1, void *node2)
// 11 => int tempHeapOrder
// 12 => void *tempHeapFirstNode
// 13 => void *tempHeapLastNode
// 14 => char *searchName
// 15 => char *formattedName
// 16 => short formattedAge
// 17 => char *formattedPhone

// Node structure
// void **node
// 0 => char *name
// 1 => short *age
// 2 => char *phone
// 3 => void **previousNode
// 4 => void **nextNode

void AddEntryOpt(void *pBuffer);
void ListEntriesOpt(void *pBuffer);
void RemoveFirstEntryOpt(void *pBuffer);
void RemoveEntryByNameOpt(void *pBuffer);
void ChangeOrderOpt(void *pBuffer);

int AlphabeticalOrderPolicy(void *value1, void *value2);
int AgeOrderPolicy(void *value1, void *value2);

void PrintMenu();
void PrintInfo(void *pBuffer);
void PrintOrderPolicyMenu();
void PrintOrderPriorityMenu();

void Clear(void *pBuffer);
void Push(void *pBuffer);
void Pop(void *pBuffer);
void RemoveByName(void *pBuffer);
void List(void *pBuffer);
void ChangeHeapOrderPolicyAndOrderPriority(void *pBuffer);

void *InitPBuffer();
void FreePBufferAndExit();
int *GetLengthAddr(void *pBuffer);
void IncrementLength(int *length);
void DecrementLength(int *length);
void **GetOrderPolicyAddr(void *pBuffer);
int *GetOrderPriorityAddr(void *pBuffer);
void **GetFirstNodeAddr(void *pBuffer);
void **GetLastNodeAddr(void *pBuffer);
short *GetOptionAddr(void *pBuffer);
char *GetTempNameAddr(void *pBuffer);
void SetTempName(void *pBuffer, char *name);
short *GetTempAgeAddr(void *pBuffer);
char *GetTempPhoneAddr(void *pBuffer);
void SetTempPhone(void *pBuffer, char *phone);
int *GetTempHeapLengthAddr(void *pBuffer);
void **GetTempHeapOrderPolicyAddr(void *pBuffer);
int *GetTempHeapOrderPriorityAddr(void *pBuffer);
void **GetTempHeapFirstNodeAddr(void *pBuffer);
void **GetTempHeapLastNodeAddr(void *pBuffer);
char *GetSearchNameAddr(void *pBuffer);
short *GetHeapSelectionAddr(void *pBuffer);
char *GetFormattedTempNameAddr(void *pBuffer);
char *GetFormattedTempAgeAddr(void *pBuffer);
char *GetFormattedTempPhoneAddr(void *pBuffer);

char *GetNodeNameAddr(void *node);
void SetNodeName(void *node, char *name);
short *GetNodeAgeAddr(void *node);
void SetNodeAge(void *node, short *age);
char *GetNodePhoneAddr(void *node);
void SetNodePhone(void *node, char *phone);
void **GetPreviousNodeAddr(void *node);
void SetPreviousNode(void *node, void *previous);
void **GetNextNodeAddr(void *node);
void SetNextNode(void *node, void *next);

int main() {
    void *pBuffer = InitPBuffer();
    
    //atexit(&FreePBufferOnExit);

    signal(SIGINT, FreePBufferAndExit); // Used to handle Ctrl + C in the middle of program

    do {
        PrintMenu();
        printf("Option: ");
        scanf("%hi", GetOptionAddr(pBuffer));
        while(fgetc(stdin) != '\n'); // Best way to flush stdin

        switch (*(GetOptionAddr(pBuffer)))
        {
            case 1:
                // Routine to add an entry to the agenda
                AddEntryOpt(pBuffer);
                break;
            case 2:
                // Routine to list all agenda entries
                ListEntriesOpt(pBuffer);
                break;
            case 3:
                // Routine to remove the agenda first entry
                RemoveFirstEntryOpt(pBuffer);
                break;
            case 4:
                // Routine to remove all entries with the informed name
                RemoveEntryByNameOpt(pBuffer);
                break;
            case 5:
                ChangeOrderOpt(pBuffer);
                break;
        }

    } while (*GetOptionAddr(pBuffer) != 6);

    // Freeing dynamically alocated memory
    *GetHeapSelectionAddr(pBuffer) = 0;
    Clear(pBuffer);
    *GetHeapSelectionAddr(pBuffer) = 1;
    Clear(pBuffer);
    free(pBuffer);

    return 0;
}

// --------------------------------------------------------------
// Option functions ---------------------------------------------

void AddEntryOpt(void *pBuffer) {
    printf("Name: ");
    scanf("%9[^\n]", GetTempNameAddr(pBuffer));
    while(fgetc(stdin) !='\n'); // Best way to flush stdin

    printf("Age: ");
    scanf("%hi", GetTempAgeAddr(pBuffer));
    while(fgetc(stdin) != '\n');

    printf("Phone: ");
    scanf("%18[^\n]", GetTempPhoneAddr(pBuffer));
    while(fgetc(stdin) != '\n');

    *GetHeapSelectionAddr(pBuffer) = 0;
    Push(pBuffer);
}

void ListEntriesOpt(void *pBuffer) {
    if (*GetLengthAddr(pBuffer) <= 0) {
        printf("Empty agenda!\n");
        return;
    }

    List(pBuffer);
}

void RemoveFirstEntryOpt(void *pBuffer) {
    if (*GetLengthAddr(pBuffer) <= 0) {
        printf("Empty agenda!\n");
        return;
    }

    *GetHeapSelectionAddr(pBuffer) = 0;
    Pop(pBuffer);
}

void RemoveEntryByNameOpt(void *pBuffer) {
    if (*GetLengthAddr(pBuffer) <= 0) {
        printf("Empty agenda!\n");
        return;
    }

    printf("Name: ");
    scanf("%9[^\n]", GetSearchNameAddr(pBuffer));
    while(fgetc(stdin) != '\n');
    RemoveByName(pBuffer);
}

void ChangeOrderOpt(void *pBuffer) {
    PrintOrderPolicyMenu();
    printf("Order policy: ");
    scanf("%hi", GetOptionAddr(pBuffer));

    switch (*GetOptionAddr(pBuffer)) {
        case 1:
            *GetTempHeapOrderPolicyAddr(pBuffer) = &AlphabeticalOrderPolicy;
            break;
        case 2:
            *GetTempHeapOrderPolicyAddr(pBuffer) = &AgeOrderPolicy;
            break;
        default:
            return;
    }

    PrintOrderPriorityMenu();
    printf("Order priority: ");
    scanf("%hi", GetOptionAddr(pBuffer));

    switch (*GetOptionAddr(pBuffer)) {
        case 1:
            *GetTempHeapOrderPriorityAddr(pBuffer) = ASC_ORDER;
            break;
        case 2:
            *GetTempHeapOrderPriorityAddr(pBuffer) = DESC_ORDER;
            break;
        default:
            return;
    }

    ChangeHeapOrderPolicyAndOrderPriority(pBuffer);
}

// ----------------------------------------------------------------
// CLI functions --------------------------------------------------

void PrintMenu() {
    printf("-------------------------\n");
    printf("1) Add entry\n");
    printf("2) List all entries\n");
    printf("3) Remove first entry\n");
    printf("4) Remove entries by name\n");
    printf("5) Change order\n");
    printf("6) Exit\n");
    printf("-------------------------\n");
}

void PrintOrderPolicyMenu() {
    printf("-------------\n");
    printf("1) Name order\n");
    printf("2) Age order\n");
    printf("-------------\n");
}

void PrintOrderPriorityMenu() {
    printf("-------------------\n");
    printf("1) Ascending order\n");
    printf("2) Descending order\n");
    printf("-------------------\n");
}

void PrintHeader() {
    printf("------------------------------------------\n");
    printf("| Name      | Age   | Phone              |\n");
    printf("------------------------------------------\n");
}

/*
============================================================
void PrintInfo(void *pBuffer)

    This function will pad the name, age and phone with a 
    predefined length and print it on screen.

============================================================
*/
void PrintInfo(void *pBuffer) {
    // Operations to pad name, age and phone with whitespaces at the end
    strcpy(GetFormattedTempNameAddr(pBuffer), GetTempNameAddr(pBuffer));
    memset(GetFormattedTempNameAddr(pBuffer) + strlen(GetTempNameAddr(pBuffer)), ' ', (NAME_LENGTH - strlen(GetTempNameAddr(pBuffer))));
    sprintf(GetFormattedTempAgeAddr(pBuffer), "%hi", *GetTempAgeAddr(pBuffer));
    memset(GetFormattedTempAgeAddr(pBuffer) + strlen(GetFormattedTempAgeAddr(pBuffer)), ' ', (AGE_LENGTH - strlen(GetFormattedTempAgeAddr(pBuffer))));
    strcpy(GetFormattedTempPhoneAddr(pBuffer), GetTempPhoneAddr(pBuffer));
    memset(GetFormattedTempPhoneAddr(pBuffer) + strlen(GetTempPhoneAddr(pBuffer)), ' ', (PHONE_LENGTH - strlen(GetTempPhoneAddr(pBuffer))));

    printf("------------------------------------------\n");
    printf("| %s | %s | %s |\n", GetFormattedTempNameAddr(pBuffer), GetFormattedTempAgeAddr(pBuffer), GetFormattedTempPhoneAddr(pBuffer));
    printf("------------------------------------------\n");
}

// ----------------------------------------------------------------
// Order Policies callbacks ---------------------------------------

int AlphabeticalOrderPolicy(void *value1, void *value2) {
    if (strcasecmp(GetNodeNameAddr((char *) value1), GetNodeNameAddr((char *) value2)) >= 1)
        return 1;
    else if (strcasecmp(GetNodeNameAddr((char *) value1), GetNodeNameAddr((char *) value2)) == 0)
        return 0;
    return -1;
}

int AgeOrderPolicy(void *value1, void *value2) {
    if (*GetNodeAgeAddr((int *) value1) > *GetNodeAgeAddr((int *) value2))
        return 1;
    else if (*GetNodeAgeAddr((int *) value1) == *GetNodeAgeAddr((int *) value2))
        return 0;
    return -1;
}

// ------------------------------------------------------------
// Heap functions ---------------------------------------------

void Clear(void *pBuffer) {
    if (!pBuffer)
        return;

    int *lengthAddr;
    void **firstNodeAddr;

    // The above if else is to decide with which heap the operations will occur
    if (*GetHeapSelectionAddr(pBuffer) == 0) {
        lengthAddr = GetLengthAddr(pBuffer);
        firstNodeAddr = GetFirstNodeAddr(pBuffer);
    }
    else {
        lengthAddr = GetTempHeapLengthAddr(pBuffer);
        firstNodeAddr = GetTempHeapFirstNodeAddr(pBuffer);
    }

    while (*lengthAddr > 0 && *firstNodeAddr != NULL) {
        Pop(pBuffer);
    }
}

void Push(void *pBuffer) {
    if (!pBuffer)
        return;

    void *node = (void *) malloc(sizeof(char) * (NAME_LENGTH + 1) + sizeof(short) + sizeof(char) * (PHONE_LENGTH + 1) + sizeof(void *) + sizeof(void *));
    if (!node)
        return;

    SetNodeName(node, GetTempNameAddr(pBuffer));
    SetNodeAge(node, GetTempAgeAddr(pBuffer));
    SetNodePhone(node, GetTempPhoneAddr(pBuffer));
    SetPreviousNode(node, NULL);
    SetNextNode(node, NULL);

    int *lengthAddr, *orderPriorityAddr;
    void **firstNodeAddr, **lastNodeAddr, *tempNode;
    int (*orderPolicy) (void *value1, void *value2); // Callback function

    // Heap selection
    if (*GetHeapSelectionAddr(pBuffer) == 0) {
        lengthAddr = GetLengthAddr(pBuffer);
        orderPolicy = *GetOrderPolicyAddr(pBuffer);
        orderPriorityAddr = GetOrderPriorityAddr(pBuffer);
        firstNodeAddr = GetFirstNodeAddr(pBuffer);
        lastNodeAddr = GetLastNodeAddr(pBuffer);
    }
    else {
        lengthAddr = GetTempHeapLengthAddr(pBuffer);
        orderPolicy = *GetTempHeapOrderPolicyAddr(pBuffer);
        orderPriorityAddr = GetTempHeapOrderPriorityAddr(pBuffer);
        firstNodeAddr = GetTempHeapFirstNodeAddr(pBuffer);
        lastNodeAddr = GetTempHeapLastNodeAddr(pBuffer);
    }

    tempNode = *firstNodeAddr;

    if (tempNode == NULL) {
        // First heap entry
        *firstNodeAddr = node;
        *lastNodeAddr = node;
        
        IncrementLength(lengthAddr);
        return;
    }

    while ((*orderPolicy)(GetNodeNameAddr(node), GetNodeNameAddr(tempNode)) != *orderPriorityAddr) {
        if (*GetNextNodeAddr(tempNode) == NULL) {
            // Add to the heap end
            SetPreviousNode(node, tempNode);
            SetNextNode(tempNode, node);
            *lastNodeAddr = node;
    
            IncrementLength(lengthAddr);
            return;
        }

        tempNode = *GetNextNodeAddr(tempNode);
    }

    // Add at the middle of heap

    if (*firstNodeAddr == tempNode) // Check if the new node will be the first or not
        *firstNodeAddr = node;
    else
        SetNextNode(*GetPreviousNodeAddr(tempNode), node);

    SetPreviousNode(node, *GetPreviousNodeAddr(tempNode));
    SetPreviousNode(tempNode, node);
    SetNextNode(node, tempNode);

    // Increment length
    IncrementLength(lengthAddr);
}

void Pop(void *pBuffer) {
    if (pBuffer == NULL)
        return;

    int *lengthAddr;
    void **firstNodeAddr, **lastNodeAddr, *tempNode;

    // Heap selection
    if (*GetHeapSelectionAddr(pBuffer) == 0) {
        lengthAddr = GetLengthAddr(pBuffer);
        firstNodeAddr = GetFirstNodeAddr(pBuffer);
        lastNodeAddr = GetLastNodeAddr(pBuffer);    
    }
    else {
        lengthAddr = GetTempHeapLengthAddr(pBuffer);
        firstNodeAddr = GetTempHeapFirstNodeAddr(pBuffer);
        lastNodeAddr = GetTempHeapLastNodeAddr(pBuffer);
    }

    tempNode = *firstNodeAddr;

    SetTempName(pBuffer, GetNodeNameAddr(tempNode));
    *GetTempAgeAddr(pBuffer) = *GetNodeAgeAddr(tempNode);
    SetTempPhone(pBuffer, GetNodePhoneAddr(tempNode));

    void *nextNode = *GetNextNodeAddr(tempNode);

    if (nextNode) {
        SetNextNode(tempNode, NULL);
        SetPreviousNode(nextNode, NULL);
        *firstNodeAddr = nextNode;
    }
    else {
        // If there isn't more node in the heap
        *firstNodeAddr = NULL;
        *lastNodeAddr = NULL;
    }

    DecrementLength(lengthAddr);
    free(tempNode);
}

// ----------------------------------------------------------
// Extended Heap functions ----------------------------------

void List(void *pBuffer) {
    PrintHeader();

    while (*GetLengthAddr(pBuffer) > 0 && *GetFirstNodeAddr(pBuffer) != NULL) {
        // Loop while heap length greater than 0 and heap first node different of null (just for caution)
        *GetHeapSelectionAddr(pBuffer) = 0;
        Pop(pBuffer);
        *GetHeapSelectionAddr(pBuffer) = 1;
        Push(pBuffer);

        PrintInfo(pBuffer);
    }

    // Cloning temp heap to main heap
    *GetHeapSelectionAddr(pBuffer) = 0;
    *GetLengthAddr(pBuffer) = *GetTempHeapLengthAddr(pBuffer);
    *GetFirstNodeAddr(pBuffer) = *GetTempHeapFirstNodeAddr(pBuffer);
    *GetLastNodeAddr(pBuffer) = *GetTempHeapLastNodeAddr(pBuffer);
    *GetTempHeapLengthAddr(pBuffer) = 0;
    *GetTempHeapFirstNodeAddr(pBuffer) = NULL;
    *GetTempHeapLastNodeAddr(pBuffer) = NULL;
}

void RemoveByName(void *pBuffer) {
    while (*GetLengthAddr(pBuffer) > 0 && *GetFirstNodeAddr(pBuffer) != NULL) {
        *GetHeapSelectionAddr(pBuffer) = 0;
        Pop(pBuffer);

        if (strcmp(GetTempNameAddr(pBuffer), GetSearchNameAddr(pBuffer)) != 0) {
            *GetHeapSelectionAddr(pBuffer) = 1;
            Push(pBuffer);
        }
    }

    // Cloning temp heap to main heap
    *GetHeapSelectionAddr(pBuffer) = 0;
    *GetLengthAddr(pBuffer) = *GetTempHeapLengthAddr(pBuffer);
    *GetFirstNodeAddr(pBuffer) = *GetTempHeapFirstNodeAddr(pBuffer);
    *GetLastNodeAddr(pBuffer) = *GetTempHeapLastNodeAddr(pBuffer);
    *GetTempHeapLengthAddr(pBuffer) = 0;
    *GetTempHeapFirstNodeAddr(pBuffer) = NULL;
    *GetTempHeapLastNodeAddr(pBuffer) = NULL;
}

void ChangeHeapOrderPolicyAndOrderPriority(void *pBuffer) {
    if (!pBuffer)
        return;

    while (*GetLengthAddr(pBuffer) > 0 && *GetFirstNodeAddr(pBuffer) != NULL) {
        *GetHeapSelectionAddr(pBuffer) = 0;
        Pop(pBuffer);
        *GetHeapSelectionAddr(pBuffer) = 1;
        Push(pBuffer);
    }

    *GetHeapSelectionAddr(pBuffer) = 0;
    *GetLengthAddr(pBuffer) = *GetTempHeapLengthAddr(pBuffer);
    *GetOrderPolicyAddr(pBuffer) = *GetTempHeapOrderPolicyAddr(pBuffer);
    *GetOrderPriorityAddr(pBuffer) = *GetTempHeapOrderPriorityAddr(pBuffer);
    *GetFirstNodeAddr(pBuffer) = *GetTempHeapFirstNodeAddr(pBuffer);
    *GetLastNodeAddr(pBuffer) = *GetTempHeapLastNodeAddr(pBuffer);
    *GetTempHeapLengthAddr(pBuffer) = 0;
    *GetTempHeapFirstNodeAddr(pBuffer) = NULL;
    *GetTempHeapLastNodeAddr(pBuffer) = NULL;
}

// ------------------------------------------------------------
// pBuffer functions ------------------------------------------

void *InitPBuffer() {
    void *pBuffer = (void *) malloc(sizeof(int) + sizeof(void *) + sizeof(int) + sizeof(void *) + sizeof(void *) + sizeof(short) + sizeof(char) * (NAME_LENGTH + 1) + sizeof(short) + sizeof(char) * (PHONE_LENGTH + 1) + sizeof(int) + sizeof(void *) + sizeof(int) + sizeof(void *) + sizeof(void *) + sizeof(char) * (NAME_LENGTH + 1) + sizeof(short) + sizeof(char) * (NAME_LENGTH + 1) + sizeof(char) * (AGE_LENGTH + 1) + sizeof(char) * (PHONE_LENGTH + 1));
    if (!pBuffer) {
        perror("Error");
        //fprintf(stderr, "Not enough memory :(\n");
        exit(-1);
    }

    dontForgetMe = pBuffer;

    *GetLengthAddr(pBuffer) = 0;
    *GetOrderPolicyAddr(pBuffer) = &AlphabeticalOrderPolicy;
    *GetOrderPriorityAddr(pBuffer) = ASC_ORDER;
    *GetFirstNodeAddr(pBuffer) = NULL;
    *GetLastNodeAddr(pBuffer) = NULL;
    memset(GetTempNameAddr(pBuffer), '\0', (NAME_LENGTH + 1));
    *GetTempAgeAddr(pBuffer) = 0;
    memset(GetTempPhoneAddr(pBuffer), '\0', (PHONE_LENGTH + 1));
    *GetOptionAddr(pBuffer) = 6;
    *GetTempHeapLengthAddr(pBuffer) = 0;
    *GetTempHeapOrderPolicyAddr(pBuffer) = &AlphabeticalOrderPolicy;
    *GetTempHeapOrderPriorityAddr(pBuffer) = ASC_ORDER;
    *GetTempHeapFirstNodeAddr(pBuffer) = NULL;
    *GetTempHeapLastNodeAddr(pBuffer) = NULL;
    memset(GetSearchNameAddr(pBuffer), '\0', NAME_LENGTH + 1);
    *GetHeapSelectionAddr(pBuffer) = 0;
    //strcpy(GetFormattedTempNameAddr(pBuffer), "\0");
    memset(GetFormattedTempNameAddr(pBuffer), '\0', NAME_LENGTH + 1);
    //strcpy(GetFormattedTempAgeAddr(pBuffer), "\0");
    memset(GetFormattedTempAgeAddr(pBuffer), '\0', AGE_LENGTH + 1);
    //strcpy(GetFormattedTempPhoneAddr(pBuffer), "\0");
    memset(GetFormattedTempPhoneAddr(pBuffer), '\0', PHONE_LENGTH + 1);

    return pBuffer;    
}

void FreePBufferAndExit() {
    *GetHeapSelectionAddr(dontForgetMe) = 0;
    Clear(dontForgetMe);
    *GetHeapSelectionAddr(dontForgetMe) = 1;
    Clear(dontForgetMe);
    free(dontForgetMe);
    exit(0);
}

int *GetLengthAddr(void *pBuffer) {
    return (int *) pBuffer;
}

void IncrementLength(int *length) {
    *length = *length + 1;
}

void DecrementLength(int *length) {
    *length = *length - 1;
}

void **GetOrderPolicyAddr(void *pBuffer) {
    return (void **) (pBuffer + sizeof(int));
}

int *GetOrderPriorityAddr(void *pBuffer) {
    return (int *) (pBuffer + sizeof(int) + sizeof(void *));
}

void **GetFirstNodeAddr(void *pBuffer) {
    return (void **) (pBuffer + sizeof(int) + sizeof(void *) + sizeof(int));
}

void **GetLastNodeAddr(void *pBuffer) {
    return (void **) (pBuffer + sizeof(int) + sizeof(void *) + sizeof(int) + sizeof(void *));
}

short *GetOptionAddr(void *pBuffer) {
    return (short *) (pBuffer + sizeof(int) + sizeof(void *) + sizeof(int) + sizeof(void *) + sizeof(void *));
}

char *GetTempNameAddr(void *pBuffer) {
    return (char *) (pBuffer + sizeof(int) + sizeof(void *) + sizeof(int) + sizeof(void *) + sizeof(void *) + sizeof(short));
}

void SetTempName(void *pBuffer, char *name) {
    strcpy(GetTempNameAddr(pBuffer), name);
}

short *GetTempAgeAddr(void *pBuffer) {
    return (short *) (pBuffer + sizeof(int) + sizeof(void *) + sizeof(int) + sizeof(void *) + sizeof(void *) + sizeof(short) + sizeof(char) * (NAME_LENGTH + 1));
}

char *GetTempPhoneAddr(void *pBuffer) {
    return (char *) (pBuffer + sizeof(int) + sizeof(void *) + sizeof(int) + sizeof(void *) + sizeof(void *) + sizeof(short) + sizeof(char) * (NAME_LENGTH + 1) + sizeof(short));
}

void SetTempPhone(void *pBuffer, char *phone) {
    strcpy(GetTempPhoneAddr(pBuffer), phone);
}

int *GetTempHeapLengthAddr(void *pBuffer) {
    return (int *) (pBuffer + sizeof(int) + sizeof(void *) + sizeof(int) + sizeof(void *) + sizeof(void *) + sizeof(short) + sizeof(char) * (NAME_LENGTH + 1) + sizeof(short) + sizeof(char) * (PHONE_LENGTH + 1));
}

void **GetTempHeapOrderPolicyAddr(void *pBuffer) {
    return (void **) (pBuffer + sizeof(int) + sizeof(void *) + sizeof(int) + sizeof(void *) + sizeof(void *) + sizeof(short) + sizeof(char) * (NAME_LENGTH + 1) + sizeof(short) + sizeof(char) * (PHONE_LENGTH + 1) + sizeof(int));
}

int *GetTempHeapOrderPriorityAddr(void *pBuffer) {
    return (int *) (pBuffer + sizeof(int) + sizeof(void *) + sizeof(int) + sizeof(void *) + sizeof(void *) + sizeof(short) + sizeof(char) * (NAME_LENGTH + 1) + sizeof(short) + sizeof(char) * (PHONE_LENGTH + 1) + sizeof(int) + sizeof(void *));
}

void **GetTempHeapFirstNodeAddr(void *pBuffer) {
    return (void **) (pBuffer + sizeof(int) + sizeof(void *) + sizeof(int) + sizeof(void *) + sizeof(void *) + sizeof(short) + sizeof(char) * (NAME_LENGTH + 1) + sizeof(short) + sizeof(char) * (PHONE_LENGTH + 1) + sizeof(int) + sizeof(void *) + sizeof(int));
}

void **GetTempHeapLastNodeAddr(void *pBuffer) {
    return (void **) (pBuffer + sizeof(int) + sizeof(void *) + sizeof(int) + sizeof(void *) + sizeof(void *) + sizeof(short) + sizeof(char) * (NAME_LENGTH + 1) + sizeof(short) + sizeof(char) * (PHONE_LENGTH + 1) + sizeof(int) + sizeof(void *) + sizeof(int) + sizeof(void *));
}

char *GetSearchNameAddr(void *pBuffer) {
    return (char *) (pBuffer + sizeof(int) + sizeof(void *) + sizeof(int) + sizeof(void *) + sizeof(void *) + sizeof(short) + sizeof(char) * (NAME_LENGTH + 1) + sizeof(short) + sizeof(char) * (PHONE_LENGTH + 1) + sizeof(int) + sizeof(void *) + sizeof(int) + sizeof(void *) + sizeof(void *));
}

short *GetHeapSelectionAddr(void *pBuffer) {
    return (short *) (pBuffer + sizeof(int) + sizeof(void *) + sizeof(int) + sizeof(void *) + sizeof(void *) + sizeof(short) + sizeof(char) * (NAME_LENGTH + 1) + sizeof(short) + sizeof(char) * (PHONE_LENGTH + 1) + sizeof(int) + sizeof(void *) + sizeof(int) + sizeof(void *) + sizeof(void *) + sizeof(char) * (NAME_LENGTH + 1));
}

char *GetFormattedTempNameAddr(void *pBuffer) {
    return (char *) (pBuffer + sizeof(int) + sizeof(void *) + sizeof(int) + sizeof(void *) + sizeof(void *) + sizeof(short) + sizeof(char) * (NAME_LENGTH + 1) + sizeof(short) + sizeof(char) * (PHONE_LENGTH + 1) + sizeof(int) + sizeof(void *) + sizeof(int) + sizeof(void *) + sizeof(void *) + sizeof(char) * (NAME_LENGTH + 1) + sizeof(short));
}

char *GetFormattedTempAgeAddr(void *pBuffer) {
    return (char *) (pBuffer + sizeof(int) + sizeof(void *) + sizeof(int) + sizeof(void *) + sizeof(void *) + sizeof(short) + sizeof(char) * (NAME_LENGTH + 1) + sizeof(short) + sizeof(char) * (PHONE_LENGTH + 1) + sizeof(int) + sizeof(void *) + sizeof(int) + sizeof(void *) + sizeof(void *) + sizeof(char) * (NAME_LENGTH + 1) + sizeof(short) + sizeof(char) * (NAME_LENGTH + 1));
}

char *GetFormattedTempPhoneAddr(void *pBuffer) {
    return (char *) (pBuffer + sizeof(int) + sizeof(void *) + sizeof(int) + sizeof(void *) + sizeof(void *) + sizeof(short) + sizeof(char) * (NAME_LENGTH + 1) + sizeof(short) + sizeof(char) * (PHONE_LENGTH + 1) + sizeof(int) + sizeof(void *) + sizeof(int) + sizeof(void *) + sizeof(void *) + sizeof(char) * (NAME_LENGTH + 1) + sizeof(short) + sizeof(char) * (NAME_LENGTH + 1) + sizeof(char) * (AGE_LENGTH + 1));
}

// -----------------------------------------------------
// Node functions --------------------------------------

char *GetNodeNameAddr(void *node) {
    return (char *) node;
}

void SetNodeName(void *node, char *name) {
    strcpy(GetNodeNameAddr(node), name);
}

short *GetNodeAgeAddr(void *node) {
    return (short *) (node + sizeof(char) * (NAME_LENGTH + 1));
}

void SetNodeAge(void *node, short *age) {
    *GetNodeAgeAddr(node) = *age;
}

char *GetNodePhoneAddr(void *node) {
    return (char *) (node + sizeof(char) * (NAME_LENGTH + 1) + sizeof(short));
}

void SetNodePhone(void *node, char *phone) {
    strcpy(GetNodePhoneAddr(node), phone);
}

void **GetPreviousNodeAddr(void *node) {
    return (void **) (node + sizeof(char) * (NAME_LENGTH + 1) + sizeof(short) + sizeof(char) * (PHONE_LENGTH + 1));
}

void SetPreviousNode(void *node, void *previous) {
    void **previousNodeAddr = GetPreviousNodeAddr(node);
    *previousNodeAddr = previous;
}

void **GetNextNodeAddr(void *node) {
    return (void **) (node + sizeof(char) * (NAME_LENGTH + 1) + sizeof(short) + sizeof(char) * (PHONE_LENGTH + 1) + sizeof(void *));
}

void SetNextNode(void *node, void *next) {
    void **nextNodeAddr = GetNextNodeAddr(node);
    *nextNodeAddr = next;
}
// ------------------------------------------------------