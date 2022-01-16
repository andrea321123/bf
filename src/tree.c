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

#include "tree.h"

#include "common.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static void printTreeRecursive(struct BFTree *tree, size_t depth) {
    for (size_t i = 0; i < depth; i++)
        printf("  ");
    
    /* We first print [tree] data, then children data (at higher depth),
     * then pairs data.
     */
    printf("%c\n", tree->opcode);

    if (tree->child)
        printTreeRecursive(tree->child, depth +1);
    if (tree->pair)
        printTreeRecursive(tree->pair, depth);
}

void BFTree_init(struct BFTree *self, enum Token token, char opcode) {
    self->opcode = opcode;
    self->value = token;
    self->pair = NULL;
    self->child = NULL;
}

void BFTree_free(struct BFTree *self) {
    if (self->child)
        BFTree_free(self->child);
    if (self->pair)
        BFTree_free(self->pair);
    
    free(self);
}

void BFTree_addChild(struct BFTree *self, struct BFTree *child) {
    self->child = child;
}

void BFTree_addPair(struct BFTree *self, struct BFTree *pair) {
    self->pair = pair;
}

void BFTree_info(struct BFTree *self) {
    printTreeRecursive(self, 0);
}
