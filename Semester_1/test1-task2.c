#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void format(char s[31], int a[31]){
    int j = 30;
    for (int i = (strlen(s) - 1); i >= 0; i--){
        a[j] = s[i] - '0';
        j--;
    }
}

int compBin(int a[31], int b[31]){ // 1 = (a > b); 0= (a = b); -1 = (a < b)
    int i = 0;
    while (((a[i] - b[i]) == 0) && (i < 30)){
        i++;
    }
    return (a[i]- b[i]);
}

int main() {
    char as[31], bs[31];
    scanf("%s %s", as, bs);

    int a[31];
    int b[31];
    int i = 0;
    while (i < 31){
        a[i] = b[i] = 0;
        i++;
    }
//asdasd
    format(as, a);
    format(bs, b);
    printf("%d", compBin(a, b));
    system("pause");
    return 0;
}