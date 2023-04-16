#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

typedef struct redBlackTree_t redBlackTree_t;
struct redBlackTree_t {
    void *value;
    redBlackTree_t *parent;
    redBlackTree_t *left;
    redBlackTree_t *right;
};


#endif