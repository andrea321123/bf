// tree.c
// Version 1.1

#include <stddef.h>
#include <stdlib.h>

#include "tree.h"

Tree *initTree() {
    Tree *head = malloc(sizeof(Tree));

    head->nChildren = 0;
    head->children = NULL;
}

void freeTree(Tree *node) {
    // recursive action: we free all the children
    for (uint64_t i = 0; i < node->nChildren; i++) {
        freeTree(node->children[i]);
    }

    free(node);
}

Tree *addChild(Tree *node, Token value) {
    node->nChildren++;
    
    // create the new node
    Tree *newNode;
    newNode = initTree();
    newNode->value = value;

    // add newNode to the tree children
    node->children = realloc(node->children, sizeof(Tree *) * node->nChildren);
    node->children[node->nChildren -1] = newNode;

    return newNode;
}