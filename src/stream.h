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

#ifndef STREAM_H
#define STREAM_H

#include <stddef.h>

/* Dynamic string implementation */
struct BFStream {
    char *str;

    size_t length;
    size_t capacity;
    size_t readIndex;
};

void BFStream_init(struct BFStream *self);

void BFStream_free(struct BFStream *self);

/* Append a character to the [self] string */
void BFStream_addChar(struct BFStream *self, char c);

/* Return next char in the stream, or EOF is stream is ended */
char BFStream_nextChar(struct BFStream *self);

#endif
