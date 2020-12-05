// list.h
// Version 1.0

#ifndef LIST_H
#define LIST_H

#include "token.h"

// implement a Token linked list
struct TokenList {
    Token value;
    struct TokenList *next;
};

typedef struct TokenList List;

// initialize a List pointer 
List *initList();

// free a list starting from the parameter pointer
void freeList(List *node);

// add a new node to the parameter list
List *addNode(List *node, Token value);

#endif