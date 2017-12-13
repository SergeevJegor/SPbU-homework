#include <stdio.h>
#include <string.h>

const int MAX_LENGTH = 256;

int main(int argc, char const *argv[]) {
    FILE *file = fopen("text.txt", "r");
    char temp[MAX_LENGTH];
    for (int i = 0; i < MAX_LENGTH; i++) {
        temp[i] = 0;
    }
    while (!feof(file)) {
        char s[MAX_LENGTH];
        for (int i = 0; i < MAX_LENGTH; i++) {
            s[i] = 0;
        }
        fgets(s, MAX_LENGTH, file);
        int len = (int) strlen(s);
        for (int i = len; i < MAX_LENGTH; i++) {
            s[i] = 0;
        }
        for (int i = 0; i < MAX_LENGTH; i++) {
            temp[i] = temp[i] ^ s[i];
        }
    }
    for (int i = 0; i < MAX_LENGTH; i++) {
        printf("%c", temp[i]);
    }
    fclose(file);
}