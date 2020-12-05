// token.h
// Version 1.1

#ifndef TOKEN_H
#define TOKEN_H

// represent a single instruction
typedef enum {
    INC_POINTER,
    DEC_POINTER,
    INC_VALUE,
    DEC_VALUE,
    GETCHAR,
    PUTCHAR,
    START_LOOP,
    END_LOOP,
    COMMENT
} Token;

#endif