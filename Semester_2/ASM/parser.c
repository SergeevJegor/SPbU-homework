#include "parser.h"
#include "commandStructure.h"

#define INITIAL_SIZE 4;
#define SIZE_MULTIPLIER 2;

#define CHECK_ERRORS {if (errorID) goto errors;};

Parser *createParser() {
    Parser *parser = (Parser *) calloc(1, sizeof(Parser));
    if (!parser) {
        printf("ERROR: Cannot allocate memory for parser");
        exit(1);
    }
    parser->commandsSize = INITIAL_SIZE;
    parser->commands = (Command *) calloc(parser->commandsSize, sizeof(Command));
    if (!parser->commands) {
        printf("ERROR: Cannot allocate memory for command array in parser");
        exit(1);
    }
    parser->markersSize = INITIAL_SIZE;
    parser->markers = (MarkedCommand *) calloc(parser->markersSize, sizeof(MarkedCommand));
    if (!parser->markers) {
        printf("ERROR: Cannot allocate memory for marker array in parser");
        exit(1);
    }
    parser->markersAmount = 0;
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
    free(parser);
}

void resizeArray(void *array, size_t sizeOfElement, int *size) {
    /*
    if (!array || !size) {
        printf("Error: got NULL pointer");
        return;
    }
     */
    *size *= SIZE_MULTIPLIER;
    realloc(array, sizeOfElement * (*size));
}

void addCommand(Parser *parser, const int commandID, const int argument, const char *marker) {
    // Resize command and marker arrays, if needed:
    if (parser->commandsSize == parser->commandsAmount)
        resizeArray(parser->commands, sizeof(Command), &parser->commandsSize);
    if (parser->markersSize == parser->markersAmount)
        resizeArray(parser->markers, sizeof(MarkedCommand), &parser->markersSize);
    // Add command with argument:
    parser->commandsAmount++;
    parser->commands[parser->commandsAmount].command_id = commandID;
    parser->commands[parser->commandsAmount].argument = argument;
    // Link command number with marker if needed:
    if (marker != "") {
        parser->markersAmount++;
        strcpy(parser->markers[parser->markersAmount].marker, marker);
        parser->markers[parser->markersAmount].commandNumber = parser->commandsAmount;
    }
}

void formatCommandLine(char *commandLine, char formattedLine[MAX_STRING_LEN]) {
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
    strcpy(commandLine, formattedLine);
}

int spacesAmount(const char commandLine[MAX_STRING_LEN]) {
    int i = 0;
    int spacesCount = 0;

    while (commandLine[i] != '\0') {
        if (commandLine[i] == ' ') {
            if (spacesCount > 2)
                return -1;
            spacesCount++;
        }
        i++;
    }
    return spacesCount;
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

void resolveErrors(const int *errorID, int lineNumber, char commandLine[MAX_STRING_LEN]) {
    switch (*errorID) {
        case 0:
            return;
        case 1:
            printf("ERROR: Incorrect format in line %d\n->\"%s\"\n", lineNumber + 1, commandLine);
            break;
        case 11:
            printf("ERROR: Marker has incorrect format in line %d\n->\"%s\"\n", lineNumber + 1, commandLine);
            break;
        case 12:
            printf("ERROR: Command has incorrect format in line %d\n->\"%s\"\n", lineNumber + 1, commandLine);
            break;
        case 2:
            printf("ERROR: Duplicated marker in line %d\n->\"%s\"\n", lineNumber + 1, commandLine);
            break;
        case 3:
            printf("ERROR: Unexpected argument(s) in line %d\n->\"%s\"\n", lineNumber + 1, commandLine);
            break;
        case 4:
            printf("ERROR: Argument has wrong format in line %d\n->\"%s\"\n", lineNumber + 1, commandLine);
            break;
        case 41:
            printf("ERROR: Argument has wrong format (marker hadn't been defined yet) in line %d\n->\"%s\"", lineNumber + 1, commandLine);
            break;
        case 5:
            printf("ERROR: Argument missed in line %d\n->\"%s\"\n", lineNumber + 1, commandLine);
            break;
        case 6:
            printf("ERROR: Command expected in line %d\n->\"%s\"\n", lineNumber + 1, commandLine);
            break;
        default:
            printf("ERROR: Unknown error\n");
            break;
    }
}

void splitWords(const char commandLine[MAX_STRING_LEN], char words[3][MAX_STRING_LEN]) {
    int i = 0;
    int j = 0;
    int wordNumber = 0;
    while (commandLine[i] != '\0') {
        if (commandLine[i] == ' ') {
            words[wordNumber][j] = '\0';
            j = 0;
            wordNumber++;
        } else {
            words[wordNumber][j] = commandLine[i];
            j++;
        }
        i++;
    }
    words[wordNumber][j] = '\0';
}

int isMarker(const char *marker) {
    // Word is marker if last symbol is ':':
    return marker[strlen(marker) - 1] == ':';
}

int isMarkerCorrect(const char *marker, Parser *parserStructure, int *errorID) {
    // Checking if string is marker:
    if (!isMarker(marker)) {
        printf("ERROR: Argument should be correct marker. Abort");
        *errorID = -1;
        return 0;
    }
    // Checking if marker have correct name:
    char markerName[MAX_STRING_LEN];
    strncpy(markerName, marker, strlen(marker) - 1);
    if (!isNameCorrect(markerName)) {
        *errorID = 11;
        return 0;
    }
    // Checking if marker duplicates any of previous marker:
    for (int i = 0; i < parserStructure->markersAmount; i++) {
        if (!strcmp(parserStructure->markers->marker, markerName)) {
            *errorID = 2;
            return 0;
        }
    }
    return 1;
}

int getCommandID(const char *commandName) {
    if (strcmp(RET_TEXT, commandName) == 0) {
        return RET;
    }
    else if (strcmp(LD_TEXT, commandName) == 0) {
        return LD;
    }
    else if (strcmp(ST_TEXT, commandName) == 0) {
        return ST;
    }
    else if (strcmp(LDC_TEXT, commandName) == 0) {
        return LDC;
    }
    else if (strcmp(ADD_TEXT, commandName) == 0) {
        return ADD;
    }
    else if (strcmp(SUB_TEXT, commandName) == 0) {
        return SUB;
    }
    else if (strcmp(CMP_TEXT, commandName) == 0) {
        return CMP;
    }
    else if (strcmp(JMP_TEXT, commandName) == 0) {
        return JMP;
    }
    else if (strcmp(BR_TEXT, commandName) == 0) {
        return BR;
    }
    else
        return -1;
}

int isCommandCorrect(const char *commandName, int *errorID) {
    if (!isNameCorrect(commandName)) {
        *errorID = 12;
        return 0;
    }
    int commandID = getCommandID(commandName);
    if (commandID == -1) {
        *errorID = 12;
        return 0;
    }
    else return 1;
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
        return 1;
    else return 0;
}

int getIntegerArgument(const char *argument, int *errorID) {
    int argumentSign = 1;
    int integerArgument = 0;
    int i = 0;
    if (argument[i] == '-'){
        argumentSign = -1;
        i++;
    }
    while (argument[i] != '\0') {
        if ((argument[i] < '0') || (argument[i] > '9')) {
            *errorID = 4;
            return 0;
        }
        integerArgument = integerArgument * 10 + (argument[i] - '0');
        i++;
    }
    return argumentSign * integerArgument;
}

int resolveArgument(const int commandID, const char *argument, int *integerArgument, Parser *parserStructure, int *errorID) {
    *integerArgument = 0;
    if (doesFuncTakeMarkerArg(commandID)) {
        if (!isNameCorrect(argument)) {
            *errorID = 4;
            return 0;
        }
        int markerWasDefined = 0;
        int i;
        for (i = 0; i < parserStructure->markersAmount; i++) {
            if (argument == parserStructure->markers[i].marker){
                markerWasDefined = 1;
                break;
            }
        }
        if (!markerWasDefined) {
            *errorID = 41;
            return 0;
        } else {
            // In this case int argument will show the number of command to jump
            *integerArgument = parserStructure->markers[i].commandNumber;
            return 1;
        }
    }
    else if (doesFuncTakeIntegerArg(commandID)) {
        *integerArgument = getIntegerArgument(argument, errorID);
        if (*errorID) {
            return 0;
        } else
            return 1;
    }
    // 1 -- resolved; 0 -- not resolved
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
        exit(2); // TODO invent error number
    }

    int lineIndex = 0;
    char commandLine[MAX_STRING_LEN];
    while (!feof(program)) {
        int errorID;
        errorID = 0;

        fgets(commandLine, MAX_STRING_LEN, program);

        char formattedLine[MAX_STRING_LEN];
        formatCommandLine(commandLine, formattedLine);
        if (formattedLine[0] == '\0') {
            errorID = 0;
            goto errors;
        }

        char words[3][MAX_STRING_LEN];
        int wordsAmount;
        int commandID;
        int integerArgument = 0;

        wordsAmount = spacesAmount(commandLine) + 1;
        // wordsAmount == -1 + 1 == 0 in case we have more than 3 words:
        if (wordsAmount == 0) {
            errorID = 1;
            goto errors;
        }

        splitWords(commandLine, words);

        // If we have only 1 word, it should be a function without arguments:
        if (wordsAmount == 1) {
            isCommandCorrect(words[0], &errorID);
            if (errorID)
                goto errors;
            commandID = getCommandID(words[0]);
            if (doesFuncTakeIntegerArg(commandID) || doesFuncTakeMarkerArg(commandID)) {
                errorID = 5;
                goto errors;
            }
            addCommand(parser, commandID, 0, "");
        }
        // If we have 2 words it can be marker+function (if 1st word contains ":" as last symbol) or function+argument:
        else if (wordsAmount == 2) {
            // Marker+function:
            if (isMarker(words[0])) {
                isMarkerCorrect(words[0], parser, &errorID);
                if (errorID)
                    goto errors;
                char *markerName = "";
                strcpy(markerName, words[0]);
                markerName[strlen(markerName) - 1] = '\0';
                isCommandCorrect(words[1], &errorID);
                if (errorID)
                    goto errors;
                commandID = getCommandID(words[1]);
                if (doesFuncTakeMarkerArg(commandID) || doesFuncTakeIntegerArg(commandID)) {
                    errorID = 5;
                    goto errors;
                }
                addCommand(parser, commandID, 0, markerName);
            }
            // Function+argument
            else {
                isCommandCorrect(words[0], &errorID);
                if (errorID)
                    goto errors;
                commandID = getCommandID(words[0]);
                if (!doesFuncTakeMarkerArg(commandID) && !doesFuncTakeIntegerArg(commandID)) {
                    errorID = 3;
                    goto errors;
                }
                resolveArgument(commandID, words[1], &integerArgument, parser, &errorID);
                if (errorID)
                    goto errors;
                addCommand(parser, commandID, integerArgument, "");
            }
        }
        // Marker+function+argument
        else {
            if (isMarker(words[0])) {
                isMarkerCorrect(words[0], parser, &errorID);
                if (errorID)
                    goto errors;
                char markerName[MAX_STRING_LEN];
                strcpy(markerName, words[0]);
                markerName[strlen(markerName) - 1] = '\0';
                isCommandCorrect(words[1], &errorID);
                if (errorID)
                    goto errors;
                commandID = getCommandID(words[1]);
                if (!doesFuncTakeMarkerArg(commandID) && !doesFuncTakeIntegerArg(commandID)) {
                    errorID = 3;
                    goto errors;
                }
                resolveArgument(commandID, words[2], &integerArgument, parser, &errorID);
                if (errorID)
                    goto errors;
                addCommand(parser, commandID, integerArgument, markerName);
            }
        }

        errors:
        resolveErrors(&errorID, lineIndex, commandLine);
        lineIndex++;
    }
    fclose(program);
}