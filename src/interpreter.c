/*
 * bf
 * Copyright (C) 2022, bf contributors
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "interpreter.h"

#include "common.h"
#include "tree.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Interpreter {
    uint8_t memory[MEMORY_SIZE];
    size_t ptr;
};

static void Interpreter_init(struct Interpreter *self) {
    for (size_t i = 0; i < MEMORY_SIZE; i++)
        self->memory[i] = 0;
    
    self->ptr = 0;
}

static void Interpreter_free(struct Interpreter *self) {
    free(self);
}

static void outOfBounds() {
    fprintf(stderr, "error: memory pointer out of bounds\n");
    exit(1);
}

static void runNonLoopInstruction(
    struct Interpreter *interpreter,
    enum Token token
) {
    int input;

    switch (token) {
    case INC_POINTER_TOKEN:
        interpreter->ptr++;
        if (interpreter->ptr >= MEMORY_SIZE)
            outOfBounds();
        break;
    case DEC_POINTER_TOKEN:
        if (interpreter->ptr == 0)
            outOfBounds();
        else
            interpreter->ptr--;
        break;
    case INC_VALUE_TOKEN:
        interpreter->memory[interpreter->ptr] = 
            (interpreter->memory[interpreter->ptr] +1) %256;
        break;
    case DEC_VALUE_TOKEN:
        if (interpreter->memory[interpreter->ptr] == 0)
            interpreter->memory[interpreter->ptr] = 255;
        else
            interpreter->memory[interpreter->ptr]--;
        break;
    case PUTCHAR_TOKEN:
        putchar(interpreter->memory[interpreter->ptr]);
        break;
    case GETCHAR_TOKEN:
        input = getchar();

        /* EOF writes 0 into memory */
        if (input != EOF)
            interpreter->memory[interpreter->ptr] = (uint8_t )input;
        else
            interpreter->memory[interpreter->ptr] = 0;
        break;
    default:
        break;
    }
}

static void runRecursive(
    struct Interpreter *interpreter,
    struct BFTree *tree
) {
    while (tree && tree->value != END_TOKEN) {
        if (tree->value != START_LOOP_TOKEN)
            runNonLoopInstruction(interpreter, tree->value);
        else
            while (interpreter->memory[interpreter->ptr] != 0)
                runRecursive(interpreter, tree->child->pair);

        tree = tree->pair;        
    }
}

void BFInterpreter_run(struct BFTree *tree) {
    struct Interpreter *interpreter = malloc(sizeof(struct Interpreter));
    Interpreter_init(interpreter);

    runRecursive(interpreter, tree);

    Interpreter_free(interpreter);
}
