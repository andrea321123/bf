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

#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>

#define START_OPCODE 'S'
#define END_OPCODE 'E'

#define INC_POINTER_OPCODE '>'
#define DEC_POINTER_OPCODE '<'
#define INC_VALUE_OPCODE '+'
#define DEC_VALUE_OPCODE '-'
#define PUTCHAR_OPCODE '.'
#define GETCHAR_OPCODE ','
#define START_LOOP_OPCODE '['
#define END_LOOP_OPCODE ']'

#define DEFAULT_MEMORY_SIZE 30000

enum Token {
    START_TOKEN,
    END_TOKEN,
    COMMENT_TOKEN,

    INC_POINTER_TOKEN,
    DEC_POINTER_TOKEN,
    INC_VALUE_TOKEN,
    DEC_VALUE_TOKEN,
    PUTCHAR_TOKEN,
    GETCHAR_TOKEN,
    START_LOOP_TOKEN,
    END_LOOP_TOKEN,
};

/* Store all possible parameters that can be set by the users */
struct BFOptions {
    size_t memorySize;
    int transpile;
};

#endif
