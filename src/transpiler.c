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

#include <stddef.h>
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
            addLine("ptr = (ptr +1) % MEM_SIZE;", depth);
            break;
        case DEC_POINTER_TOKEN:
            addLine("ptr = ptr == 0 ? MEM_SIZE - 1 : ptr - 1;", depth);
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
        default:
            break;
        }
    
        tree = tree->pair;
    }
}

void BFTranspiler_run(struct BFTree *tree, size_t memorySize) {
    /* Headers and defines */
    addLine("#include <stddef.h>", 0);
    addLine("#include <stdint.h>", 0);
    addLine("#include <stdio.h>", 0);
    addLine("#include <stdlib.h>", 0);
    addLine("", 0);
    printf("#define MEM_SIZE %zu\n", memorySize);
    addLine("", 0);

    /* Main function */
    addLine("int main(int argc, char *argv[]) {", 0);
    addLine("int input;", 1);
    addLine("size_t ptr = 0;", 1);
    addLine("uint8_t *mem = calloc(MEM_SIZE, sizeof(uint8_t));", 1);
    addLine("", 0);

    transpileRecursive(tree, 1);

    addLine("", 0);
    addLine("return 0;", 1);
    addLine("}", 0);
}
