// main.c
// Version 2.0

#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

// private function declarations
char *readSourceCode(char *path);

int main(int argc, char *argv[]) {
    // argv[1] must be path to source code
    if (argc < 2) {
        printf("bf: error: Specify source code path.\n");
        exit(3);
    }

    char *sourceCode = readSourceCode(argv[1]);

    // pipeline:
    // - lexing
    // - parsing
    // - evaluation
    List *list = doLexing(sourceCode);
    
    Tree *tree = doParsing(list);

    Interpreter *interpreter = initInterpreter();
    run(interpreter, tree);

    // free all allocated memory
    free(sourceCode);
    freeList(list);
    freeTree(tree);
    freeInterpreter(interpreter);

    return 0;
}

char *readSourceCode(char *path) {
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        printf("bf: error: Could not open file\n");
        exit (4);
    }

    char *sourceCode = malloc(100);
    char character;
    uint64_t allocatedSize = 100;
    uint64_t offset = 0;

    // read file char by char
    while ((character = fgetc(file)) != EOF) {
        // check if allocated space is enough
        if (offset >= allocatedSize) {
            allocatedSize *=2;
            sourceCode = realloc(sourceCode, allocatedSize);
        }

        sourceCode[offset++] = character;
    }

    sourceCode[offset] = '\0';         // add final character
    return sourceCode;
}