// lexer.h
// Version 1.0

#ifndef LEXER_H
#define LEXER_H

#include "list.h"

// return a list of Tokens based on the source code
List *parse(char *sourceCode);

#endif