#include <stdio.h>
#include <stdlib.h>

int strlen(char* str);
void strcopy(char* dst, char* src);
void strcat(char* dst, char* src);
int strcmp(char* s1, char* s2);

int main() {
    char *str = "abc";
    int a = strlen(str);
    printf("%i", a);
    system("pause");
    return 0;
}

int strlen(char* str){
    int i = 0;
    while (*(str+i) != 0){
        i++;
    }
    return i;
}