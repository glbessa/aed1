#ifndef STDLIB_H
#include <stdlib.h>
#define STDLIB_H 1
#endif

#ifndef LINKED_LIST_H
#include "linkedList.h"
#define LINKED_LIST_H 1
#endif

struct treeNode_t {
    void *value;
    linkedList *childrenNodes;
};