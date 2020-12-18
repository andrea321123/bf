// lexer.c
// Version 2.0

#include <stddef.h>

#include "lexer.h"

// private functions declaration
Token charToToken(char c);

List *doLexing(char *sourceCode) {
    List *head = initList();
    List *tail = head;

    char *p = sourceCode;
    uint64_t lineCounter = 1;
    
    // we read each character
    while (*p != '\0') {
        // if it is a '\n' increment counter and continue
        if (*p == '\n') {
            lineCounter++;
            p++;
            continue;
        }

        Token token = charToToken(*p);

        // if it is an instruction, add to the list
        if (token != COMMENT) {
            tail = addNode(tail, token, lineCounter);
        }

        p++;
    }

    // remove the first value from the list because not used
    List *ret = head->next;
    head->next = NULL;
    freeList(head);

    return ret;
}

Token charToToken(char c) {
    Token token = COMMENT;

    // check each meaningful character
    if (c == '>') {
        token = INC_POINTER;
    }
    else if (c == '<') {
        token = DEC_POINTER;
    }
    else if (c == '+') {
        token = INC_VALUE;
    }
    else if (c == '-') {
        token = DEC_VALUE;
    }
    else if (c == ',') {
        token = GETCHAR;
    }
    else if (c == '.') {
        token = PUTCHAR;
    }
    else if (c == '[') {
        token = START_LOOP;
    }
    else if (c == ']') {
        token = END_LOOP;
    }

    return token;
}