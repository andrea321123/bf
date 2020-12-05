// parser.c
// Version 1.0

#include <stddef.h>
#include <stdlib.h>

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
            // should be handled as error
            exit(0);
        }
        if (token != START_LOOP) {
            addChild(tree, token);
        }
        else {      // it is a loop
            // we jump to the end of the [] block
            Tree *loopChild = addChild(tree, token);
            list = doParsingRecursive(loopChild, list->next);
        }

        list = list->next;      // visit next node
    }

    return tree;
}

// we add to the tree each block of instruction ([] are considered a
// single block and then it is parsed recursively
// Should return the node with value ']'
List *doParsingRecursive(Tree *tree, List *list) {
    if (list == NULL) {
        // should be handled as error
        exit(1);
    }
    while (list->value != END_LOOP) {
        if (list->value != START_LOOP) {
            addChild(tree, list->value);
        }
        else {      // it is a loop
            Token token = list->value;
            // we jump to the end of the [] block
            Tree *loopChild = addChild(tree, token);
            list = doParsingRecursive(loopChild, list->next);
        }

        list = list->next;

        // error handling: reached end of the list (shouldn't happen because
        // we are still nested in at least one loop)
        if (list == NULL) {
            exit(2);
        }
    }

    return list;
}