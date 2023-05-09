#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct avl_node_t;
struct avl_node_t {
    void *value;
    int height;
    avl_node_t *left;
    avl_node_t *right;
};

typedef struct avl_tree_t;
struct avl_tree_t {
    avl_node_t *root;
    int (*cmp_function)(avl_node_t *node1, avl_node_t *node2);
};

avl_node_t *avl_tree_alloc(void *value) {
    avl_node_t *avl = (avl_node_t *) malloc(sizeof(avl_node_t));
    if (!avl) {
        perror("Error while allocating avl tree");
        exit(-1);
    }

    avl->value = value;
    avl->height = 0;
    avl->left = NULL;
    avl->right = NULL;

    return avl;
}

int avl_get_node_heigth(avl_node_t *node) {
    if (!node)
        return -1;
    return node->height;
}

int avl_balance_factor(avl_node_t *node) {
    return abs(avl_get_node_heigth(node->left) - avl_get_node_heigth(node->right));
}

// Left rotation - RR Rotation
//   A               B
//    \             / \
//     B      =>   A   C
//      \
//       C
avl_node_t *avl_left_rotation(avl_node_t *node) {
    avl_node_t *pivot = node->right;
    avl_node_t *temp = pivot->left;
    pivot->left = node;
    node->right = temp;

    return pivot;
}

// Right rotation - LL Rotation
//         A             B
//        /             / \
//       B      =>     C   A
//      /
//     C
avl_node_t *avl_right_rotation(avl_node_t *node) {
    avl_node_t *pivot = node->left;
    avl_node_t *temp = pivot->right;
    pivot->right = node;
    node->left = temp;

    return pivot;
}

// Double left rotation - RL Rotation
//     A               C
//      \             / \
//       B    =>     A   B
//      /
//     C
avl_node_t *avl_double_left_rotation(avl_node_t *node) {
    node->right = avl_right_rotation(node->right);
    return avl_left_rotation(node);
}

// Double right rotation - LR Rotation
//      A             B
//     /             / \
//    B      =>     C   A
//     \
//      C
avl_node_t *avl_double_right_rotation(avl_node_t *node) {
    node->left = avl_left_rotation(node->left);
    return avl_right_rotation(node);
}

int max(int x, int y) {
    if (x > y)
        return x;
    return y;
}

int min(int x, int y) {
    if (x < y)
        return x;
    return y;
}

void avl_clear(avl_node_t *avl) {
    
}

#endif