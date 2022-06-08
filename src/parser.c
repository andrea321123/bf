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

#include "parser.h"

#include "common.h"
#include "list.h"
#include "tree.h"

#include <stdlib.h>

static struct BFList *parseRecursive(
    struct BFTree *tree,
    struct BFList *list,
    enum Token stopToken
) {
    struct BFTree *lastPair = tree;

    while (list->value != stopToken) {
        /* Append every instruction to the pairs */
        struct BFTree *tmp = malloc(sizeof(struct BFTree));
        BFTree_init(tmp, list->value, list->opcode, list->count);
        BFTree_addPair(lastPair, tmp);
        lastPair = tmp;

        /* Eventually add all nested instruction to the children section */
        if (lastPair->value == START_LOOP_TOKEN) {
            struct BFTree *child = malloc(sizeof(struct BFTree));
            BFTree_init(child, START_TOKEN, 'S', 1);
            list = parseRecursive(child, list->next, END_LOOP_TOKEN);
            BFTree_addChild(lastPair, child);
        }
        
        list = list->next;
    }

    return list;
}

void BFParser_run(struct BFTree *tree, struct BFList *list) {
    parseRecursive(tree, list, END_TOKEN);
}
