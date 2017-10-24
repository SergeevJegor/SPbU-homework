#include <stdio.h>
#include <stdlib.h>
#include <mem.h>

void other();
void input();


int main() {
    printf("Main adress %p \n", &main);
    printf("Other adress %p \n", &other);
    input();
    system("pause");
    return 0;
}


void input(){
    int i = 0;
    int intVal;
    char hex[8];
    int string[0];

    while (1){
        gets(hex);
        if (!strlen(hex)){
            break;
        }
        intVal = strtol(hex, 0, 16);
        *(string + i) = intVal;
        i++;
    }
}

void other(){
    printf("Executed");
}