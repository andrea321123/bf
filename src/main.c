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

#include "common.h"
#include "interpreter.h"
#include "lexer.h"
#include "list.h"
#include "parser.h"
#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void showUsageAndExit() {
    puts("Usage: bf [FILE]");
    puts("bf is an interpreter for the Brainfuck language");
    puts("");
    puts("With no FILE, or when FILE is -, read standard input");

    exit(0);
}

static void showVersionAndExit() {
    puts("bf 1.0");
    puts("Copyright (C) 2022 bf contributors");

    exit(0);
}

static void readSourceCode(FILE *stream, char **str) {
    fseek(stream, 0, SEEK_END);
    size_t size = (size_t)ftell(stream);
    fseek(stream, 0, SEEK_SET);

    if (*str)
        *str = realloc(*str, sizeof(char) * (size +1));
    else
        *str = malloc(sizeof(char) * (size +1));
    fread(*str, size, 1, stream);
}

static void executeSourceFile(FILE *input) {
    /* Pipeline:
     * - Reading input
     * - lexical analysis
     * - Parsing
     * - Evaluation
     */
    char *sourceCode = NULL;
    readSourceCode(input, &sourceCode);
    if (input != stdin)
        fclose(input);
    
    struct BFList *list = malloc(sizeof(struct BFList));
    BFList_init(list, START_TOKEN, 0, 0, START_OPCODE);
    BFLexer_run(list, sourceCode);
    free(sourceCode);

    struct BFTree *tree = malloc(sizeof(struct BFTree));
    BFTree_init(tree, START_TOKEN, START_OPCODE);
    BFParser_run(tree, list->next);
    BFList_free(list);

    BFInterpreter_run(tree);
    BFTree_free(tree);
}

int main(int argc, char *argv[]) {
    FILE *input = stdin;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
            showUsageAndExit();
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0)
            showVersionAndExit();
        
        if (strcmp(argv[i], "-") != 0) {
            input = fopen(argv[i], "rb");
            if (!input) {
                fprintf(stderr, "error: file %s not found\n", argv[i]);
                exit(1);
            }
        }
    }

    if (argc == 1)
        showUsageAndExit();

    executeSourceFile(input);

    return 0;
}
