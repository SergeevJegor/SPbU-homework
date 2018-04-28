#ifndef ASM_INTERPRETER_H
#define ASM_INTERPRETER_H

#include <stdlib.h>
#include <stdio.h>
#include "format.h"
#include "commandStructure.h"
#include "parser.h"
#include "stack.h"

typedef struct {
    Command *commands;
    int commandsAmount;
    int *data;
    Stack *stack;
} CommandsArray;

void interpretCommands(char *fileName); // TODO add file name

#endif
