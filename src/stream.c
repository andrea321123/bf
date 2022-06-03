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

#include "stream.h"

#include "common.h"

#include <stdio.h>
#include <stdlib.h>

#define START_CAPACITY 10

void BFStream_init(struct BFStream *self) {
    self->str = malloc(sizeof(char) * START_CAPACITY);
    self->capacity = START_CAPACITY;
    self->length = 0;
    self->readIndex = 0;
}

void BFStream_free(struct BFStream *self) {
    free(self->str);
    free(self);
}

void BFStream_addChar(struct BFStream *self, char c) {
    if (self->length >= self->capacity) {
        self->capacity *= 2;
        self->str = realloc(self->str, self->capacity);
    }

    self->str[self->length] = c;
    self->length++;
}

char BFStream_nextChar(struct BFStream *self) {
    if (self->readIndex >= self->length)
        return EOF;

    char c = self->str[self->readIndex];
    self->readIndex++;
    return c;
}
