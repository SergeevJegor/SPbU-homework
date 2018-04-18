#ifndef ASM_PARSER_H
#define ASM_PARSER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "format.h"
#include "commandStructure.h"
#include "parser.h"

typedef struct {
    char marker[MAX_STRING_LEN];
    int commandNumber;
} MarkedCommand;

typedef struct {
    MarkedCommand *markers;
    Command *commands;

    int markersSize;
    int commandsSize;

    int markersAmount;
    int commandsAmount;
} Parser;

Parser *createParser();

void deleteParser(Parser *parser);

int parseFile(Parser *parser, const char *fileName);

Command *getCommandsList(Parser *parser);

#endif
