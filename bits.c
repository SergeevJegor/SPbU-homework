#include <stdio.h>
#include <stdlib.h>

int bitAnd(int x, int y);//
int bitXor(int x, int y);//
int thirdBits(void);//
int fitsBits(int x, int n);//
int sign(int x);//
int getByte(int x, int n);//
int logicalShift(int x, int n);//
int addOK(int x, int y);
int bang(int x);//
int conditional(int x, int y, int z);//
int isPower2(int x);//

int main() {
    //printf("%i",/*function*/);
    system("pause");
    return 0;
}

int bitAnd(int x, int y){
    return ~(~x | ~y);
}

int bitXor(int x, int y){
    return ~(~(~x & y) & ~(x & ~y));
}

int thirdBits(void){
    int x = 36; /*00100100*/
    x = x | (x << 6) | (x << 12) | (x << 18) | (x << 24);
    return x;
}

int fitsBits(int x, int n){
    int dif = (~n + 1) + 32;
    return !(x ^ ((x << dif) >> dif));
}

int sign(int x){
    return (!!x) | (x >> 31);
}

int getByte(int x, int n){
    return (x >> (n << 3)) & 255;
}

int logicalShift(int x, int n){
    return (x >> n) & (~(((1 << 31) >> n) << 1));
}

int addOK(int x, int y){
    int temp = (x + y) >> 31;
    x = x >> 31;
    y = y >> 31;
    return !!(~temp | x | y) & (temp | ~x | ~y);
}

int conditional(int x, int y, int z){
    return ((((!!x) << 31) >> 31) & y) + ((((!x) << 31) >> 31) & z);
}

int bang(int x){
    int negX = ~x+1;
    return ((negX | x) >> 31) + 1;
}

int isPower2(int x){
    int sign = x >> 31;

    return !((x & (x + (~0) ^ sign)) + (!x));
}