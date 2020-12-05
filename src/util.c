// util.c
// Version 1.1

#include "util.h"

// private functions declaration
char *tokenToInfo(Token token);
void printTreeRecursive(Tree *tree, uint64_t depth);

void printList(List *list) {
    while (list != NULL) {
        printf("%s\n", tokenToInfo(list->value));
        list = list->next;
    }
}

void printTree(Tree *tree) {
    printTreeRecursive(tree, 0);
}

// return a string containing information about the token
char *tokenToInfo(Token token) {
    if (token == INC_POINTER) {
        return "> : increment the data pointer";
    }
    if (token == DEC_POINTER) {
        return "< : decrement the data pointer";
    }
    if (token == INC_VALUE) {
        return "+ : increment the byte at the data pointer";
    }
    if (token == DEC_VALUE) {
        return "- : decrement the byte at the data pointer";
    }
    if (token == GETCHAR) {
        return ", : store an input value in the byte at the data pointer.";
    }
    if (token == PUTCHAR) {
        return ". : output the byte at the data pointer.";
    }
    if (token == START_LOOP) {
        return "[ : start of loop";
    }
    if (token == END_LOOP) {
        return "] : end of loop";
    }

    return "Comment";
}

void printTreeRecursive(Tree *tree, uint64_t depth) {
    // print "  " to represent the depth
    for (uint64_t i = 0; i < depth; i++) {
        printf("  ");
    }

    // print tree data
    printf("%s\n", tokenToInfo(tree->value));

    // print children data
    for (uint64_t i = 0; i < tree->nChildren; i++) {
        printTreeRecursive(tree->children[i], depth +1);
    }
}