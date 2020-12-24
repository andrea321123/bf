// parser.c
// Version 2.2

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "parser.h"

// private functions declaration
List *doParsingRecursive(Tree *tree, List *list);

Tree *doParsing(List *list) {
    Tree *tree = initTree();
    tree->value = COMMENT;

    // nested instruction will be handled recursively
    while (list != NULL) {
        Token token = list->value;
        if (token == END_LOOP) {
            printf("bf: error at line %lu: '[' missing\n", list->line);
            exit(1);
        }
        if (token != START_LOOP) {
            addChild(tree, token, list->line);
        }
        else {      // it is a loop
            // we jump to the end of the [] block
            Tree *loopChild = addChild(tree, token, list->line);

            uint64_t line = list->line;
            list = doParsingRecursive(loopChild, list->next);
            if (list == NULL) {         // missing ']'
                printf("bf: error at line %lu: ']' missing\n", line);
                exit(2);
            }
        }

        list = list->next;      // visit next node
    }

    return tree;
}

// we add to the tree each block of instruction ([] are considered a
// single block and then it is parsed recursively
// Should return the node with value ']'
List *doParsingRecursive(Tree *tree, List *list) {
    // if last instruction was '['
    if (list == NULL) {
        return NULL;
    }

    while (list->value != END_LOOP) {
        if (list->value != START_LOOP) {
            addChild(tree, list->value, list->line);
        }
        else {      // it is a loop
            Token token = list->value;
            // we jump to the end of the [] block
            Tree *loopChild = addChild(tree, token, list->line);
            list = doParsingRecursive(loopChild, list->next);
        }

        uint64_t line = list->line;
        list = list->next;

        // error handling: reached end of the list (shouldn't happen because
        // we are still nested in at least one loop)
        if (list == NULL) {
            printf("bf: error at line %lu: ']' missing\n", line);
            exit(2);
        }
    }

    return list;
}