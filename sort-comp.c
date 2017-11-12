#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct SortFunc{
    void (*funcPointer)(int*, int);
    char funcName[255];
};

void bubbleSort(int *a, int arraySize);
void quickSort(int *a, int arraySize);
void countSort(int *a, int arraySize);
void randArr(int *a, int arraySize);
//void printArr(int *a, int arraySize);
void swap(int *a, int *b);

int main() {
    srand(time(NULL));
    struct SortFunc arraysDisc[3] = {{countSort, "Counting sort"}, {quickSort, "Quicksort"}, {bubbleSort, "Bubble sort"}};

    int arrSize[9] = {5, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
    int *a = malloc(100000000 * sizeof(int));
    int start_t, end_t;

    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 3; j++){
            randArr(a, arrSize[i]);
            start_t = clock();
            arraysDisc[j].funcPointer(a, arrSize[i]);
            end_t = clock();
            printf("Sort time of %s for %i array size is %.3fs \n", arraysDisc[j].funcName, arrSize[i], ((float)(end_t - start_t)) / CLOCKS_PER_SEC);
        }
    }
    system("pause");
    return 0;
}

void randArr(int *a, int arraySize){
    for (int i = 0; i < arraySize; i++){
        a[i] = rand();
    }
}

/*void printArr(int *a, int arraySize){
    for (int i = 0; i < arraySize; i++){
        printf("%i ", a[i]);
    }
    printf("\n\n");
}*/

void swap(int *a, int *b){
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}


void bubbleSort(int *a, int arraySize){
    for (int i = 0; i < arraySize - 1; i++){
        for (int j = i + 1; j < arraySize; j++){
            if (a[i] > a[j]){
                swap(a + i, a + j);
            }
        }
    }
}

void quickSort(int *a, int arraySize){
    if (arraySize < 2) return;

    int base = a[arraySize/2];
    int i, j;
    for ( i = 0, j = arraySize - 1; ; i++, j--){
        while (a[i] < base) i++;
        while (a[j] > base) j--;

        if (i >= j) break;

        swap(a + i, a + j);
    }
    quickSort(a, i);
    quickSort(a + i, arraySize - i);
}

void countSort(int *a, int arraySize){
    int min = 2147483647, max = -2147483648;
    for (int i = 0; i < arraySize; i++){
        if (a[i] < min) min = a[i];
        if (a[i] > max) max = a[i];
    }
    int *memory = malloc((max - min + 1) * sizeof(int));

    for (int i = 0; i < max - min + 1; i++){
        memory[i] = 0;
    }

    for (int i = 0; i < arraySize; i++){
        memory[a[i] - min]++;
    }
    int j = 0;
    for (int i = 0; i < max - min + 1; i++){
        if (memory[i]){
            int amount = memory[i];
            while (amount > 0){
                a[j] = i + min;
                j++;
                amount--;
            }
        }
    }
}