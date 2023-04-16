#include "binaryTree.h"

static int (*CmpFunction) (void *value1, void *value2) = &CmpNodeValueInt;

int CmpNodeValueInt(void *value1, void *value2) {
    int v1 = *((int *) value1);
    int v2 = *((int *) value2);

    if (v1 < v2)
        return -1;
    if (v1 == v2)
        return 0;
    return 1;
}

binaryTree_t *BTCreateNode(void *nodeValue) {
    binaryTree_t *node = (binaryTree_t *) malloc(sizeof(binaryTree_t));
    if (node == NULL)
        return NULL;

    node->value = nodeValue;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;

    return node;
}

int BTIsLeaf(binaryTree_t *tree) {
    if (tree == NULL)
        return 0;
    if (tree->left == NULL || tree->right == NULL)
        return 0;
    if (tree->left->value == NULL && tree->right->value == NULL)
        return 1;
    return 0;
}

int BTDepth(binaryTree_t *tree) {
    int depth = 0;
    while (tree != NULL) {
        depth++;
        tree = tree->parent;
    }

    return depth;
}

int BTHeight(binaryTree_t *tree) {
    if (tree == NULL)
        return 0;

    int leftHeight = BTHeight(tree->left);
    int rightHeight = BTHeight(tree->right);

    if (leftHeight > rightHeight)
        return leftHeight + 1;
    return rightHeight + 1;
}

void BTClear(binaryTree_t *tree) {
    if (tree == NULL)
        return;
    
    if (tree->value != NULL)
        free(tree->value);
    BTClear(tree->left);
    BTClear(tree->right);
    free(tree);
}

void *BTInsert(binaryTree_t *tree, void *value) {
    binaryTree_t *newNode = BTCreateNode(value);

    if (tree == NULL) {
        newNode->left = BTCreateNode(NULL);
        newNode->left->parent = newNode;
        newNode->right = BTCreateNode(NULL);
        newNode->right->parent = newNode;

        return newNode;
    }
    
    binaryTree_t *cmpNode = tree;
    int cmpResult;

    while(cmpNode->value != NULL) {
        cmpResult = (*CmpFunction) (value, cmpNode->value);
        if (cmpResult == -1)
            cmpNode = cmpNode->left;
        else if(cmpResult == 1)
            cmpNode = cmpNode->right;
        else if (cmpResult == 0)
            break;
    }
    
    newNode->parent = cmpNode->parent;
    if (newNode->parent != NULL) {
        if ((*CmpFunction)(newNode->value, newNode->parent->value) == -1)
            newNode->parent->left = newNode;
        else
            newNode->parent->right = newNode;
    }

    newNode->right = cmpNode;
    newNode->left = cmpNode->left;
    cmpNode->left = BTCreateNode(NULL);
    cmpNode->left->parent = cmpNode;
    cmpNode->parent = newNode;

    if (newNode->left == NULL) {
        newNode->left = BTCreateNode(NULL);
        newNode->left->parent = newNode;
    }
    else {
        newNode->left->parent = newNode;
    }
    if (newNode->right == NULL) {
        newNode->right = BTCreateNode(NULL);
        newNode->right->parent = newNode;
    }

    return tree;
}

void BTRemove(binaryTree_t *tree, void *value) {

}

int BTFind(binaryTree_t *tree, void *value) {
    if (tree == NULL)
        return 0;
    
    binaryTree_t *tempNode = tree;
    int cmpResult;
    while (tempNode->value != NULL) {
        cmpResult = (*CmpFunction) (value, tempNode->value);
        if (cmpResult == -1)
            tempNode = tempNode->left;
        else if (cmpResult == 0)
            return 1; // Value found
        else
            tempNode = tempNode->right;
    }

    return 0;
}

void BTListPreOrder(binaryTree_t *tree) {
    if (tree == NULL)
        return;
    if (tree->value == NULL)
        return;

    printf("%i ", *((int *) tree->value));
    BTListPreOrder(tree->left);
    BTListPreOrder(tree->right);
}

void BTListInOrder(binaryTree_t *tree) {
    if (tree == NULL)
        return;
    if (tree->left == NULL || tree->right == NULL)
        return;

    if (tree->left->value == NULL && tree->right->value == NULL)
        printf("%i ", *((int *) tree->value));
    else {
        BTListInOrder(tree->left);
        printf("%i ", *((int *) tree->value));
        BTListInOrder(tree->right);
    }
}

void BTListPostOrder(binaryTree_t *tree) {
    if (tree == NULL)
        return;
    if (tree->value == NULL)
        return;

    BTListPostOrder(tree->left);
    BTListPostOrder(tree->right);

    printf("%i ", *((int *) tree->value));
}