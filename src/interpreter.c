// interpreter.c
// Version 1.1

#include <stdlib.h>
#include <stdio.h>

#include "interpreter.h"

// private function declarations
void executeToken(Interpreter *interpreter, Token token);

Interpreter *initInterpreter() {
    Interpreter *interpreter = malloc(sizeof(Interpreter));

    // init memory block
    for (uint64_t i = 0; i < MEMORY_SIZE; i++) {
        interpreter->memory[i] = 0;
    }

    interpreter->pointer = 0;
    return interpreter;
}

void freeInterpreter(Interpreter *interpreter) {
    free(interpreter);
}

void run(Interpreter *interpreter, Tree *tree) {
    // run normal instruction (non-loop)
    if (tree->value != START_LOOP && tree->value != COMMENT) {
        executeToken(interpreter, tree->value);
    }
    else if (tree->value == COMMENT) {      // tree head node
        for (uint64_t i = 0; i < tree->nChildren; i++) {
            run(interpreter, tree->children[i]);
        }
    }
    else {      // loop block
        while (interpreter->memory[interpreter->pointer] != 0) {
            for (uint64_t i = 0; i < tree->nChildren; i++) {
                run(interpreter, tree->children[i]);
            }
        }
    }
}

void executeToken(Interpreter *interpreter, Token token) {
    if (token == INC_POINTER) {
        interpreter->pointer++;
    }
    else if (token == DEC_POINTER) {
        interpreter->pointer--;
    }
    else if (token == INC_VALUE) {
        interpreter->memory[interpreter->pointer]++;
    }
    else if (token == DEC_VALUE) {
        interpreter->memory[interpreter->pointer]--;
    }
    else if (token == GETCHAR) {
        interpreter->memory[interpreter->pointer] = getchar();
    }
    else if (token == PUTCHAR) {
        putchar(interpreter->memory[interpreter->pointer]);
    }
}