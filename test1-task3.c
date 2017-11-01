#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* code = fopen("D:\\Projects\\C\\Current-homework\\text.txt", "rb");
    char c, prev = '0';
    int com = 0;
    while (!feof(code)){
        c = (char) fgetc(code);
        if (c == '\n'){
            if (com == 1){
                printf("\n");
            }
            com = 0;
        } else if ((c == '/') && (prev == '/') && (com == 0)){
            com = 1;
        }else if (com == 1){
            printf("%c", c);
        }

        prev = c;
    }

    fclose(code);
    system("pause");
    return 0;
}