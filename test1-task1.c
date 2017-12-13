#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int MAX_LEN = 255;

int main() {
    char c;
    char s[MAX_LEN];

    printf("Введите строку: \n");
    gets(s);
    printf("Введите символ: \n");
    c = getchar();

    int len = strlen(s);
    for (int i = 0; i < len; i++){
        if (s[i] != c){
            printf("%c", s[i]);
        }
    }
    printf("\n");
    getchar();
    return 0;
}