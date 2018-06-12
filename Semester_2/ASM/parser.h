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
    MarkedCommand *markerDestination;
    Command *commands;

    int markersSize;
    int markerDestinationSize;
    int commandsSize;

    int markersAmount;
    int markerDestinationAmount;
    int commandsAmount;
} Parser;

Parser *createParser();

void deleteParser(Parser *parser);

int parseFile(Parser *parser, const char *fileName);

#endif
