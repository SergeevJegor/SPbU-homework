#include <stdlib.h>
#include "interpreter.h"

int main() {
/*
    char fileName[255];
    printf("Enter file name: ");
    scanf("%s", fileName);



    int EXIT = FALSE;
    while (!EXIT) {

    }*/
    /*char *line = "    asdsa asd sad   asdad  asd: asd";
    char line1[MAX_STRING_LEN];
    formatCommandLine(line, line1);
    printf("%s", line1);
    char words[3][MAX_STRING_LEN];
    splitWords(line1, words);
    printf("\n%s\n%s\n%s", words[0], words[1], words[2]);*/
    interpretCommands("gcd");
    return 0;
}
