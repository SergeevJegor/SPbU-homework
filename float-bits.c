#include <stdio.h>
#include <stdlib.h>

int methodsAmount = 0;

typedef struct {
    int sign;
    int exponent;
    int mantissa;
} floatType;

typedef struct {
    void (* funcPointer)(floatType *);
    char* funcDescription;
} methods;

void printFloat(floatType *f);

void interfaceFloat(methods *m, floatType *f);

void unionMethod(floatType *f);

void pointerMethod(floatType *f);

void bitFieldsMethod(floatType *f);

void toFloat(int bits, floatType *f);

int main() {
    floatType floatNum;
    methods allMethods[3] = {{&unionMethod, "Computation will use union (float and int)"},
                             {&pointerMethod, "Computation will use integer dereference"},
                             {&bitFieldsMethod, "Computation will use union (float with bit fields structure)"}};
    methodsAmount = sizeof(allMethods)/sizeof(*allMethods);
    interfaceFloat(allMethods, &floatNum);
    printFloat(&floatNum);
    return 0;
}

void printFloat(floatType *f) {
    if (f->exponent == 0 && f->mantissa == 0)
        printf("Zero\n");
    else if (f->exponent == 255 && f->mantissa == 0) {
        if (f->sign == 0)
            printf("+Infinity\n");
        else printf("-Infinity\n");
    } else if (f->exponent == 255 && f->mantissa != 0)
        printf("NaN\n");
    else {
        printf("____%i  %i\n", f->sign, f->exponent - 127);
        printf("(-1) * 2 * %f\n", (float) f->mantissa / (1 << 23) + 1);
    }
}

void interfaceFloat(methods* m, floatType *f){
    printf("What computation method do you want to use?\n");
    for (int i = 0; i < methodsAmount; i++){
        printf("%i. %s\n", i + 1, m[i].funcDescription);
    }
    int userChoice = 0;
    scanf("%i", &userChoice);
    userChoice--;
    m[userChoice].funcPointer(f);
}

void unionMethod(floatType *f) {
    union {
        float floatVal;
        int intVal;
    } floatN;
    if (sizeof(int) != sizeof(float)) {
        exit(1);
    }
    float f1, f2;
    scanf("%f%f", &f1, &f2);
    floatN.floatVal = f1 / f2;
    toFloat(floatN.intVal, f);
}

void pointerMethod(floatType *f) {
    float n;
    float f1, f2;
    scanf("%f%f", &f1, &f2);
    n = f1 / f2;
    toFloat(*(int *) (&n), f);
}

void bitFieldsMethod(floatType *f) {
    union {
        float floatVal;
        struct {
            unsigned m : 23;
            unsigned e : 8;
            unsigned s : 1;
        } bitFields;
    } floatNum;

    scanf("%f", &floatNum.floatVal);
    f->sign = floatNum.bitFields.s;
    f->exponent = floatNum.bitFields.e;
    f->mantissa = floatNum.bitFields.m;
}

void toFloat(int bits, floatType *f) {
    f->sign = (bits >> 31) & 1;
    f->exponent = (bits >> 23) & ((1 << 8) - 1);
    f->mantissa = bits & ((1 << 23) - 1);
}