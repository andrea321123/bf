# bf

## About The Project

Interpreter for one of the most famous esoteric language, brainf*ck. For more information about the language, refer to [this page](https://en.wikipedia.org/wiki/Brainfuck).  
The goal of this project is to create a readable, easily extensible brainfuck interpreter and a fast brainfuck-to-C99 transpiler.

## Building

### Prerequisites

You can build the project using Cmake. Hence you should install Cmake on your machine. For more information, refer to the [CMake website](https://https://cmake.org/install).

### Build instructions

Build instructions for unix-like operating systems:  
```sh
git clone https://github.com/andrea321123/bf
cd bf
mkdir build
cd build
cmake ..
make
```

## Usage

The basic usage of the program is:

```sh
./bf bf/source/file
```

Too see a list of available options, run:

```sh
./bf --help

Usage: bf [FILE]
bf is an interpreter for the brainfuck language

With no FILE, or when FILE is -, read standard input

  -r, --run           run bf source program (default behaviour)
  -t, --transpile     transpile bf source to a C source file
  -f, --fast          does not check memory underflow or overflow.
                        Faster execution, but the program may crash
  -m MEMORY           specify the memory array size (default 30000)

    -h, --help        display this help and exit
    -v, --version     output version information and exit

```
