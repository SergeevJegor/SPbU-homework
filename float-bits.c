#include <stdio.h>
#include <stdlib.h>


struct floatType{
    int sign;
    int exponent;
    int mantissa;
};

void printFloat(struct floatType* f);
void fillFloatType(int bits);
void unionMethod(struct floatType* f);
void pointerMethod(struct floatType* f);
void bitFieldsMethod(struct floatType* f);
void toFloat(int bits, struct floatType* f);

int main() {
    struct floatType floatNum;
    unionMethod(&floatNum);
    return 0;
}

void printFloat(struct floatType* f){
    if (f->sign) f->sign = -1;
    else f->sign = 1;
    
}

void unionMethod(struct floatType* f){
    union{
        float floatVal;
        int intVal;
    } floatN;
    float f1, f2;
    scanf("%f%f", &f1, &f2);
    floatN.intVal = (float) f1/f2;
    toFloat(floatN.intVal, f);
    printf(f);
}

void pointerMethod(struct floatType* f){
    float n;
    scanf("%f", &n);
    toFloat(*(int *)(& n), f);
}

void toFloat(int bits, struct floatType* f){
    f->sign = (bits >> 31) & 1;
    f->exponent = (bits >> 23) & ((1 << 8) - 1);
    f->mantissa = bits & ((1 << 23) - 1);
}