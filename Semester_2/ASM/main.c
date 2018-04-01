#include <stdlib.h>
#include "format.h"
#include "parser.h"

int main() {

    char fileName[255];
    printf("Enter file name: ");
    scanf("%s", fileName);
    FILE *program = fopen(fileName, "r");
    if (!program) {
        printf("ERROR. Cannot open file");
        return 1;
    }


    int EXIT = FALSE;
    while (!EXIT) {

    }
    return 0;
}