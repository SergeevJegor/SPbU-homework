#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct SortFunc{
    void *funcPointer;
    char funcName[255];
};

void bubbleSort(int *a, int arraySize);
void quickSort(int *a, int l, int r);
void memSort(int *a, int arraySize);
void randArr(int *a, int arraySize);
int partition();

int main() {
    srand(time(NULL));


    int arrSize[9] = {5, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
    int a[100000000];
    int allSorts[3];
    int start_t, end_t;

    for (int i = 0; i < 9; i++){
        randArr(a, arrSize[i]);
        start_t = clock();
        bubbleSort(a, arrSize[i]);
        end_t = clock();
        printf("Sort time of %s for %i array size is %i \n");
    }
    system("pause");
    return 0;
}

void randArr(int *a, int arraySize) {
    for (int i = 0; i < arraySize; i++){
        a[i] = rand();
    }
}

void bubbleSort(int *a, int arraySize) {
    int tmp;
    for (int i = 0; i < arraySize - 1; i++){
        for (int j = i + 1; j < arraySize; j++){
            if (a[i] < a[j]){
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}

void quickSort(int *a, int l, int r) {

}

