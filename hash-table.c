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

void clearTable(struct linkedList *table, int tableSize);

void insertToTable();

void parseText(struct linkedList* table, FILE *file);

int main {
    int tableSize;
    printf("Enter size of hash table:\n");
    scanf("%i", &tableSize);
    FILE *file = fopen("book.txt", "r");
    if (!file) {
        printf("Can't open file to read");
        exit(2);
    }

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

struct linkedList *createTable(int size) {
    struct linkedList *table = malloc(size * sizeof(struct linkedList));
    if (!table) {
        printf("Can't allocate memory. Abort");
        exit(1);
    }
    return table;
}

void clearTable(struct linkedList *table, int tableSize){
    for (int i = 0; i < tableSize; i++){
        struct linkedList *temp = table;
        free(table + i);
    }
}