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
#include "stream.h"

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

/* Perform optimizations on generated list.
 * The only optimization actually used is to join together multiple
 * instructions of the same type into a single list element
 * (the number of instructions are specified by the [count] field).
 */
static void optimize(struct BFList *list) {
    while (list->value != END_TOKEN) {
        if (list->value == INC_POINTER_TOKEN ||
            list->value == DEC_POINTER_TOKEN ||
            list->value == INC_VALUE_TOKEN ||
            list->value == DEC_VALUE_TOKEN
        ) {
            enum Token token = list->value;
            struct BFList *tmp = list->next;
            while (tmp->value == token && list->count < UINT8_MAX) {
                /* Free [tmp] node */
                list->next = tmp->next;
                tmp->next = NULL;
                BFList_free(tmp);

                /* Update [tmp] node and list count */
                tmp = list->next;
                list->count++;
            }
        }

        list = list->next;
    }
}

void BFLexer_run(struct BFList *head, struct BFStream *stream) {
    size_t line = 1;
    size_t column = 1;
    struct BFList *lastNode = head;

    char c = BFStream_nextChar(stream);
    while (c != EOF) {
        enum Token token = opcodeToToken(c);
        if (token != COMMENT_TOKEN) {
            struct BFList *newNode = malloc(sizeof(struct BFList));
            BFList_init(newNode, token, line, column, c);
            BFList_addNext(lastNode, newNode); 
            lastNode = newNode;
        }

        if (c == '\n') {
            column = 1;
            line++;
        } else {
            column++;
        }

        c = BFStream_nextChar(stream);
    }

    struct BFList *eofNode = malloc(sizeof(struct BFList));
    BFList_init(eofNode, END_TOKEN, line, column, END_OPCODE);
    BFList_addNext(lastNode, eofNode);

    checkValidProgram(head);
    optimize(head);
}
