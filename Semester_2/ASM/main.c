#include <stdlib.h>
#include "interpreter.h"

int main() {
    char stringKey = (char) "";
    int intKey = 0;
    int exitLoop = FALSE;
    while (!exitLoop) {
        printf("Enter action number to execute:\n");
        printf("1. Interpret program from file\n");
        printf("2. Exit interpretation\n");
        fscanf(stdin, "%c", &stringKey);
        intKey = stringKey - '0';
        if (intKey == 2)
            return 0;
        if (intKey == 1) {
            exitLoop = TRUE;
        } else
            printf("You entered wrong action number. Please, try again\n");
    }
    char fileName[MAX_STRING_LEN];
    exitLoop = FALSE;
    while (!exitLoop) {
        printf("Enter file name:\n");
        fscanf(stdin, "%s", fileName);
        // Check, if file can be opened:
        FILE *program = fopen(fileName, "r");
        if (!program) {
            fclose(program);
            printf("Can't find file with this name. Try again?\n");
            printf("1. Yes\n");
            printf("2. No. Abort\n");
            fscanf(stdin, "%c", &stringKey);
            intKey = stringKey - '0';
            if (intKey == 1)
                continue;
            else if (intKey == 2)
                return 0;
            else {
                printf("You entered wrong action number. Please, try again\n");
                continue;
            }

        } else {
            fclose(program);
            exitLoop = TRUE;
        }
    }
    printf("Starting interpreting...\n");
    interpretCommands(fileName);
    getc(stdin);
    return 0;
}
