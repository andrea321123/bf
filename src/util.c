// util.c
// Version 1.0

#include "util.h"

// private functions declaration
char *tokenToInfo(Token token);

void printList(List *list) {
    while (list != NULL) {
        printf("%s\n", tokenToInfo(list->value));
        list = list->next;
    }
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