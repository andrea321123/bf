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

#ifndef TREE_H
#define TREE_H

#include "common.h"

#include <stdint.h>

/*
 * Data structure used for easy manipulation and interpretation of BF programs.
 * It is a binary tree, where the "left child" stores the first instruction of
 * a "loop" instruction (so only '[' instructions will have a left child).
 * The "right child" stores the next instruction to execute. 
 * 
 * As an example, the program '++++[--]+' will be represented as:
 * 
 * -----    -----    -----    -----    -----    -----
 * | + | -> | + | -> | + | -> | + | -> | [ | -> | + |
 * -----    -----    -----    -----    -----    -----
 *                                       |
 *                                     -----    -----
 *                                     | - | -> | - |
 *                                     -----    ----- 
 */
struct BFTree {
    char opcode;
    enum Token value;
    uint8_t count;

    struct BFTree *child;
    struct BFTree *pair;
};

void BFTree_init(
    struct BFTree *self,
    enum Token token,
    char opcode,
    uint8_t count
);

void BFTree_free(struct BFTree *self);

/* Add child node to the [self] node. */
void BFTree_addChild(struct BFTree *self, struct BFTree *child);

/* Add pair node to the [self] node. */
void BFTree_addPair(struct BFTree *self, struct BFTree *pair);

void BFTree_info(struct BFTree *self);

#endif
