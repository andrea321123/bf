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

#ifndef LIST_H
#define LIST_H

#include "common.h"

#include <stddef.h>

/* Linked list implementation used to store each
 * bf instruction into a sequential data structure.
 * Each BFList element act as a node of the linked list.
 */
struct BFList {
    size_t line;
    size_t column;
    char opcode;

    enum Token value;
    struct BFList *next;
};

void BFList_init(
    struct BFList *self,
    enum Token token,
    size_t line,
    size_t column,
    char opcode
);

void BFList_free(struct BFList *self);

/* Add [next] node to the [self] node. */
void BFList_addNext(struct BFList *self, struct BFList *next);

void BFList_info(struct BFList *self);

#endif
