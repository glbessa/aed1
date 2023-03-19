#ifndef STDLIB_H
#include <stdlib.h>
#define STDLIB_H
#endif

typedef struct binaryTreeNode_t binaryTreeNode_t;
struct binaryTreeNode_t {
    void *value;
    binaryTreeNode_t *left;
    binaryTreeNode_t *right;
};

typedef struct binaryTree_t binaryTree_t;
struct binaryTree_t {
    unsigned int depth;
    unsigned int heigth;
    binaryTreeNode_t *root;
};

typedef struct binaryNodeWithParent_t binaryNodeWithParent_t;
struct binaryNodeWithParent_t {
    binaryNodeWithParent_t *parent;
    void *value;
    binaryNodeWithParent_t *left;
    binaryNodeWithParent_t *right;
};

