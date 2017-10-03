#include <stdio.h>
#include <stdlib.h>

int strlen(char* str);
void strcopy(char* dst, char* src);//src = source, dst = destination
void strcat(char* dst, char* src);
int strcmp(char* s1, char* s2);

int main() {
    /*char string[255] = "length of this string is 27";
    printf("%i", strlen(string));*/

    /*char src[255] = "that should be copied";
    char dst[255] = "fill with something";
    strcopy(dst, src);
    printf(dst);*/

    /*char src[255] = "that should be copied";
    char dst[255] = "fill with something";
    strcat(dst, src);
    printf(dst);*/

    /*char s1[255] = "abcd";
    char s2[255] = "abcd";
    printf("%i", strcmp(s1, s2));*/

    system("pause");
    return 0;
}

int strlen(char* str){
    int i = 0;
    while (*(str + i) != 0){
        i++;
    }
    return i;
}

void strcopy(char* dst, char* src){
    int i = 0;
    while (*(src + i) != 0){
        *(dst + i) = *(src + i);
        i++;
    }
    *(dst + i) = 0;
}

void strcat(char* dst, char* src){
    int i = 0;
    int len = strlen(dst);
    while (*(src + i) != 0){
        *(dst + len + i) = *(src + i);
        i++;
    }
    *(dst + len + i) = 0;
}

int strcmp(char* s1, char* s2){
    int i = 0;
    int res = 0;
    int comp = *(s1+i) - *(s2+i);
    while (((comp = *(s1+i) - *(s2+i))==0)&&(*(s1+i) != 0)){
        i++;
    }
    return comp;
}