// parser.h
// Version 1.0

#ifndef PARSER_H
#define PARSER_H

#include "tree.h"
#include "list.h"

// create an Abstract Syntax Tree based on a list of tokens
Tree *doParsing(List *list);

#endif