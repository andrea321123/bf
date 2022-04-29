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

#define START_OPCODE 'S'
#define END_OPCODE 'E'

/* Basic opcodes */
#define INC_POINTER_OPCODE '>'
#define DEC_POINTER_OPCODE '<'
#define INC_VALUE_OPCODE '+'
#define DEC_VALUE_OPCODE '-'
#define PUTCHAR_OPCODE '.'
#define GETCHAR_OPCODE ','
#define START_LOOP_OPCODE '['
#define END_LOOP_OPCODE ']'

/* Extended Type I opcodes */
#define END_PROGRAM_OPCODE '@'
#define MOVE_STORAGE_VALUE_OPCODE '$'
#define MOVE_VALUE_STORAGE_OPCODE '!'
#define RIGHT_SHIFT_OPCODE '}'
#define LEFT_SHIFT_OPCODE '{'
#define NOT_OPCODE '~'
#define XOR_OPCODE '^'
#define AND_OPCODE '&'
#define OR_OPCODE '|'

#define DEFAULT_MEMORY_SIZE 30000

enum Token {
    START_TOKEN,
    END_TOKEN,
    COMMENT_TOKEN,

    /* Basic tokens */
    INC_POINTER_TOKEN,
    DEC_POINTER_TOKEN,
    INC_VALUE_TOKEN,
    DEC_VALUE_TOKEN,
    PUTCHAR_TOKEN,
    GETCHAR_TOKEN,
    START_LOOP_TOKEN,
    END_LOOP_TOKEN,

    /* Extended Type I tokens */
    END_PROGRAM_TOKEN,
    MOVE_STORAGE_VALUE_TOKEN,
    MOVE_VALUE_STORAGE_TOKEN,
    RIGHT_SHIFT_TOKEN,
    LEFT_SHIFT_TOKEN,
    NOT_TOKEN,
    XOR_TOKEN,
    AND_TOKEN,
    OR_TOKEN
};

#endif
