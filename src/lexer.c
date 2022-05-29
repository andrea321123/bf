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

#include "lexer.h"

#include "common.h"
#include "list.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static enum Token opcodeToToken(char opcode) {
    switch (opcode) {
    case INC_POINTER_OPCODE:
        return INC_POINTER_TOKEN;
    case DEC_POINTER_OPCODE:
        return DEC_POINTER_TOKEN;
    case INC_VALUE_OPCODE:
        return INC_VALUE_TOKEN;
    case DEC_VALUE_OPCODE:
        return DEC_VALUE_TOKEN;
    case PUTCHAR_OPCODE:
        return PUTCHAR_TOKEN;
    case GETCHAR_OPCODE:
        return GETCHAR_TOKEN;
    case START_LOOP_OPCODE:
        return START_LOOP_TOKEN;
    case END_LOOP_OPCODE:
        return END_LOOP_TOKEN;
    default:
        return COMMENT_TOKEN;
    }
}

static void checkValidProgram(struct BFList *list) {
    if (list->value == END_TOKEN)
        return;

    int bracketCount = 0;

    struct BFList *previous = list;
    list = list->next;

    while (bracketCount >= 0 && previous->value != END_TOKEN) {
        if (list->value == START_LOOP_TOKEN)
            bracketCount++;
        else if (list->value == END_LOOP_TOKEN)
            bracketCount--;

        previous = list;
        list = list->next;
    }

    if (bracketCount > 0) {
        fprintf(stderr, "error: ']' instruction missing\n"); 
        exit(1);
    }
    if (bracketCount < 0) {
        fprintf(
            stderr,
            "error: ']' instruction not expected (at %zu, %zu)\n",
            previous->line,
            previous->column
        );
        exit(1);
    }
}

void BFLexer_run(struct BFList *head, char *sourceCode) {
    size_t line = 1;
    size_t column = 1;
    size_t sourceCodeSize = strlen(sourceCode);
    struct BFList *lastNode = head;

    for (size_t i = 0; i < sourceCodeSize; i++) {
        enum Token token = opcodeToToken(sourceCode[i]);
        if (token != COMMENT_TOKEN) {
            struct BFList *newNode = malloc(sizeof(struct BFList));
            BFList_init(newNode, token, line, column, sourceCode[i]);
            BFList_addNext(lastNode, newNode); 
            lastNode = newNode;
        }

        if (sourceCode[i] == '\n') {
            column = 1;
            line++;
        } else {
            column++;
        }
    }

    struct BFList *eofNode = malloc(sizeof(struct BFList));
    BFList_init(eofNode, END_TOKEN, line, column, END_OPCODE);
    BFList_addNext(lastNode, eofNode);

    checkValidProgram(head);
}
