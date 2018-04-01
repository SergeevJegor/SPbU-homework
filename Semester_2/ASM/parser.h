#ifndef ASM_PARSER_H
#define ASM_PARSER_H

#include <stdlib.h>
#include <stdio.h>
#include "format.h"
#include "commandStructure.h"
#include "parser.h"

typedef struct {
    char marker[MAX_STRING_LEN];
    int commandNumber;
} MarkedCommand;

typedef struct {
    MarkedCommand * 
};

int correctCommand(char com[MAX_STRING_LEN]);

Command parseCommand(char com[MAX_STRING_LEN]);

#endif
