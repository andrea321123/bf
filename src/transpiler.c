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

#include "transpiler.h"

#include "common.h"
#include "tree.h"

#include <stdio.h>

#define TAB_SIZE 2

static void addLine(char *line, size_t depth) {
    for (size_t i = 0; i < depth; i++)
        for (size_t j = 0; j < TAB_SIZE; j++)
            putchar(' ');
    
    puts(line);
}

static void transpileRecursive(struct BFTree *tree, size_t depth) {
    while (tree) {
        switch (tree->value) {
        case INC_POINTER_TOKEN:
            addLine("ptr++;", depth);
            break;
        case DEC_POINTER_TOKEN:
            addLine("ptr--;", depth);
            break;
        case INC_VALUE_TOKEN:
            addLine("mem[ptr]++;", depth);
            break;
        case DEC_VALUE_TOKEN:
            addLine("mem[ptr]--;", depth);
            break;
        case PUTCHAR_TOKEN:
            addLine("putchar((uint8_t)mem[ptr]);", depth);
            break;
        case GETCHAR_TOKEN:
            addLine("input = getchar();", depth);
            addLine("if (input != EOF)", depth);
            addLine("mem[ptr] = (uint8_t)input;", depth +1);
                addLine("else", depth);
            addLine("mem[ptr] = 0;", depth);
            break;
        case START_LOOP_TOKEN:
            addLine("while (mem[ptr]) {", depth);
            transpileRecursive(tree->child, depth +1);
            addLine("}", depth);
            break;

        /* Extended Type I instructions */
        case END_PROGRAM_TOKEN:
            addLine("exit(0);", depth);
            break;
        case MOVE_STORAGE_VALUE_TOKEN:
            addLine("storage = mem[ptr];", depth);
            break;
        case MOVE_VALUE_STORAGE_TOKEN:
            addLine("mem[ptr] = storage;", depth);
            break;
        case RIGHT_SHIFT_TOKEN:
            addLine("mem[ptr] >>= 1;", depth);
            break;
        case LEFT_SHIFT_TOKEN:
            addLine("mem[ptr] <<= 1;", depth);
            break;
        case NOT_TOKEN:
            addLine("mem[ptr] = ~(mem[ptr]);", depth);
            break;
        case XOR_TOKEN:
            addLine("mem[ptr] ^= storage;", depth);
            break;
        case AND_TOKEN:
            addLine("mem[ptr] &= storage;", depth);
            break;
        case OR_TOKEN:
            addLine("mem[ptr] |= storage;", depth);
            break;
        default:
            break;
        }
    
        tree = tree->pair;
    }
}

void BFTranspiler_run(struct BFTree *tree, int extended1) {
    addLine("#include <stddef.h>", 0);
    addLine("#include <stdint.h>", 0);
    addLine("#include <stdio.h>", 0);
    addLine("#include <stdlib.h>", 0);
    addLine("", 0);
    addLine("#define MEM_SIZE 30000", 0);
    addLine("", 0);
    addLine("int main(int argc, char *argv[]) {", 0);
    addLine("int input;", 1);
    addLine("size_t ptr = 0;", 1);
    if (extended1)
        addLine("uint8_t storage = 0;", 1);
    addLine("uint8_t mem[MEM_SIZE];", 1);
    addLine("for (size_t i = 0; i < MEM_SIZE; i++)", 1);
    addLine("mem[i] = 0;", 2);
    addLine("", 0);

    transpileRecursive(tree, 1);

    addLine("", 0);
    addLine("return 0;", 1);
    addLine("}", 0);
}
