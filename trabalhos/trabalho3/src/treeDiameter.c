#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *BTCreateNode(int val);
int BTHeight(struct TreeNode *root);
int diameterOfBinaryTree(struct TreeNode *root);

int main() {
    struct TreeNode *tree1 = BTCreateNode(5);
    tree1->left = BTCreateNode(3);
    tree1->right = BTCreateNode(7);
    tree1->left->left = BTCreateNode(2);
    tree1->left->right = BTCreateNode(4);

    struct TreeNode *tree2 = BTCreateNode(9);
    tree2->left = BTCreateNode(2);
    tree2->right = BTCreateNode(4);
    tree2->right->left = BTCreateNode(5);
    tree2->right->left->left = BTCreateNode(14);
    tree2->right->left->left->left = BTCreateNode(12);
    tree2->right->right = BTCreateNode(7);
    tree2->right->right->right = BTCreateNode(3);
    tree2->right->right->right->right = BTCreateNode(8);

    struct TreeNode *tree3 = BTCreateNode(3);
    tree3->left = BTCreateNode(1);

    printf("Diâmetro árvore 1: %i\n", diameterOfBinaryTree(tree1));
    printf("Diâmetro árvore 2: %i\n", diameterOfBinaryTree(tree2));
    printf("Diâmetro árvore 3: %i\n", diameterOfBinaryTree(tree3));

    return 0;
}

// ---------------------------------------
// struct TreeNode *BTCreateNode(int val)
// 
//      Faz a alocação de um nó na memória
//      e inicializa seus valores.
// ---------------------------------------
struct TreeNode *BTCreateNode(int val) {
    struct TreeNode *node = (struct TreeNode *) malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;

    return node;
}

// ------------------------------------
// BTHeight(struct TreeNode *root)
//
//     Retorna a altura do nó passado
//     como root
// ------------------------------------
int BTHeight(struct TreeNode *root) {
    if (root == NULL)
        return 0;

    int leftHeight = BTHeight(root->left);
    int rightHeight = BTHeight(root->right);

    if (leftHeight > rightHeight)
        return leftHeight + 1;
    return rightHeight + 1;
}

// -----------------------------------------------
// int diameterOfBinaryTree(struct TreeNode *root)
//
//      Retorna o diâmetro de uma árvore binária.
// -----------------------------------------------
int diameterOfBinaryTree(struct TreeNode *root) {
    if (root == NULL)
        return 0;

    int maxDiameter, leftDiameter, rightDiameter = 0;
    maxDiameter = BTHeight(root->left) + BTHeight(root->right);
    leftDiameter = diameterOfBinaryTree(root->left);
    if (maxDiameter < leftDiameter)
        maxDiameter = leftDiameter;

    rightDiameter = diameterOfBinaryTree(root->right);
    if (maxDiameter < rightDiameter)
        maxDiameter = rightDiameter;

    return maxDiameter;
}