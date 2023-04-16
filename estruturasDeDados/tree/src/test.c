#include <stdio.h>
#include <stdlib.h>

#include "binaryTree.h"

void *AllocInt(int value);

int main() {
    void *a = AllocInt(10);
    void *b = AllocInt(20);
    void *c = AllocInt(5);
    void *d = AllocInt(7);
    void *e = AllocInt(40);
    void *f = AllocInt(35);
    void *g = AllocInt(3);
    void *h = AllocInt(18);
    binaryTree_t *tree = BTInsert(NULL, a);
    BTInsert(tree, b);
    BTInsert(tree, c);
    BTInsert(tree, d);
    BTInsert(tree, e);
    BTInsert(tree, f);
    BTInsert(tree, g);
    BTInsert(tree, h);

    BTListPreOrder(tree);
    //ListInOrder(tree);
    //ListPostOrder(tree);

    int result = BTFind(tree, f);
    if (result)
        printf("\nEncontrado");
    else
        printf("\nNão encontrado");

    printf("\n");

    printf("%i\n", BTHeight(tree));

    BTClear(tree);

    return 0;
}

void *AllocInt(int value) {
    int *pointer = (int *) malloc(sizeof(int));
    *pointer = value;
    return (void *) pointer;
}