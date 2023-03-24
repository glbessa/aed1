#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// list node struct
struct ListNode {
    int val;
    struct ListNode *next;
};

bool IsPalindrome(struct ListNode *head);
int GetValueByIndex(struct ListNode *head, unsigned int index);
int GetListLength(struct ListNode *head);
struct ListNode *Push(struct ListNode *head, int index, int value);
void Clear(struct ListNode *head);

int main(int argc, char **argv)
{
    int length = 0;
    int value = 0;
    struct ListNode *head = NULL;

    printf("List length: ");
    scanf("%i", &length);

    for (int i = 0; i < length; i++) {
        printf("Value: ");
        scanf("%i", &value);
        head = Push(head, -1, value);
        if (head == NULL) {
            printf("Error when appending to list... :-\n");
        }
    }
    
    bool result = IsPalindrome(head);
    if (result)
        printf("true\n");
    else
        printf("false\n");

    // freeing everything used to test
    Clear(head);

    return 0;
}

/*
===============================================
bool IsPalindrome(struct ListNode *head)

    Checks if the list of integer is a
    palindrome or not.

===============================================
*/
bool IsPalindrome(struct ListNode *head) {
    int length = GetListLength(head);
    int valueFirstHalf = 0, valueLastHalf = 0;

    int halfLength = floor((double) (length) / 2); // pay attention to casting, it won't work if you don't cast length to double before doing maths
    int startHalfTop = ceil((double) (length) / 2);
    int endHalfBottom = halfLength - 1;

    for (int i = 0; i < halfLength; i++) {
        valueFirstHalf = GetValueByIndex(head, (endHalfBottom - i));
        if (valueFirstHalf == NULL)
            return NULL;
        valueLastHalf = GetValueByIndex(head, (startHalfTop + i));
        if (valueLastHalf == NULL)
            return NULL;
        if (valueFirstHalf != valueLastHalf)
            return false;
    }

    return true;
}

/*
===============================================
int GetValueByIndex(struct ListNode *head, unsigned int index)

    Returns the value in that index of the list,
    the last value in the list if the index 
    is out of range or NULL if the head pointer
    is NULL

===============================================
*/
int GetValueByIndex(struct ListNode *head, unsigned int index) {
    if (head == NULL)
        return NULL;

    struct ListNode *temp = head;
    while(index > 0 && temp->next != NULL) {
        temp = temp->next;
        index--;
    }

    return temp->val;
}

/*
===============================================
int GetListLength(struct ListNode *head)

    Return the length of the list pointed by
    head.

===============================================
*/
int GetListLength(struct ListNode *head) {
    if (head == NULL)
        return 0;

    int length = 1;
    struct ListNode *temp = head;

    while (temp->next != NULL) {
        temp = temp->next;
        length++;
    }

    return length;
}

/*
===============================================
struct ListNode *Push(struct ListNode *head, int index, int value)

    Insert a value into the list.

===============================================
*/
struct ListNode *Push(struct ListNode *head, int index, int value) {
    struct ListNode *newNode = (struct ListNode *) malloc(sizeof(struct ListNode));
    if (newNode == NULL)
        return NULL;

    newNode->val = value;
    newNode->next = NULL;

    struct ListNode *temp = head;

    if (head == NULL || index == 0) {
        newNode->next = head;
        return newNode;
    }

    if (index == -1) {
        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newNode;

        return head;
    }

    int i = 0;
    while(temp->next != NULL || i != (index - 1)) {
        temp = temp->next;
        i++;
    }

    newNode->next = temp->next;
    temp->next = newNode;

    return head;
}

/*
===============================================
void Clear(struct ListNode *head)

    Clear all items into the list.

===============================================
*/
void Clear(struct ListNode *head) {
    if (head == NULL)
        return;
    
    struct ListNode *next = head;

    while(next != NULL) {
        head = next;
        next = head->next;
        free(head);
    }
}
