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
#include "stream.h"
#include "transpiler.h"
#include "tree.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void showUsageAndExit() {
    puts("Usage: bf [FILE]");
    puts("bf is an interpreter for the brainfuck language");
    puts("");
    puts("With no FILE, or when FILE is -, read standard input");
    puts("");
    puts("  -r, --run           run bf source program (default behaviour)");
    puts("  -t, --transpile     transpile bf source to a C source file");
    puts("  -f, --fast          does not check memory underflow or overflow.");
    puts("                        Faster execution, but the program may crash");
    puts("  -m MEMORY           specify the memory array size (default 30000)");
    puts("");
    puts("    -h, --help        display this help and exit");
    puts("    -v, --version     output version information and exit");

    exit(0);
}

static void showVersionAndExit() {
    printf("bf %s\n", VERSION);
    printf("%s\n", REPO_LINK);
    puts("Copyright (C) 2022 bf contributors");

    exit(0);
}

static void readSourceCode(FILE *file, struct BFStream *stream) {
    char c;

    while ((c = fgetc(file)) != EOF)
        BFStream_addChar(stream, c);
}

static void bf(FILE *input, struct BFOptions *options) {
    /* Pipeline:
     * - Reading input
     * - lexical analysis
     * - Parsing
     * - Evaluation / code generation
     */
    struct BFStream *stream = malloc(sizeof(struct BFStream));
    BFStream_init(stream);
    readSourceCode(input, stream);
    if (input != stdin)
        fclose(input);
    
    struct BFList *list = malloc(sizeof(struct BFList));
    BFList_init(list, START_TOKEN, 0, 0, START_OPCODE);
    BFLexer_run(list, stream);
    BFStream_free(stream);

    struct BFTree *tree = malloc(sizeof(struct BFTree));
    BFTree_init(tree, START_TOKEN, START_OPCODE, 1);
    BFParser_run(tree, list->next);
    BFList_free(list);

    if (options->transpile)
        BFTranspiler_run(tree, options);
    else
        BFInterpreter_run(tree, options);
    BFTree_free(tree);
}

int main(int argc, char *argv[]) {
    FILE *input = stdin;

    struct BFOptions options;
    options.memorySize = DEFAULT_MEMORY_SIZE;
    options.transpile = 0;
    options.fast = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            showUsageAndExit();
        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
            showVersionAndExit();
        } else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--transpile") == 0) {
            options.transpile = 1;
        } else if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "--run") == 0) {
            options.transpile = 0;
        } else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--fast") == 0) {
            options.fast = 1;
        } else if (strcmp(argv[i], "-m") == 0) {
            i++;
            if (i == argc) {
                fprintf(stderr, "error: memory array size not specified\n");
                exit(1);
            }
            if (strlen(argv[i]) > 10) {
                fprintf(stderr, "error: memory size not valid\n");
                exit(1);
            }
            options.memorySize = strtol(argv[i], NULL, 10);
            if (!options.memorySize || options.memorySize <= 0) {
                fprintf(stderr, "error: memory size not valid\n");
                exit(1);
            }
        } else if (strcmp(argv[i], "-") != 0) {
            input = fopen(argv[i], "rb");
            if (!input) {
                fprintf(stderr, "error: file %s not found\n", argv[i]);
                exit(1);
            }
        }
    }

    bf(input, &options);

    return 0;
}
