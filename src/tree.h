// tree.h
// Version 2.0

#ifndef TREE_H
#define TREE_H

#include <stdint.h>

#include "token.h"

typedef struct TokenTree Tree;

// node of the Abstract Syntax tree
struct TokenTree {
    Token value;
    uint64_t line;
    struct TokenTree **children;
    uint64_t nChildren;
};

// initialize a Tree pointer 
Tree *initTree();

// free a tree starting from the parameter pointer
void freeTree(Tree *node);

// add a new node to the parameter tree
Tree *addChild(Tree *node, Token value, uint64_t line);

#endif