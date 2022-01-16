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

#include "list.h"

#include "common.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void BFList_init(
    struct BFList *self,
    enum Token value,
    size_t line,
    size_t column,
    char opcode
) {
    self->line = line;
    self->column = column;
    self->opcode = opcode;
    self->value = value;
    self->next = NULL;
}

void BFList_free(struct BFList *self) {
    if (self->next)
        BFList_free(self->next);

    free(self);
}

void BFList_addNext(struct BFList *self, struct BFList *next) {
    self->next = next;
}

void BFList_info(struct BFList *self) {
    while (self) {
        printf("%c at %zu, %zu\n", self->opcode, self->line, self->column);
        self = self->next;
    }
}
