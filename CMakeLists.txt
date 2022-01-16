cmake_minimum_required(VERSION 3.0.0)
project(bf C)

set(CMAKE_C_STANDARD 11)

add_executable(bf
    src/main.c
    src/list.c
    src/lexer.c
    src/tree.c
    src/parser.c
    src/interpreter.c
)