// interpreter.h
// Version 1.0

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "tree.h"

#define MEMORY_SIZE 30000

// implements the memory and memory pointer of the interpreter
typedef struct {
    uint8_t memory[MEMORY_SIZE];
    uint64_t pointer;
} Interpreter;

// initialize the interpreter
Interpreter *initInterpreter();

// destroy the interpreter
void freeInterpreter(Interpreter *interpreter);

// execute code of an Abstract Syntax Tree
void run(Interpreter *interpreter, Tree *tree);

#endif