#include <stdio.h>
#include <stdlib.h>

int checkEndian() {
    union {
        int i;
        char c;
    } check;
    check.i = 1;
    return (check.c == 1);
}
int main() {
    int i = checkEndian();
    if (i == 1) {
        printf("Little endian");
    } else {
        printf("Big endian");
    }
    system("pause");
    return 0;
}