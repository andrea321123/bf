// main.c
// Version 1.1

#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

// private function declarations
char *readSourceCode(char *path);

int main(int argc, char *argv[]) {
    // argv[1] must be path to source code
    if (argc <2) {
        printf("ERROR: Specify source code path.\n");
        exit(4);
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

    printf("OPREMENERE");
    int sas = 0;
    scanf("%d", &sas);
    return 0;
}

char *readSourceCode(char *path) {
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        printf("ERROR: Could not open file\n");
        exit (5);
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
            printf("%lu\n", allocatedSize);
        }

        sourceCode[offset++] = character;
    }

    sourceCode[offset] = '\0';         // add final character
    return sourceCode;
}