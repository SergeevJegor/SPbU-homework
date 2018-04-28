#include "interpreter.h"
#include "commandStructure.h"

CommandsArray *createInterpreter(char *fileName) {
    Parser *parser = createParser();
    parseFile(parser, fileName);
    CommandsArray *interpreter = calloc(1, sizeof(CommandsArray));
    interpreter->commandsAmount = parser->commandsAmount;
    interpreter->commands = calloc((size_t) interpreter->commandsAmount, sizeof(Command));
    if (!interpreter->commands) {
        printf("ERROR: Cannot allocate memory for interpreter's commands array");
        exit(1);
    }
    interpreter->data = calloc(DATA_SIZE, sizeof(int));
    if (!interpreter->data) {
        printf("ERROR: Cannot allocate memory for interpreter's data array");
        exit(1);
    }
    interpreter->stack = createStack();

    for (int i = 0; i < parser->commandsAmount; i++) {
        interpreter->commands[i] = parser->commands[i];
    }
    deleteParser(parser);
    return interpreter;
}

/*
void getCommandByID(int commandID, int argument) {
    char *command = "";
    switch (commandID) {
        case RET:
            command = RET_TEXT;
            break;
        case LD:
            command = LD_TEXT;
            break;
        case ST:
            command = ST_TEXT;
            break;
        case LDC:
            command = LDC_TEXT;
            break;
        case ADD:
            command = ADD_TEXT;
            break;
        case SUB:
            command = SUB_TEXT;
            break;
        case CMP:
            command = CMP_TEXT;
            break;
        case JMP:
            command = JMP_TEXT;
            break;
        case BR:
            command = BR_TEXT;
            break;
        default:
            break;
    }
    printf("%s with argument %d\n", command, argument);
}
 */

void deleteInterpreter(CommandsArray *interpreter) {
    if (!interpreter) {
        printf("ERROR: Interpreter doesn't exist");
        return;
    }
    deleteStack(interpreter->stack);
    free(interpreter->data);
    free(interpreter->commands);
    free(interpreter);
}

void printStack(CommandsArray *interpreter) {
    if (!interpreter) {
        printf("ERROR: Interpreter doesn't exist");
        return;
    }
    printf("Stack status:\n");
    for (int i = interpreter->stack->amount - 1; i >= 0; i--)
        printf("   %d\n", interpreter->stack->elements[i]);
}

void interpretCommands(char *fileName) {
    CommandsArray *interpreter = createInterpreter(fileName);
    /*
    for (int i = 0; i < interpreter->commandsAmount; i++) {
        printf("Command: %d. Argument: %d\n", interpreter->commands[i].commandID, interpreter->commands[i].argument);
    }
     */

    int currentCommandNumber = 0;
    int finishedInterpreting = FALSE;
    const int maxAddressedMemory = DATA_SIZE - 1;
    while ((currentCommandNumber < interpreter->commandsAmount) && (!finishedInterpreting)) {
        //getCommandByID(interpreter->commands[currentCommandNumber].commandID, interpreter->commands[currentCommandNumber].argument);
        switch (interpreter->commands[currentCommandNumber].commandID) {
            case RET:
                finishedInterpreting = TRUE;
                break;
            case LD:
                pushStack(interpreter->stack, interpreter->data[interpreter->commands[currentCommandNumber].argument]);
                currentCommandNumber++;
                break;
            case ST:
                if (interpreter->commands[currentCommandNumber].argument <= maxAddressedMemory) {
                    interpreter->data[interpreter->commands[currentCommandNumber].argument] = popStack(
                            interpreter->stack);
                    currentCommandNumber++;
                } else {
                    printf("ERROR: Memory address exceeds data size limit");
                }
                break;
            case LDC:
                pushStack(interpreter->stack, interpreter->commands[currentCommandNumber].argument);
                currentCommandNumber++;
                break;
            case ADD:
                if (interpreter->stack->amount > 1) {
                    pushStack(interpreter->stack, interpreter->stack->elements[interpreter->stack->amount - 1] +
                                                  interpreter->stack->elements[interpreter->stack->amount - 2]);
                } else {
                    printf("ERROR: Not enough elements on stack");
                    exit(2);
                }
                currentCommandNumber++;
                break;
            case SUB:
                if (interpreter->stack->amount > 1) {
                    pushStack(interpreter->stack, interpreter->stack->elements[interpreter->stack->amount - 1] -
                                                  interpreter->stack->elements[interpreter->stack->amount - 2]);
                } else {
                    printf("ERROR: Not enough elements on stack");
                    exit(2);
                }
                currentCommandNumber++;
                break;
            case CMP:
                if (interpreter->stack->amount > 1) {
                    int result;
                    if (interpreter->stack->elements[interpreter->stack->amount - 1] <
                        interpreter->stack->elements[interpreter->stack->amount - 2]) {
                        result = -1;
                    } else if (interpreter->stack->elements[interpreter->stack->amount - 1] >
                               interpreter->stack->elements[interpreter->stack->amount - 2]) {
                        result = 1;
                    } else result = 0;
                    pushStack(interpreter->stack, result);
                } else {
                    printf("ERROR: Not enough elements on stack");
                    exit(2);
                }
                currentCommandNumber++;
                break;
            case JMP:
                if ((interpreter->commands[currentCommandNumber].argument >= 0) &&
                    (interpreter->commands[currentCommandNumber].argument < interpreter->commandsAmount)) {
                    currentCommandNumber = interpreter->commands[currentCommandNumber].argument;
                } else {
                    printf("ERROR: Unknown marker");
                }
                break;
            case BR:
                if ((interpreter->commands[currentCommandNumber].argument >= 0) &&
                    (interpreter->commands[currentCommandNumber].argument < interpreter->commandsAmount)) {
                    if (interpreter->stack->elements[interpreter->stack->amount - 1] != 0) {
                        currentCommandNumber = interpreter->commands[currentCommandNumber].argument;
                    } else currentCommandNumber++;
                } else {
                    printf("ERROR: Unknown marker");
                }
                break;
            default:
                printf("ERROR: Unknown command ID in commands array");
                break;
        }
    }
    printStack(interpreter);
    deleteInterpreter(interpreter);
}