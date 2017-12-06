#include <stdio.h>

struct floatType f;

void printFloat(struct floatType f);
void fillFloatType(int bits);
void unionMethod();
void pointerMethod();
void bitFieldsMethod();

int main() {
    unionMethod();
    return 0;
}

struct floatType{
    int sign;
    int exponent;
    int mantissa;
};

void printFloat(struct floatType f){
    if (f.sign) f.sign = -1;
    else f.sign = 1;

}

void unionMethod(){
    union{
        float floatVal;
        int intVal;
    } floatN;
    float f1, f2;
    scanf("%f%f", &f1, &f2);
    floatN.intVal = f1/f2;
}