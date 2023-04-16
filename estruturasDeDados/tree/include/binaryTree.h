#ifndef BINARY_TREE_T
#define BINARY_TREE_T

#include <stdio.h>
#include <stdlib.h>

typedef struct binaryTree_t binaryTree_t;
struct binaryTree_t {
    void *value;
    binaryTree_t *parent;
    binaryTree_t *left;
    binaryTree_t *right;
};

int CmpNodeValueInt(void *value1, void *value2);

binaryTree_t *BTCreateNode(void *nodeValue);
int BTHeight(binaryTree_t *tree);
int BTIsLeaf(binaryTree_t *tree);
void BTClear(binaryTree_t *tree);
void *BTInsert(binaryTree_t *tree, void *value);
int BTFind(binaryTree_t *tree, void *value);
void BTListPreOrder(binaryTree_t *tree);
void BTListInOrder(binaryTree_t *tree);
void BTListPostOrder(binaryTree_t *tree);

#endif