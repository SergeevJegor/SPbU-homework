#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char *key;
    int value;
    struct Node *next;
};

struct linkedList {
    struct Node *head;
    int length;
};

int hashFunction(char *key, int tableSize);
//s -- string. h(s) = (s[0] + s[1] * p + s[2] * p^2 + ... + s[i] * p^i) % tableSize; p -- prime number

struct linkedList *createTable(int size);

void clearTable();

void resizeTable();

void insertToTable();

int main {
    int tableSize;
    printf("Enter size of hash table:\n");
    scanf("%i", &tableSize);

    return 0;
};

int hashFunction(char *key, int tableSize) {
    int p = 1;
    int total = 0;
    int i = 0;
    while (key[i] != "\0") {
        total += key[i] * p;
        p *= 73;
        i++;
    }
    return total % tableSize;
}

struct linkedList *createTable(int size){
    struct linkedList* table = malloc(size * sizeof(struct linkedList));
    if (!table){
        printf("Can't allocate memory. Abort");
        exit(1);
    }
    return table;
}

