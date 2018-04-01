cmake_minimum_required(VERSION 3.9)
project(ASM C)

set(CMAKE_C_STANDARD 99)

add_executable(ASM parser.c parser.h main.c format.h commandStructure.h stack.c stack.h)