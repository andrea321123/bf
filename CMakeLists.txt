cmake_minimum_required(VERSION 3.0.0)
project(bf C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra")

add_executable(bf
    src/interpreter.c
    src/lexer.c
    src/list.c
    src/main.c
    src/parser.c
    src/stream.c
    src/tree.c
    src/transpiler.c
)
