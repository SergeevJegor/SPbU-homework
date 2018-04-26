#include "parser.h"
#include "commandStructure.h"

#define INITIAL_SIZE 128
#define SIZE_MULTIPLIER 2

#define E_FORMAT 1
#define E_MARKER_FORMAT 11
#define E_COM_FORMAT 12
#define E_MARKER_DUPLICATED 2
#define E_ARG_UNEXPECTED 3
#define E_ARG_FORMAT 4
#define E_ARG_MISSED 5
#define ERROR (-1)

#define CHECK_ERRORS \
if (errorID) {\
    resolveErrors(errorID, lineIndex, commandLine, &parsingResult);\
    lineIndex++;\
    continue;\
}


Parser *createParser() {
    Parser *parser = (Parser *) calloc(1, sizeof(Parser));
    if (!parser) {
        printf("ERROR: Cannot allocate memory for parser");
        exit(1);
    }
    parser->commandsSize = INITIAL_SIZE;
    parser->commands = (Command *) calloc((size_t) parser->commandsSize, sizeof(Command));
    if (!parser->commands) {
        printf("ERROR: Cannot allocate memory for command array in parser");
        exit(1);
    }
    parser->markersSize = INITIAL_SIZE;
    parser->markers = (MarkedCommand *) calloc((size_t) parser->markersSize, sizeof(MarkedCommand));
    if (!parser->markers) {
        printf("ERROR: Cannot allocate memory for marker array in parser");
        exit(1);
    }
    parser->markerDestinationSize = INITIAL_SIZE;
    parser->markerDestination = (MarkedCommand *) calloc((size_t) parser->markerDestinationSize, sizeof(MarkedCommand));
    if (!parser->markerDestination) {
        printf("ERROR: Cannot allocate memory for marker array in parser");
        exit(1);
    }

    parser->markersAmount = 0;
    parser->markerDestinationAmount = 0;
    parser->commandsAmount = 0;

    return parser;
}

void deleteParser(Parser *parser) {
    if (!parser) {
        printf("ERROR: Parser doesn't exist");
        return;
    }
    if (parser->commands)
        free(parser->commands);
    if (parser->markers)
        free(parser->markers);
    if (parser->markerDestination)
        free(parser->markerDestination);
    free(parser);
}

void resizeCommandsArray(Parser *parser) {
    parser->commandsSize *= SIZE_MULTIPLIER;
    parser->commands = (Command *) realloc(parser->commands, parser->commandsSize * sizeof(Command));
}

void resizeMarkersArray(Parser *parser) {
    parser->markersSize *= SIZE_MULTIPLIER;
    parser->markers = (MarkedCommand *) realloc(parser->markers, parser->markersSize * sizeof(MarkedCommand));
}

void resizeMarkerDestinationArray(Parser *parser) {
    parser->markerDestinationSize *= SIZE_MULTIPLIER;
    parser->markerDestination = (MarkedCommand *) realloc(parser->markerDestination, parser->markerDestinationSize * sizeof(MarkedCommand));
}

void addCommand(Parser *parser, const int commandID, const int argument, const char *marker) {
    // Resize command and marker arrays, if needed:
    if (parser->commandsSize == parser->commandsAmount) {
        parser->commandsSize *= SIZE_MULTIPLIER;
        parser->commands = (Command *) realloc(parser->commands, parser->commandsSize * sizeof(Command));
    }
    if (parser->markersSize == parser->markersAmount) {
        parser->markersSize *= SIZE_MULTIPLIER;
        parser->markers = (MarkedCommand *) realloc(parser->markers, parser->markersSize * sizeof(MarkedCommand));
    }
    // Add command with argument:
    parser->commands[parser->commandsAmount].command_id = commandID;
    parser->commands[parser->commandsAmount].argument = argument;
    // Link command number with marker if needed:
    if (marker != "") {
        strcpy(parser->markers[parser->markersAmount].marker, marker);
        parser->markers[parser->markersAmount].commandNumber = parser->commandsAmount;
        parser->markersAmount++;
    }
    parser->commandsAmount++;
}

void formatCommandLine(const char *commandLine, char formattedLine[MAX_STRING_LEN]) {
    int freeIndex = 0;
    int i = 0;
    // Removing spaces at the beginning of line
    while (commandLine[i] == ' ')
        i++;
    /* Changing '\n' and ';' symbols to '\0' (our command line will end at the comment or new line)
     * Removing multiple spaces */
    while (commandLine[i] != '\0') {
        if (commandLine[i] == '\n' || commandLine[i] == ';') {
            formattedLine[freeIndex] = '\0';
            break;
        }
        if (commandLine[i] == ' ') {
            if (formattedLine[freeIndex - 1] == ' ') {
                i++;
                continue;
            }
        }
        formattedLine[freeIndex] = commandLine[i];
        freeIndex++;
        i++;
    }
}

int isNameCorrect(const char *name) {
    int i = 0;
    if (((name[i] < 'A') || (name[i] > 'Z')) && ((name[i] < 'a') || (name[i] > 'z')))
        return 0;
    i++;
    while (name[i] != '\0') {
        if (((name[i] < 'A') || (name[i] > 'Z')) &&
            ((name[i] < 'a') || (name[i] > 'z')) &&
            ((name[i] < '0') || (name[i] > '9')) &&
            (name[i] != '_'))
            return 0;
        i++;
    }
    return 1;
}

void resolveErrors(const int errorID, int lineNumber, char commandLine[MAX_STRING_LEN], int *parsingResult) {
    switch (errorID) {
        case 0:
            return;
        case E_FORMAT:
            printf("ERROR: Incorrect format in line %d\n->\"%s\"\n", lineNumber + 1, commandLine);
            *parsingResult = FALSE;
            break;
        case E_MARKER_FORMAT:
            printf("ERROR: Marker has incorrect format in line %d\n->\"%s\"\n", lineNumber + 1, commandLine);
            *parsingResult = FALSE;
            break;
        case E_COM_FORMAT:
            printf("ERROR: Command has incorrect format in line %d\n->\"%s\"\n", lineNumber + 1, commandLine);
            *parsingResult = FALSE;
            break;
        case E_MARKER_DUPLICATED:
            printf("ERROR: Duplicated marker in line %d\n->\"%s\"\n", lineNumber + 1, commandLine);
            *parsingResult = FALSE;
            break;
        case E_ARG_UNEXPECTED:
            printf("ERROR: Unexpected argument(s) in line %d\n->\"%s\"\n", lineNumber + 1, commandLine);
            *parsingResult = FALSE;
            break;
        case E_ARG_FORMAT:
            printf("ERROR: Argument has wrong format in line %d\n->\"%s\"\n", lineNumber + 1, commandLine);
            *parsingResult = FALSE;
            break;
        case E_ARG_MISSED:
            printf("ERROR: Argument missed in line %d\n->\"%s\"\n", lineNumber + 1, commandLine);
            *parsingResult = FALSE;
            break;
        default:
            printf("ERROR: Unknown error\n");
            break;
    }
}

int isMarker(const char *marker) {
    // Word is marker if last symbol is ':':
    return marker[strlen(marker) - 1] == ':';
}

int isMarkerCorrect(Parser *parser, const char *marker) {
    // Checking if string is marker:
    if (!isMarker(marker)) {
        printf("ERROR: Argument should be correct marker. Abort");
        return ERROR;
    }
    // Checking if marker have correct name:
    char markerName[MAX_STRING_LEN] = "";
    strncpy(markerName, marker, strlen(marker) - 1);
    if (!isNameCorrect(markerName))
        return E_MARKER_FORMAT;
    // Checking if marker duplicates any of previous marker:
    for (int i = 0; i < parser->markersAmount; i++) {
        if (!strcmp(parser->markers->marker, markerName))
            return E_MARKER_DUPLICATED;
    }
    return 0;
}

int getCommandID(const char *commandName) {
    if (strcmp(RET_TEXT, commandName) == 0) {
        return RET;
    } else if (strcmp(LD_TEXT, commandName) == 0) {
        return LD;
    } else if (strcmp(ST_TEXT, commandName) == 0) {
        return ST;
    } else if (strcmp(LDC_TEXT, commandName) == 0) {
        return LDC;
    } else if (strcmp(ADD_TEXT, commandName) == 0) {
        return ADD;
    } else if (strcmp(SUB_TEXT, commandName) == 0) {
        return SUB;
    } else if (strcmp(CMP_TEXT, commandName) == 0) {
        return CMP;
    } else if (strcmp(JMP_TEXT, commandName) == 0) {
        return JMP;
    } else if (strcmp(BR_TEXT, commandName) == 0) {
        return BR;
    } else
        return ERROR;
}

int isCommandCorrect(const char *commandName) {
    if (!isNameCorrect(commandName))
        return E_COM_FORMAT;
    int commandID = getCommandID(commandName);
    if (commandID == ERROR)
        return E_COM_FORMAT;
    else
        return 0;
}

int addDestinationMarker(Parser *parser, const char *destinationMarker) {
    if (parser->markerDestinationSize == parser->markerDestinationAmount) {
        parser->markerDestinationSize *= SIZE_MULTIPLIER;
        parser->markerDestination = (MarkedCommand *) realloc(parser->markerDestination,
                                                              parser->markerDestinationSize * sizeof(MarkedCommand));
    }
    MarkedCommand destinationMarkerAssociation;
    strcpy(destinationMarkerAssociation.marker, destinationMarker);
    destinationMarkerAssociation.commandNumber = -1; // TODO edit -1 to commandNumber
    parser->markerDestination[parser->markerDestinationAmount] = destinationMarkerAssociation;
    parser->markerDestinationAmount++;
    return parser->markerDestinationAmount - 1;
}

int doesFuncTakeMarkerArg(const int commandID) {
    if ((commandID == JMP) || (commandID == BR))
        return 1;
    else return 0;
}

int doesFuncTakeIntegerArg(const int commandID) {
    if ((commandID == LD) ||
        (commandID == ST) ||
        (commandID == LDC))
        return E_FORMAT;
    else return 0;
}

int getIntegerArgument(const char *argument, int *integerArgument) {
    int argumentSign = 1;
    *integerArgument = 0;
    int i = 0;
    if (argument[i] == '-') {
        argumentSign = -1;
        i++;
    }
    while (argument[i] != '\0') {
        if ((argument[i] < '0') || (argument[i] > '9'))
            return E_ARG_FORMAT;
        *integerArgument = *integerArgument * 10 + (argument[i] - '0');
        i++;
    }
    *integerArgument = *integerArgument * argumentSign;
    return 0;
}

int resolveArgument(Parser *parser, const int commandID, const char *argument, int *integerArgument) {
    *integerArgument = 0;
    int errorID = 0;
    if (doesFuncTakeMarkerArg(commandID)) {
        if (!isNameCorrect(argument))
            return E_ARG_FORMAT;
        // In this case int argument will show the number of command to jump
        *integerArgument = addDestinationMarker(parser, argument);
        return 0;
    } else if (doesFuncTakeIntegerArg(commandID)) {
        errorID = getIntegerArgument(argument, integerArgument);
        if (errorID) {
            return errorID;
        } else
            return 0;
    }
    return 0;
}

int parseFile(Parser *parser, const char *fileName) {
    if (!parser) {
        printf("ERROR: Parser doesn't exist");
        return FALSE;
    }
    if (!fileName) {
        printf("ERROR: No file to parse");
    }
    FILE *program = fopen("/home/jegor/Projects/C/ASM/input", "r");
    if (!program) {
        printf("ERROR. Cannot open file");
        exit(2);
    }

    int parsingResult = TRUE;

    int lineIndex = 0;
    char commandLine[MAX_STRING_LEN] = "";
    while (!feof(program)) {
        int errorID = 0;

        fgets(commandLine, MAX_STRING_LEN, program);
        if (commandLine[strlen(commandLine) - 1] == '\n')
            commandLine[strlen(commandLine) - 1] = '\0';

        char formattedLine[MAX_STRING_LEN] = "";
        formatCommandLine(commandLine, formattedLine);
        if (!formattedLine[0]) {
            lineIndex++;
            continue;
        }
        // Splitting command line:
        // If command line has more than 4 words it anyway has format error, so we take only 4 first words
        char *words[4];
        char *currentWord = strtok(formattedLine, " ");
        int wordsAmount = 0;
        while (wordsAmount < 4) {
            words[wordsAmount] = currentWord;
            currentWord = strtok(NULL, " ");
            wordsAmount++;
        }

        char *marker = "";
        char *argument = "";
        int integerArgument = 0;
        if (isMarker(words[0])) {
            errorID = isMarkerCorrect(parser, words[0]);
            CHECK_ERRORS;
            marker = words[0];
            marker[strlen(marker) - 1] = '\0';
            // Shift command words (words[0] should fit command name):
            for (int i = 0; i < 3; i++)
                words[i] = words[i + 1];
        }
        errorID = isCommandCorrect(words[0]);
        CHECK_ERRORS;
        int commandID = getCommandID(words[0]);
        if (doesFuncTakeIntegerArg(commandID) || doesFuncTakeMarkerArg(commandID)) {
            if (!words[1]) {
                errorID = E_ARG_MISSED;
                CHECK_ERRORS;
            }
            if (words[2]) {
                errorID = E_ARG_UNEXPECTED;
                CHECK_ERRORS;
            }
            argument = words[1];
        } else if (words[1]) {
            errorID = E_ARG_UNEXPECTED;
            CHECK_ERRORS;
        }
        errorID = resolveArgument(parser, commandID, argument, &integerArgument);
        CHECK_ERRORS;

        addCommand(parser, commandID, integerArgument, marker);

        lineIndex++;
    }
    // Linking marker names with command numbers:
    for (int i = 0; i < parser->markerDestinationAmount; i++) {
        for (int j = 0; j < parser->markersAmount; j++) {
            if (!strcmp(parser->markerDestination[i].marker, parser->markers[j].marker)) {
                parser->markerDestination[i].commandNumber = parser->markers[j].commandNumber;
            }
        }
    }
    // Replacing links (commandNumber->markerName) with (commandNumber->destinationCommandNumber:
    for (int i = 0; i < parser->commandsAmount; i++) {
        if (doesFuncTakeMarkerArg(parser->commands[i].command_id)) {
            parser->commands[i].argument = parser->markerDestination[parser->commands[i].argument].commandNumber;
        }
    }
    fclose(program);
    /*
    if (parsingResult) {
        for (int i = 0; i < parser->commandsAmount; i++) {
            printf("Command: %d. Argument: %d\n", parser->commands[i].command_id, parser->commands[i].argument);
        }
    }
     */
}