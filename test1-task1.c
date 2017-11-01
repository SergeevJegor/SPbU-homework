#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void charDel(char* s, int n){
    for (int i = n; i < strlen(s); i++){
        s[i] = s[i+1];
    }
}

int main() {
    char s[255];
    char c;

    gets(s);
    c =(char) getchar();
    int i = 0;
    while (s[i] != 0){
        if (s[i] == c){
            charDel(s, i);
            i--;
        }
        i++;
    }
    printf("%s", s);
    system("pause");
    return 0;
}