#include <stdio.h>
#include <stdlib.h>

int bitAnd(int x, int y);//
int bitXor(int x, int y);//
int thirdBits();//
int fitsBits(int x, int n);//
int signBits(int x);//
int getByte(int x, int n);//
int logicalShift(int x, int n);//
int addOK(int x, int y);
int bang(int x);//
int conditional(int x, int y, int z);//
int isPower2(int x);//

int main() {
    /*int x = 4, y = 7, z = 9;
    printf("%i", %funcname%);*/
    system("pause");
    return 0;
}

int bitAnd(int x, int y){
    return ~(~x | ~y);
}

int bitXor(int x, int y){
    return ~(~(~x & y) & ~(x & ~y));
}

int thirdBits(){
    int x = 73; /*001001001*/
    x = (x << 18) | (x << 9) | (x);
    x = (x << 6) | 9;
    return x;
}

int fitsBits(int x, int n){
    return !(((x & ~(x << 31)) + (~x & (x << 31))) >> (n + ~0));/* (x << 31) = 0, x>=0; =1, x<0 */
}

int signBits(int x){
    return (!!x) | (x >> 31);
}

int getByte(int x, int n){
    return (x >> (n << 3)) & 255;
}

int logicalShift(int x, int n){
    return (x >> n) & ~((1 << 31) >> (n - 1));
}

int addOK(int x, int y){
    int signXY = (x + y) >> 31;
    int signX = x >> 31;
    int signY = y >> 31;
    return !(~(signX ^ signXY) & (signX ^ signY));
}

int conditional(int x, int y, int z){
    return ((((!!x) << 31) >> 31) & y) + ((((!x) << 31) >> 31) & z);
}

int bang(int x){
    x = (x >> 16) | (x >> 8) | (x >> 4) | (x >> 2) | (x >> 1) | x;
    return ~x & 1;
}

int isPower2(int x){
    int sign = x >> 31;

    return !((x & (x + (~0) ^ sign)) + (!x));
}