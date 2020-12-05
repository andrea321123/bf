// list.c
// Version 1.0

#include <stddef.h>
#include <stdlib.h>

#include "list.h"

List *initList() {
    List *head = malloc(sizeof(List));
    head->next = NULL;

    return head;
}

void freeList(List *node) {
    // recursive action: we free all the next pointers
    if (node->next != NULL) {
        freeList(node->next);
    }

    free(node);
}

List *addNode(List *node, Token value) {
    // create the new node
    List *newNode;
    newNode = initList();
    newNode->value = value;

    node->next = newNode;   // connect the new node to the list
    return newNode;
}